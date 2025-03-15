#include "module/module_registry.hpp"
#include "memory/memory.hpp"
#include "string/string_ref.hpp"

namespace pulsar {

ModuleRegistry& ModuleRegistry::Get() {
    static ModuleRegistry module_registry;
    return module_registry;
}

ModuleRegistry::~ModuleRegistry() {
    for (Entry& entry: modules_) {
        DeleteInstance(entry.value);
    }
}

void ModuleRegistry::AddModule(const StringRef module_name, Module* module) {
    modules_.Insert(module_name, module);
}


}  //namespace pulsar