#include "memory/memory.hpp"
#include "defines.hpp"
#include "memory/memory_trace.hpp"

#include <cstdlib>
#include <cstring>

namespace pulsar {

void* Memory::Allocate(size_t size) {
    MemoryTrace::GlobalAddAllocateBytes(size);
    return ::malloc(size);
}

void Memory::Free(void* block, size_t size) {
    PCHECK_MSG(block, "Attempt to free a null pointer.");
    MemoryTrace::GlobalAddFreedBytes(size);
    ::free(block);
}

void* Memory::Copy(void* destination,
                   const void* source,
                   size_t size) {
    PCHECK(destination && source)
    return memcpy(destination, source, size);
}

void* Memory::CopyMove(void* destination,
                   const void* source,
                   size_t size) {
    PCHECK(destination && source)
    return memmove(destination, source, size);
}

void* Memory::Write(void* destination, int32_t value, size_t size) {
    return memset(destination, value, size);
}

int Memory::Compare(const void* buffer1, const void* buffer2, size_t size) {
    return memcmp(buffer1, buffer2, size);
}

}  // namespace pulsar

namespace pf = ::pulsar;

void* operator new(size_t size) {
    return ::pf::Memory::Allocate(size);
}

void* operator new(size_t size, void* (*alloc)(size_t size)) {
    return alloc(size);
}

void operator delete(void* resource, size_t size) noexcept {
    return ::pf::Memory::Free(resource, size);
}

void operator delete(void* resource, size_t size, void* (*dealloc)(void* resource, size_t size)) noexcept {
    dealloc(resource, size);
}

