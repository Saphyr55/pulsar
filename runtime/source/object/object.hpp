#pragma once

#include <utility>
#include "collection/array.hpp"
#include "collection/hash_map.hpp"
#include "memory/allocator.hpp"
#include "memory/memory.hpp"
#include "runtime_exports.hpp"

namespace pulsar {

class Object;

class PULSAR_RUNTIME_API ObjectRegistry {
public:
    using AllocatorType = DefaultAllocator<Object*>;

    static ObjectRegistry& Get();

    template <typename T>
        requires std::derived_from<T, Object>
    void Register(T* object) {
        object->memory_size_ = sizeof(T);
        objects_.Add(object); 
    }

    void Unregister(Object* object);

    void Tick();

public:
    ObjectRegistry() = default;
    ~ObjectRegistry();

private:
    AllocatorType allocator_;
    Array<Object*> objects_;
};

/**
 * @class Object
 * @brief The Object class provides an interface for objects that require
 * regular updates.
 *
 * The Object class is designed to be used as a base class for objects
 * that require regular updates. It provides a single method, Tick(), that  is
 * called once per frame to update the object's state.
 */
class PULSAR_RUNTIME_API Object {
public:
    virtual void Tick() {};
    virtual ~Object() = default;

private:
    friend class ObjectRegistry;
    size_t memory_size_ = sizeof(Object);
};

}  //namespace pulsar

template <typename ObjectType>
    requires std::derived_from<ObjectType, ::pulsar::Object>
ObjectType* NewObject(auto&&... args) {
    
    using RegistryType = ::pulsar::ObjectRegistry;
    using AllocatorType = ::pulsar::DefaultAllocator<ObjectType>; // TODO: Use a better allocator for objects.

    ObjectType* object = new ObjectType(std::forward<decltype(args)>(args)...);
    RegistryType::Get().Register<ObjectType>(object);
    
    return object;
}
