#pragma once

#include "memory/memory.hpp"

namespace pulsar {

template <typename AllocatorType, typename ResourceType>
concept IsAllocator = requires(AllocatorType t, ResourceType* r, size_t n) {
    { t.Allocate(n) } -> std::same_as<ResourceType*>;
    { t.Deallocate(r, n) } -> std::same_as<void>;
};

template <typename ResourceType>
class DefaultAllocator {
public:
    ResourceType* Allocate(const size_t n) {
        return static_cast<ResourceType*>(Memory::Allocate(n * sizeof(ResourceType)));
    }

    void Deallocate(ResourceType* resource, const size_t n) {
        Memory::Free(resource, n * sizeof(ResourceType));
    }
};

}  // namespace pulsar

template <typename ResourceType>
inline static ResourceType* NewInstance(auto&&... args) {
    return ::new ResourceType(std::forward<decltype(args)>(args)...);
}

template <typename ResourceType>
inline static void DeleteInstance(ResourceType* instance) {
    ::delete instance;
}

template <typename ResourceType>
inline static ResourceType* NewArray(size_t size) {
    return ::new ResourceType[size];
}

template <typename ResourceType>
inline static void DeleteArray(ResourceType* arr) {
    ::delete[] arr;
}
