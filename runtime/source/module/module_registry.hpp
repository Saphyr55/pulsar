#pragma once

#include "collection/hash_map.hpp"
#include "memory/allocator.hpp"
#include "module/module.hpp"
#include "runtime_exports.hpp"
#include "string/string.hpp"
#include "string/string_ref.hpp"

namespace pulsar {

class PULSAR_RUNTIME_API ModuleRegistry {
public:
    using Registry = HashMap<StringRef, Module*>;
    using Entry = Registry::EntryType;

public:
    static ModuleRegistry& Get();

    void AddModule(StringRef module_name, Module* module);

    inline Registry& GetModules() {
        return modules_;
    }

    ModuleRegistry()
        : modules_(20) {}

    ~ModuleRegistry();

private:
    Registry modules_;
};

}  //namespace pulsar

#define PULSAR_ADD_MODULE(name, type)                                   \
    static const type* g_module_##type = []() -> type* {                \
        type* module_##type = ::NewInstance<type>();                    \
        ::pulsar::ModuleRegistry::Get().AddModule(name, module_##type); \
        return module_##type;                                           \
    }();
