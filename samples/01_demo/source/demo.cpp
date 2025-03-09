#include <defines.hpp>
#include <main/main.hpp>
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

#include <unordered_map>

using namespace pulsar;

class DemoModule : public Module {
public:
    virtual void Startup() override {
        Console::WriteLine("Startup demo module.");
    }
    
    virtual void Shutdown() override {
        Console::WriteLine("Shutdown demo module.");
    }

    virtual ~DemoModule() override {}
};

