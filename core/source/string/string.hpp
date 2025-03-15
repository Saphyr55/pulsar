#pragma once

#include "collection/array.hpp"
#include "core_exports.hpp"

namespace pulsar {

PULSAR_CORE_API size_t Strlen(const char* str);
PULSAR_CORE_API errno_t Strcpy(char* dst, size_t bytes_size, const char* src);
PULSAR_CORE_API errno_t Strcat(char* dst, size_t bytes_size, const char* src);
PULSAR_CORE_API int Strcmp(const char* str1, const char* str2);

class PULSAR_CORE_API String {
public:
    size_t Size() const {
        return buffer_.Size();
    }

    size_t GetCapacity() const {
        return buffer_.GetCapacity();
    }

    String& Append(const char* str) {
        size_t size = Strlen(str);
        buffer_.Pop();
        for (int i = 0; i < size; i++) {
            buffer_.Add(str[i]);
        }
        buffer_.Add('\0');
        return *this;
    }

    String& Append(const String& str) {
        Append(str.Data());
        return *this;
    }

    const char* Data() const {
        return buffer_.Data();
    }

    char* Data() {
        return buffer_.Data();
    }

    void Clear() {
        buffer_.Clear();
    }

    void Reverse(size_t capacity) {
        buffer_.Reverse(capacity);
    }

public:
    String()
        : buffer_() {
        buffer_.Add('\0');
    }

    explicit String(size_t capacity)
        : buffer_(capacity) {
        PCHECK(capacity != 0)
        buffer_.Add('\0');
    }

    String(const char* str)
        : buffer_(Strlen(str) + 1) {
        Append(str);
    }

    String(const String& other)
        : buffer_(other.buffer_) {}

    String& operator=(const String& other) {
        if (this != std::addressof(other)) {
            buffer_ = other.buffer_;
        }
        return *this;
    }

    ~String() {}

protected:
    void EnsureCapacity(size_t required_capacity) {
        if (required_capacity > buffer_.GetCapacity()) {
            Reverse(required_capacity);
        }
    }

private:
    Array<char> buffer_;
};

}  //namespace pulsar

template <>
struct PULSAR_CORE_API ::std::hash<::pulsar::String> {
    size_t operator()(const ::pulsar::String& s) const noexcept {
        return ::std::hash<const char*>{}(s.Data());
    }
};
