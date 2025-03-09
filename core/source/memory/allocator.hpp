#pragma once

#include "memory/memory.hpp"

namespace pulsar {

template <typename T>
class DefaultAllocator {
public:
    T* Allocate(const size_t n) {
        return static_cast<T*>(Memory::Allocate(n * sizeof(T)));
    }

    void Deallocate(T* resource, const size_t n) {
        Memory::Free(resource, n * sizeof(T));
    }
};

}  // namespace pulsar