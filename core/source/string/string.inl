#include "string/string.hpp"

namespace pulsar {

inline size_t Strlen(const char* cstr) {
    return strlen(cstr);
}

inline errno_t Strcpy(char* dst, size_t bytes_size, const char* src) {
    return strcpy_s(dst, bytes_size, src);
}

inline errno_t Strcat(char* dst, size_t bytes_size, const char* src) {
    return strcat_s(dst, bytes_size, src);
}

inline int Strcmp(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}

}  // namespace pulsar