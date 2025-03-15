#include "string/string.hpp"

namespace pulsar {

String::String()
    : data_(nullptr), size_(0) {
    CopyString("", 0);
}

String::String(const char* str) {
    PCHECK(str)
    size_ = Strlen(str);
    CopyString(str, size_);
}

String::String(const String& other) {
    CopyString(other.data_, other.size_);
}

String::~String() {
    DeleteArray(data_);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        DeleteArray(data_);
        CopyString(other.data_, other.size_);
    }
    return *this;
}

String String::Concat(const String& str) const {
    size_t new_length = size_ + str.size_;
    char new_data[new_length + 1];
    Memory::Copy(new_data, data_, size_);
    Memory::Copy(new_data + size_, str.data_, str.size_);
    new_data[new_length + 1] = '\0';
    return String(new_data);
}

void String::CopyString(const char* str, size_t len) {
    data_ = NewArray<char>(len + 1);
    Memory::Copy(data_, str, len);
    data_[len] = '\0';
    size_ = len;
}

}  //namespace pulsar