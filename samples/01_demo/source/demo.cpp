#include <defines.hpp>
#include <memory/memory.hpp>
#include <memory/memory_trace.hpp>
#include <memory/shared_ref.hpp>
#include <collection/array.hpp>
#include <collection/index_range.hpp>
#include <collection/option.hpp>
#include <io/console.hpp>
#include <io/file_handle.hpp>
#include <io/file_system.hpp>
#include <module/module.hpp>
#include <module/module_registry.hpp>
#include <string/format.hpp>

using namespace pulsar;

class DemoModule : public Module {
public:
    virtual void Startup() override {
        PrintLine("Startup demo module.");
    }
    
    virtual void Shutdown() override {
        PrintLine(VFormat("Shutdown %s.", "DemoModule"));
    }

    virtual ~DemoModule() override {}
};

PULSAR_ADD_MODULE("DemoModule", DemoModule)
