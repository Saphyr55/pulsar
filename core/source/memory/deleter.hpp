#pragma once

#include <memory>
#include "memory/memory.hpp"

namespace pulsar {

template <typename DeleterType>
struct DeleterHolder {
    template <typename ResourceType>
    PINLINE void InvokeDeleter(ResourceType* resource) {
        deleter_.Destroy(resource);
    }

    explicit DeleterHolder(DeleterType&& deleter)
        : deleter_(std::move(deleter)) {}

private:
    DeleterType deleter_;
};

template <typename ResourceType>
struct DefaultDeleter {
    PINLINE void operator()(ResourceType* ptr) const { Destroy(ptr); }

    PINLINE void Destroy(ResourceType* ptr) const {
        if (ptr) {
            ::delete ptr;
        }
    }

    virtual ~DefaultDeleter() = default;
};

}  // namespace pulsar