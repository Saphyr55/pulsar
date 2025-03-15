#pragma once

#include <memory>
#include "collection/array.hpp"
#include "defines.hpp"
#include "memory/memory.hpp"
#include "string/string.hpp"

namespace pulsar {

class StringBuffer {
public:
    size_t Size() const {
        return buffer_.Size();
    }

    size_t GetCapacity() const {
        return buffer_.GetCapacity();
    }

    StringBuffer& Append(const char* str) {
        size_t size = Strlen(str);
        buffer_.Pop();
        for (int i = 0; i < size; i++) {
            buffer_.Add(str[i]);
        }
        buffer_.Add('\0');
        return *this;
    }

    StringBuffer& Append(String str) {
        Append(str.c_str());
        return *this;
    }

    const char* Data() const {
        return buffer_.Data();
    } 
    
    char* Data() {
        return buffer_.Data();
    }

    String ToString() const {
        return String(buffer_.Data());
    }

    void Clear() {
        buffer_.Clear();
    }

public:
    StringBuffer()
        : buffer_() {
        buffer_.Add('\0');
    }

    explicit StringBuffer(size_t capacity)
        : buffer_(capacity) {
        PCHECK(capacity != 0)
        buffer_.Add('\0');
    }

    StringBuffer(const char* str)
        : buffer_(Strlen(str) + 1) {
        Append(str);
    }

    StringBuffer(const StringBuffer& other)
        : buffer_(other.buffer_) {}

    StringBuffer& operator=(const StringBuffer& other) {
        if (this != std::addressof(other)) {
            buffer_ = other.buffer_;
        }
        return *this;
    }

    ~StringBuffer() {}

private:
    void EnsureCapacity(size_t required_capacity) {
        if (required_capacity > buffer_.GetCapacity()) {
            buffer_.Reverse(required_capacity);
        }
    }

private:
    Array<char> buffer_;
};

}  //namespace pulsar