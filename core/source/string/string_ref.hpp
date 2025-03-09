#pragma once

#include "string/string.hpp"

#include <memory>

namespace pulsar {

template <typename CharType>
class StringRefBase {
public:
    constexpr StringRefBase()
        : data_(nullptr), size_(0) {}

    constexpr StringRefBase(const CharType* str)
        : data_(str), size_(Strlen(str)) {}

    constexpr StringRefBase(const StringRefBase& other) = default;

    constexpr StringRefBase& operator=(const StringRefBase& other) = default;

    constexpr const CharType& operator[](size_t index) const {
        PCHECK(index >= size_)
        return data_[index];
    }

    constexpr operator const CharType*() const { return data_; }

    constexpr const CharType* Data() const { return data_; }

    constexpr size_t Size() const { return size_; }

    constexpr bool IsEmpty() const { return size_ == 0; }

    constexpr bool operator==(const StringRefBase& other) const {
        return size_ == other.size_ && MemoryCopy(data_, other.data_, size_) == 0;
    }

    constexpr bool operator==(const CharType* str) const {
        return *this == StringRefBase(str);
    }

    friend std::ostream& operator<<(std::ostream& os, const StringRefBase& view) {
        os << view.Data();
        return os;
    }

private:
    const CharType* data_;
    size_t size_;
};

using StringRef = StringRefBase<char>;
using WStringRef = StringRefBase<wchar_t>;

}  // namespace pulsar
