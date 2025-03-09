#pragma once

#include "collection/array.hpp"
#include "defines.hpp"
#include "hash/hasher.hpp"
#include "memory/allocator.hpp"
#include "memory/memory.hpp"

#include <initializer_list>

namespace pulsar {

template <typename KeyType, typename ValueType>
struct HashMapEntry {
    KeyType key;
    ValueType value;

    HashMapEntry() = default;

    HashMapEntry(const KeyType& in_key, const ValueType& in_value)
        : key(in_key)
        , value(in_value) {}
};

template <typename KeyType, typename ValueType>
struct HashMapElement {
    HashMapEntry<KeyType, ValueType> entry;
    HashMapElement<KeyType, ValueType>* next = nullptr;

    HashMapElement() = default;

    HashMapElement(const KeyType& key, const ValueType& value)
        : entry(key, value)
        , next(nullptr) {}
};

template <typename KeyType,
          typename ValueType,
          typename AllocatorType = DefaultAllocator<HashMapElement<KeyType, ValueType>>,
          typename HasherType = Hasher>
class HashMap {
public:
    using ElementType = HashMapElement<KeyType, ValueType>;
    using EntryType = HashMapEntry<KeyType, ValueType>;

    uint32_t Hash(const KeyType& key) const {
        return Hasher::hash<KeyType>(key) % capacity_;
    }

    void Remove(const KeyType& key) {
        size_t index = Hash(key);

        ElementType* current = elements_[index];
        ElementType* prev = nullptr;

        while (current != nullptr) {
            if (current->entry.key == key) {
                if (prev == nullptr) {
                    elements_[index] = current->next;
                } else {
                    prev->next = current->next;
                }

                allocator_.Deallocate(current, 1);
                --size_;

                return;
            }
            prev = current;
            current = current->next;
        }
    }

    ElementType* Insert(const KeyType& key, const ValueType& value) {
        if (size_ >= capacity_) {
            ResizeRehash(capacity_ * 2);
        }

        uint32_t index = Hash(key);

        ElementType* old_element = elements_[index];
        ElementType* current = old_element;

        while (current != nullptr) {
            if (current->entry.key == key) {  // TODO: Use a comparator.
                current->entry.value = value;
                return old_element;
            }
            current = current->next;
        }

        ElementType* new_element = CreateElement(key, value);
        new_element->next = old_element;
        elements_[index] = new_element;
        size_++;

        return new_element;
    }

    bool Contains(const KeyType& key) const {
        return GetPtr(key) != nullptr;
    }

    ValueType& Get(const KeyType& key) {
        uint32_t index = Hash(key);

        ElementType* element = Lookup(index, key);
        PCHECK(element);

        return element->entry.value;
    }

    ValueType* GetPtr(const KeyType& key) {
        uint32_t index = Hash(key);

        ElementType* element = Lookup(index, key);
        if (element) {
            return &element->entry.value;
        }

        return nullptr;
    }

    const ValueType& Get(const KeyType& key) const {
        uint32_t index = Hash(key);

        ElementType* element = Lookup(index, key);
        PCHECK(element);

        return element->entry.value;
    }

    const ValueType* GetPtr(const KeyType& key) const {
        uint32_t index = Hash(key);
        ElementType* element = Lookup(index, key);

        if (element) {
            return &element->entry.value;
        }

        return nullptr;
    }

    void Clear() {
        if (!elements_ || size_ == 0) {
            return;
        }

        for (size_t i = 0; i < capacity_; i++) {
            allocator_.Deallocate(elements_[i], 1);
            elements_[i] = nullptr;
        }

        size_ = 0;
    }

    PINLINE size_t Size() {
        return size_;
    }

    PINLINE size_t GetCapacity() {
        return capacity_;
    }

    HashMap(size_t capacity = 8)
        : size_(0)
        , capacity_(capacity)
        , elements_(nullptr)
        , allocator_(AllocatorType()) {
        elements_ = AllocateElements(capacity_);
    }

    HashMap(std::initializer_list<EntryType> init)
        : size_(init.size())
        , capacity_(init.size())
        , elements_(nullptr)
        , allocator_(AllocatorType()) {
        elements_ = AllocateElements(capacity_);
        for (const EntryType& entry : init) {
            Insert(entry.key, entry.value);
        }
    }

    HashMap(const HashMap& other)
        : size_(other.size_)
        , capacity_(other.capacity_)
        , elements_(nullptr)
        , allocator_(AllocatorType()) {
        elements_ = AllocateElements(capacity_);
        CopyFromOther(other.elements_, other.capacity_);
    }

    ~HashMap() {
        Clear();

        if (elements_) {
            Memory::Free(elements_, capacity_ * sizeof(ElementType*));
        }
    }
    
    HashMap& operator=(const HashMap& other) {
        if (this != &other) {
            Clear();
            capacity_ = other.capacity_;
            size_ = 0;
            elements_ = static_cast<ElementType**>(Memory::Allocate(capacity_ * sizeof(ElementType*)));
            CopyFromOther(other.elements_, other.capacity_);
        }

        return *this;
    }

	const ValueType& operator[](const KeyType& key) const {
        return Get(key);
    }

    ValueType& operator[](const KeyType& key) {
        uint32_t index = Hash(key);

        ElementType* element = Lookup(index, key);
        if (element == nullptr) {
            element = Insert(key, ValueType());
            return element->entry.value;
        }

        return element->entry.value;
    }

private:
    ElementType* Lookup(uint32_t index, const KeyType& key) const {
        ElementType* element = elements_[index];

        while (element != nullptr) {
            if (element->entry.key == key) { // TODO: Use a comparator.
                return element;
            }
            element = element->next;
        }

        return nullptr;
    }

    void ResizeRehash(size_t new_capacity) {
        size_t old_capacity = capacity_;
        ElementType** old_elements = elements_;

        size_t old_allocation_size = old_capacity * sizeof(ElementType*);
        ElementType** new_elements = AllocateElements(new_capacity);

        for (size_t i = 0; i < old_capacity; i++) {
            ElementType* old_element = old_elements[i];
            while (old_element != nullptr) {
                Insert(old_element->entry.key, old_element->entry.value);
                ElementType* temp = old_element;
                old_element = old_element->next;
            }
            new_elements[i] = old_element;
        }

        elements_ = new_elements;
        Memory::Free(old_elements, old_allocation_size);
    }

    ElementType* CreateElement(const KeyType& key, const ValueType& value) {
        ElementType* new_element = allocator_.Allocate(1);
        new_element->entry = EntryType(key, value);
        return new_element;
    }

    void CopyFromOther(ElementType** other_elements, size_t other_capacity) {
        for (size_t i = 0; i < other_capacity; ++i) {
            ElementType* current = allocator_.Allocate(1);
            Memory::Copy(current, other_elements[i], sizeof(ElementType));
            while (current != nullptr) {
                Insert(current->key, current->value);
                current = current->next;
            }
        }
    }

    static ElementType** AllocateElements(size_t capacity) {
        size_t allocation_size = capacity * sizeof(ElementType*);
        ElementType** elements = static_cast<ElementType**>(Memory::Allocate(allocation_size));
        for (size_t i = 0; i < capacity; i++) {
            elements[i] = nullptr;
        }
        return elements;
    }

private:
    uint32_t* hashes_{};
    ElementType** elements_;
    AllocatorType allocator_;
    size_t size_{};
    size_t capacity_{};
};

}  //namespace pulsar