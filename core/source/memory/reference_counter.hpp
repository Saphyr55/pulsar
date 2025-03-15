#pragma once

#include "core_exports.hpp"
#include "defines.hpp"
#include "memory/deleter.hpp"

#include <atomic>

namespace pulsar {

class PULSAR_CORE_API ReferenceCounter {
public:
    using RefCountType = std::atomic_int32_t;

public:
    virtual void DestroyResource() = 0;

    int32_t GetSharedReferenceCount() const { return shared_reference_count_.load(); }

    bool IsUnique() const { return GetSharedReferenceCount() == 1; }

    void AddSharedReference() { shared_reference_count_.fetch_add(1); }

    void ReleaseSharedReference() {
        int32_t shared_reference_count = shared_reference_count_.fetch_sub(1);
        if (shared_reference_count == 0) {
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
        : DeleterHolder<DeleterType>(std::move(deleter))
        , resource_(resource) {}

    ReferenceCounterWithDeleter(const ReferenceCounterWithDeleter&) = delete;
    ReferenceCounterWithDeleter& operator=(const ReferenceCounterWithDeleter&) = delete;

private:
    ResourceType* resource_;
};

template <typename ResourceType, typename DeleterType>
PINLINE ReferenceCounter* NewReferenceCounterWithDeleter(ResourceType* resource, DeleterType&& deleter) {
    return static_cast<ReferenceCounter*>(new ReferenceCounterWithDeleter<ResourceType, DeleterType>(resource, std::move(deleter)));
}

template <typename ResourceType>
PINLINE ReferenceCounter* NewDefaultReferenceCounter(ResourceType* resource) {
    return NewReferenceCounterWithDeleter<ResourceType, DefaultDeleter<ResourceType>>(resource, DefaultDeleter<ResourceType>());
}

}  // namespace pulsar