#pragma once

#include "core_exports.hpp"
#include "defines.hpp"
#include "memory/allocator.hpp"
#include "memory/memory.hpp"

#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstring>

namespace pulsar {

inline size_t Strlen(const char* cstr);

inline errno_t Strcpy(char* dst, size_t bytesSize, const char* src);

inline errno_t Strcat(char* dst, size_t bytesSize, const char* src);

inline int Strcmp(const char* str1, const char* str2);

class PULSAR_CORE_API String {
public:
    inline size_t Size() const {
        return size_;
    }

    inline bool IsEmpty() const {
        return size_ == 0;
    }

    bool operator==(const String& str) const {
        return size_ == str.size_ && Memory::Compare(data_, str.data_, size_) == 0;
    }

    bool operator!=(const String& str) const {
        return !(*this == str);
    }

    String operator+(const String& str) const {
        return Concat(str);
    }

    String& operator+=(const String& str) {
        *this = Concat(str);
        return *this;
    }

    String& operator+=(const char* str) {
        *this = Concat(String(str));
        return *this;
    }

    inline operator const char*() {
        return data_;
    }

    inline const char* c_str() const {
        return data_;
    }
    
public:
    String();
    String(const char* str);
    String(const String& other);
    ~String();

    String& operator=(const String& other);

private:
    String Concat(const String& str) const;

    void CopyString(const char* str, size_t len);

private:
    char* data_;
    size_t size_;
};

}  // namespace pulsar

#include "string.inl"