#pragma once

#include "defines.hpp"
#include "memory/deleter.hpp"

#include <atomic>
#include <type_traits>

namespace pulsar {

class ReferenceCounter {
public:
    using RefCountType = std::atomic<s32>;

public:
    virtual void DestroyResource() = 0;

    PINLINE s32 GetSharedReferenceCount() const {
        return shared_reference_count_.load(std::memory_order_relaxed);
    }

    PINLINE bool IsUnique() const { return GetSharedReferenceCount() == 1; }

    PINLINE void AddSharedReference() {
        shared_reference_count_.fetch_add(1, std::memory_order_relaxed);
    }

    PINLINE void ReleaseSharedReference() {
        s32 sharedCount =
            shared_reference_count_.fetch_sub(1, std::memory_order_acq_rel);
        if (sharedCount == 0) {
            DestroyResource();
            delete this;
        }
    }

public:
    virtual ~ReferenceCounter() = default;

protected:
    RefCountType shared_reference_count_ = 1;
};

template <typename ResourceType, typename DeleterType>
class ReferenceCounterWithDeleter : private DeleterHolder<DeleterType>,
                                    public ReferenceCounter {
public:
    virtual void DestroyResource() override {
        if (resource_) {
            this->InvokeDeleter(resource_);
        }
    }

public:
    ReferenceCounterWithDeleter(ResourceType* resource, DeleterType&& deleter)
        : DeleterHolder<DeleterType>(std::move(deleter)), resource_(resource) {
        this->shared_reference_count_ = 1;
    }

    ReferenceCounterWithDeleter(const ReferenceCounterWithDeleter&) = delete;
    ReferenceCounterWithDeleter& operator=(const ReferenceCounterWithDeleter&) = delete;

private:
    ResourceType* resource_;
};

template <typename ResourceType, typename DeleterType>
PINLINE ReferenceCounter* NewReferenceCounterWithDeleter(
    ResourceType* resource,
    DeleterType&& deleter) {
    return static_cast<ReferenceCounter*>(
        new ReferenceCounterWithDeleter<ResourceType, DeleterType>(resource, std::move(deleter)));
}

template <typename ResourceType>
PINLINE ReferenceCounter* NewDefaultReferenceCounter(ResourceType* resource) {
    return NewReferenceCounterWithDeleter<ResourceType,
                                          DefaultDeleter<ResourceType>>(
        resource, DefaultDeleter<ResourceType>());
}

}  // namespace pulsar