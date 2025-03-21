#pragma once

#include "defines.hpp"
#include "memory/allocator.hpp"

#include <algorithm>
#include <type_traits>

namespace pulsar {

template <typename ElementType,
          typename AllocatorType = DefaultAllocator<ElementType>>
class Array {
public:
    using SizeType = size_t;
    using IteratorType = ElementType*;

public:
    void Add(const ElementType& element) {
        if (size_ >= capacity_) {
            Reverse(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        new (data_ + size_) ElementType(element);
        ++size_;
    }

    void Add(ElementType&& element) {
        if (size_ >= capacity_) {
            Reverse(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        new (data_ + size_) ElementType(std::move(element));
        ++size_;
    }

    template<typename OtherAllocatorType>
    void AddArray(const Array<ElementType, OtherAllocatorType>& array) {
        for (auto& element: array) {
            Add(element);
        }
    }

    template <typename... Args>
    void Emplace(Args&&... args) {
        if (size_ >= capacity_) {
            Reverse(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (data_ + size_) ElementType(std::forward<Args>(args)...);
        ++size_;
    }

    void Pop() {
        if (size_ > 0) {
            --size_;
            data_[size_].~ElementType();
        }
    }

    constexpr ElementType& operator[](SizeType index) {
        PCHECK(index < size_)
        return data_[index];
    }

    constexpr const ElementType& operator[](SizeType index) const {
        PCHECK(index < size_)
        return data_[index];
    }

    constexpr SizeType Size() const {
        return size_;
    }

    constexpr SizeType GetCapacity() const {
        return capacity_;
    }

    constexpr bool IsEmpty() const {
        return Size() == 0;
    }

    void Clear() {
        for (SizeType i = 0; i < size_; i++) {
            data_[i].~ElementType();
        }

        size_ = 0;
    }

    void Remove(const ElementType& value) {
        SizeType newSize = 0;
        for (SizeType i = 0; i < size_; ++i) {
            if (data_[i] != value) {
                if (newSize != i) {
                    new (data_ + newSize) ElementType(data_[i]);
                }
                ++newSize;
            } else {
                data_[i].~ElementType();
            }
        }
        size_ = newSize;
    }

    void Reverse(SizeType capacity) {
        AllocatorResize(capacity);
    }

    void Shrink() {
        if (size_ < capacity_) {
            Reverse(size_);
        }
    }

    void Swap(Array& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(allocator_, other.allocator_);
    }

    const ElementType* Data() const {
        return data_;
    }

    ElementType* Data() {
        return data_;
    }

public:
    constexpr explicit Array(AllocatorType&& allocator = AllocatorType()) noexcept
        : data_(nullptr)
        , size_(0)
        , capacity_(1)
        , allocator_(allocator) {
        data_ = AllocatorAllocate(capacity_);
    }

    constexpr Array(size_t capacity,
                    AllocatorType&& allocator = AllocatorType()) noexcept
        : data_(nullptr)
        , size_(0)
        , capacity_(capacity)
        , allocator_(allocator) {
        data_ = AllocatorAllocate(capacity_);
    }

    constexpr Array(std::initializer_list<ElementType> init,
                    const AllocatorType& allocator = AllocatorType())
        : allocator_(allocator)
        , data_(nullptr)
        , size_(init.size())
        , capacity_(init.size()) {
        if (size_ > 0) {
            data_ = AllocatorAllocate(capacity_);
            SizeType i = 0;
            for (const auto& item : init) {
                new (data_ + i) ElementType(item);
                ++i;
            }
        }
    }

    constexpr Array(const Array& other) noexcept
        : allocator_(other.allocator_)
        , data_(nullptr)
        , size_(other.size_)
        , capacity_(other.capacity_) {
        MoveData(other.data_);
    }

    constexpr Array(Array&& other) noexcept
        : data_(other.data_)
        , size_(other.size_)
        , capacity_(other.capacity_)
        , allocator_(std::move(other.allocator_)) {
        other.data_ = nullptr;
    }

    ~Array() {
        Clear();
        if (data_) {
            AllocatorDeallocate(data_, capacity_);
            data_ = nullptr;
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            Swap(temp);
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            Clear();

            if (data_) {
                AllocatorDeallocate(data_, capacity_);
            }

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            allocator_ = std::move(other.allocator_);
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        return *this;
    }

public:
    IteratorType begin() {
        return data_;
    }

    const IteratorType begin() const {
        return data_;
    }

    const IteratorType cbegin() const {
        return data_;
    }

    IteratorType end() {
        return data_ + size_;
    }

    const IteratorType end() const {
        return data_ + size_;
    }

    const IteratorType cend() const {
        return data_ + size_;
    }

private:
    void MoveData(ElementType* source) {
        if (size_ <= 0) {
            return;
        }

        data_ = AllocatorAllocate(capacity_);
        for (SizeType i = 0; i < size_; ++i) {
            new (data_ + i) ElementType(source[i]);
        }
    }

    void AllocatorResize(SizeType new_capacity) {
        if (new_capacity < size_) {
            size_ = new_capacity;
        }
        
        ElementType* new_data = AllocatorAllocate(new_capacity);
        for (SizeType i = 0; i < size_; ++i) {
            new (new_data + i) ElementType(std::move(data_[i]));
            data_[i].~ElementType();
        }

        if (data_) {
            AllocatorDeallocate(data_, capacity_);
        }
        
        data_ = new_data;
        capacity_ = new_capacity;

        if constexpr (std::is_default_constructible_v<ElementType>) {
            for (SizeType i = 0; i < capacity_; ++i) {
                new (data_ + i) ElementType();
            }
            size_ = capacity_;
        } else if constexpr (std::is_pointer_v<ElementType>) {
            for (SizeType i = 0; i < capacity_; ++i) {
                new (data_ + i) (ElementType)(nullptr);
            }
            size_ = capacity_;
        }

    }

    ElementType* AllocatorAllocate(SizeType n) {
        return allocator_.Allocate(n);
    }

    void AllocatorDeallocate(ElementType* p, SizeType n) {
        if (p) {
            allocator_.Deallocate(p, n);
        }
    }

private:
    ElementType* data_;
    SizeType size_;
    SizeType capacity_;
    AllocatorType allocator_;
};

template <typename ElementType, typename AllocatorType>
constexpr bool operator==(const Array<ElementType, AllocatorType>& lhs,
                          const Array<ElementType, AllocatorType>& rhs) {
    if (lhs.Size() != rhs.Size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.Size(); ++i) {
        if (!(lhs[i] == rhs[i])) {
            return false;
        }
    }

    return true;
}

template <typename ElementType, typename AllocatorType>
constexpr bool operator!=(const Array<ElementType, AllocatorType>& lhs,
                          const Array<ElementType, AllocatorType>& rhs) {
    return !(lhs == rhs);
}

template <typename ElementType, typename AllocatorType>
constexpr void Swap(
    Array<ElementType, AllocatorType>& lhs,
    Array<ElementType, AllocatorType>& rhs) noexcept(noexcept(lhs.Swap(rhs))) {
    lhs.Swap(rhs);
}

}  // namespace pulsar
