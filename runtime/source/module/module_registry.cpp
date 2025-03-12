#include "module/module_registry.hpp"
#include "memory/memory.hpp"
#include "module_registry.hpp"

namespace pulsar {

ModuleRegistry& ModuleRegistry::Get() {
    static ModuleRegistry module_registry;
    return module_registry;
}

void ModuleRegistry::AddModule(const char* module_name, Module* module) {
    modules_.Insert(module_name, module);
}


}  //namespace pulsar