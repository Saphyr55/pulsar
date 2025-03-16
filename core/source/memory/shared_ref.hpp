#pragma once

#include <concepts>
#include "core_exports.hpp"
#include "memory/reference_counter.hpp"

namespace pulsar {

template <typename ResourceType>
class SharedRef {
public:
    ResourceType& operator*() {
        PCHECK(resource_)
        return *resource_;
    }

    ResourceType* operator->() { return resource_; }

    const ResourceType& operator*() const {
        PCHECK(resource_)
        return *resource_;
    }

    const ResourceType* operator->() const { return resource_; }

    ResourceType* GetResource() { return resource_; }

    const ResourceType* GetResource() const { return resource_; }

    s32 GetSharedReferenceCount() const {
        return reference_counter_->GetSharedReferenceCount();
    }

    bool IsUnique() const { return reference_counter_->IsUnique(); }

    template <typename DeleterType = DefaultDeleter<ResourceType>>
    void Reset(ResourceType* resource = nullptr,
               DeleterType&& deleter = DeleterType()) {
        Release();

        resource_ = resource;

        if (resource_) {
            reference_counter_ =
                NewReferenceCounterWithDeleter<ResourceType, DeleterType>(resource_,
                                                                          deleter);
        } else {
            reference_counter_ = nullptr;
        }
    }

    bool IsValid() const { return resource_ != nullptr; }

    explicit operator bool() const { return IsValid(); }

    SharedRef() = default;
    
    explicit SharedRef(ResourceType* resource)
        : resource_(resource)
        , reference_counter_(NewDefaultReferenceCounter<ResourceType>(resource_)) {
    }

    template <typename DerivedType>
        requires std::derived_from<DerivedType, ResourceType>
    explicit SharedRef(DerivedType* resource)
        : resource_(resource)
        , reference_counter_(NewDefaultReferenceCounter<DerivedType>(resource)) {}

    template <typename DerivedType, typename DeleterType>
        requires std::derived_from<DerivedType, ResourceType>
    SharedRef(DerivedType* resource, DeleterType&& deleter)
        : resource_(resource)
        , reference_counter_(NewReferenceCounterWithDeleter<DerivedType, DeleterType>(resource, deleter)) {
    }

    template <typename DerivedType>
        requires std::derived_from<DerivedType, ResourceType>
    explicit SharedRef(const SharedRef<DerivedType>& other)
        : resource_(other.resource_)
        , reference_counter_(other.reference_counter_) {
        if (reference_counter_) {
            reference_counter_->AddSharedReference();
        }
    }

    template <typename DerivedType>
        requires std::derived_from<DerivedType, ResourceType>
    SharedRef& operator=(const SharedRef<DerivedType>& other) {
        if (this != &other) {
            Release();

            resource_ = other.resource_;
            reference_counter_ = other.reference_counter_;
            if (reference_counter_) {
                reference_counter_->AddSharedReference();
            }
        }

        return *this;
    }

    template <typename DerivedType>
        requires std::derived_from<DerivedType, ResourceType>
    SharedRef(SharedRef<DerivedType>&& other)
        : resource_(other.resource_)
        , reference_counter_(other.reference_counter_) {
        other.resource_ = nullptr;
        other.reference_counter_ = nullptr;
    }

    template <typename DerivedType>
        requires std::derived_from<DerivedType, ResourceType>
    SharedRef& operator=(SharedRef<DerivedType>&& other) {
        resource_ = other.resource_;
        reference_counter_ = other.reference_counter_;

        other.resource_ = nullptr;
        other.reference_counter_ = nullptr;
        return *this;
    }

    ~SharedRef() { Release(); }

public:
    template <typename OtherResourceType>
    friend class SharedRef;

private:
    void Release() {
        if (reference_counter_) {
            reference_counter_->ReleaseSharedReference();
        }
    }

private:
    ResourceType* resource_ = nullptr;
    ReferenceCounter* reference_counter_ = nullptr;
};

template <typename ResourceType, typename... Args>
PINLINE SharedRef<ResourceType> MakeSharedRef(Args&&... args) {
    return SharedRef<ResourceType>(new ResourceType(std::forward<Args>(args)...));
}

}  // namespace pulsar

template <typename ResourceType>
struct ::std::hash<::pulsar::SharedRef<ResourceType>> {
    size_t operator()(const ::pulsar::SharedRef<ResourceType>& ref) const {
        return ::std::hash<ResourceType*>()(ref.GetResource());
    }
};
