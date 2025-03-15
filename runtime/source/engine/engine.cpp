#include "engine/engine.hpp"
#include "display/display.hpp"
#include "module/module.hpp"
#include "module/module_registry.hpp"
#include "object/object.hpp"

namespace pulsar {

Engine& Engine::Get() {
    static Engine engine;
    return engine;
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

bool Engine::IsRunning() const {
    return running_;
}

void Engine::Tick() {
    Display::Get().PumpsEvents();
    ObjectRegistry::Get().Tick();
}

bool Engine::Init() {

    ModuleRegistry& registry = ModuleRegistry::Get();

    for (ModuleRegistry::Entry& entry : registry.GetModules()) {
        if (entry.value != nullptr) {
            entry.value->Startup();
        }
    }

    return true;
}

}  //namespace pulsar