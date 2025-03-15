#pragma once

#include <cstddef>
#include <functional>

#include "core_exports.hpp"
#include "defines.hpp"

/**
 * @brief Overloads the global `new` operator to allocate memory.
 *
 * @param size The size of the memory block to allocate, in bytes.
 * @return A pointer to the allocated memory block.
 */
void* operator new(size_t size);

/**
 * @brief Overloads the global `new` operator to allocate memory using a custom allocator.
 *
 * @param size The size of the memory block to allocate, in bytes.
 * @param alloc A function pointer to the custom allocator.
 * @return A pointer to the allocated memory block.
 */
void* operator new(size_t size, std::function<void*(size_t size)> alloc);


/**
 * @brief Overloads the global `delete` operator to deallocate memory.
 *
 * @param resource A pointer to the memory block to deallocate.
 * @param size The size of the memory block, in bytes.
 */
void operator delete(void* resource, size_t size) noexcept;

void operator delete(void* resource, size_t size, std::function<void(void* resource, size_t size)> dealloc) noexcept;

namespace pulsar {

/**
 * @class Memory
 * @brief Provides memory management utilities such as allocation, deallocation, and memory manipulation.
 *
 * This class contains static methods for handling memory operations, including allocation, freeing,
 * writing values to memory, and copying memory blocks.
 */
class Memory {
public:

    /**
     * @brief Allocates a block of memory of the specified size.
     *
     * @param size The size of the memory block to allocate, in bytes.
     * @return A pointer to the allocated memory block, or nullptr if allocation fails.
     */
    PULSAR_CORE_API static void* Allocate(size_t size);

    /**
     * @brief Frees a previously allocated block of memory.
     *
     * @param block A pointer to the memory block to free.
     * @param size The size of the memory block, in bytes.
     */
    PULSAR_CORE_API static void Free(void* block, size_t size);

    /**
     * @brief Writes a specified value into a memory block.
     *
     * @param destination A pointer to the memory block where the value will be written.
     * @param value The value to write into the memory block.
     * @param size The number of bytes to write.
     * @return A pointer to the destination memory block.
     */
    PULSAR_CORE_API static void* Write(void* destination,
                                       int32_t value,
                                       size_t size);

    /**
     * @brief Copies a block of memory from the source to the destination.
     *
     * @param destination A pointer to the destination memory block.
     * @param source A pointer to the source memory block.
     * @param size The number of bytes to copy.
     * @return A pointer to the destination memory block.
     */
    PULSAR_CORE_API static void* Copy(void* destination,
                                      const void* source,
                                      size_t size);
        
    PULSAR_CORE_API static void* CopyMove(void* destination,
                                          const void* source,
                                          size_t size);

    PULSAR_CORE_API static int Compare(const void* buffer1, const void* buffer2, size_t size);
};

} // namespace pulsar
