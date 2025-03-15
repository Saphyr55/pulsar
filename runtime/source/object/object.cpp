#include "object/object.hpp"
#include "object.hpp"

namespace pulsar {

ObjectRegistry& ObjectRegistry::Get() {
    static ObjectRegistry registry;
    return registry;
}

void ObjectRegistry::Register(Object* object) {
    objects_.Add(object); 
}

void ObjectRegistry::Unregister(Object* object) {
    objects_.Remove(object);
}

void ObjectRegistry::Tick() {
    for (Object* object : objects_) {
        object->Tick();
    }
}

ObjectRegistry::~ObjectRegistry() {
    for (Object* object : objects_) {
        delete object;
    }
    objects_.Clear();
}

}