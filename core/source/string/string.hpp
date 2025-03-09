#pragma once

#include "defines.hpp"
#include "memory/allocator.hpp"
#include "memory/memory.hpp"

#include <cstring>

namespace pulsar {
template <typename CharType>
class StringRefBase;

/**
 * @brief Calculates the size of a null-terminated string.
 *
 * @tparam TChar The character type (default is `char`).
 * @param cstr The null-terminated string whose size is to be calculated.
 * @return The size of the string, excluding the null terminator.
 */
inline size_t Strlen(const char* cstr);

/**
 * @brief Copies a null-terminated string from source to destination.
 *
 * @param dst The destination buffer where the string will be copied.
 * @param bytesSize The size of the destination buffer in bytes.
 * @param src The source null-terminated string to be copied.
 * @return An error code (`errno_t`) indicating success or failure.
 */
inline errno_t Strcpy(char* dst, size_t bytesSize, const char* src);

/**
 * @brief Concatenates a null-terminated string to the end of another string.
 *
 * @param dst The destination buffer containing the string to which `src` will
 * be appended.
 * @param bytesSize The size of the destination buffer in bytes.
 * @param src The source null-terminated string to be appended.
 * @return An error code (`errno_t`) indicating success or failure.
 */
inline errno_t Strcat(char* dst, size_t bytesSize, const char* src);

/**
 * @brief Compares two null-terminated strings.
 *
 * @tparam TChar The character type (default is `char`).
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return An integer less than, equal to, or greater than zero if `str1` is
 * found, respectively, to be less than, to match, or be greater than `str2`.
 */
inline int Strcmp(const char* str1, const char* str2);

}  // namespace pulsar

#include "string.inl"