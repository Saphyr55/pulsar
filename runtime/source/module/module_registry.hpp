#pragma once

#include "collection/hash_map.hpp"
#include "memory/shared_ref.hpp"
#include "module/module.hpp"
#include "runtime_exports.hpp"
#include "string/string_ref.hpp"

namespace pulsar {

class PULSAR_RUNTIME_API ModuleRegistry {
public:
    using Registry = HashMap<const char*, Module*>;
    using Entry = Registry::EntryType;

public:
    static ModuleRegistry& Get();

    void AddModule(const char* module_name, Module* module);

    inline HashMap<const char*, Module*>& GetModules() {
        return modules_;
    }

    ModuleRegistry() : modules_(8) {
    }

    ~ModuleRegistry() {
    }

private:
    Registry modules_;
};

}  //namespace pulsar

#define PULSAR_ADD_MODULE(NAME, TYPE) static std::nullptr_t _g_module__##__COUNTER__ = []() -> std::nullptr_t { \
    ::pulsar::ModuleRegistry::Get().AddModule(NAME, ::pulsar::newobj<TYPE>());                                  \
    return nullptr;                                                                                             \
}();
