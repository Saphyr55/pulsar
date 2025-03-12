#include "engine/engine.hpp"
#include "collection/hash_map.hpp"
#include "module/module.hpp"
#include "module/module_registry.hpp"
#include "string/string_ref.hpp"

namespace pulsar {

Engine& Engine::Get() {
    static Engine engine;
    return engine;
}

bool Engine::Run() {
    return true;
}

bool Engine::Shutdown() {
    ModuleRegistry& registry = ModuleRegistry::Get();

    for (ModuleRegistry::Entry& entry : registry.GetModules()) {
        if (entry.value != nullptr) {
            entry.value->Shutdown();
        }
    }

    return true;
}

bool Engine::Startup() {
    ModuleRegistry& registry = ModuleRegistry::Get();

    for (ModuleRegistry::Entry& entry : registry.GetModules()) {
        if (entry.value != nullptr) {
            entry.value->Startup();
        }
    }

    return true;
}

}  //namespace pulsar