#pragma once

#include <concepts>
#include "string/string.hpp"

namespace pulsar {

template <typename CharType>
class StringRefBase {
public:
    constexpr StringRefBase()
        : data_(nullptr)
        , size_(0) {}

    constexpr StringRefBase(const CharType* str)
        : data_(str)
        , size_(Strlen(str)) {}

    constexpr StringRefBase(const String& str) 
        requires std::same_as<CharType, char>
        : data_(str.Data())
        , size_(str.Size()) {}

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
        return size_ == other.size_ && Strcmp(data_, other.data_) == 0;
    }

    constexpr bool operator==(const CharType* str) const {
        return *this == StringRefBase(str);
    }

private:
    const CharType* data_;
    size_t size_;
};

using StringRef = StringRefBase<char>;
using WStringRef = StringRefBase<wchar_t>;

}  // namespace pulsar

template <>
struct PULSAR_CORE_API ::std::hash<::pulsar::StringRef> {
    size_t operator()(const ::pulsar::StringRef& s) const noexcept {
        return ::std::hash<const char*>{}(s.Data());
    }
};
