#pragma once

#include <utility>
#include "collection/array.hpp"
#include "collection/hash_map.hpp"
#include "memory/allocator.hpp"
#include "memory/memory.hpp"

namespace pulsar {

class Object;

class ObjectRegistry {
public:
    using AllocatorType = DefaultAllocator<Object*>;

    static ObjectRegistry& Get();

    void Register(Object* object);

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
class Object {
public:
    virtual void Tick() {};

    virtual ~Object() = default;
};

}  //namespace pulsar

template <typename T>
    requires std::derived_from<T, ::pulsar::Object>
T* NewObject(auto&&... args) {

    // TODO: Use a better allocator for objects.
    static ::pulsar::DefaultAllocator<T> allocator;
    
    T* object = new (&allocator.Allocate) T(std::forward<decltype(args)>(args)...);
    ::pulsar::ObjectRegistry::Get().Register(object);
    return object;
}
