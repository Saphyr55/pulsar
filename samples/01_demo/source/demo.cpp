#include <collection/array.hpp>
#include <collection/index_range.hpp>
#include <collection/option.hpp>
#include <defines.hpp>
#include <io/file_handle.hpp>
#include <io/file_system.hpp>
#include <memory/memory.hpp>
#include <memory/memory_trace.hpp>
#include <memory/shared_ref.hpp>
#include <module/module.hpp>
#include <module/module_registry.hpp>
#include <string/format.hpp>
#include <trace/trace.hpp>
#include <display/display.hpp>
#include <renderer/vulkan/vulkan.hpp>

using namespace pulsar;

class DemoModule : public Module {
public:
    virtual void Startup() override {
        PLOG_INFO("Demo Module", "Startup demo module.");
        Display& display = Display::Get();

        window_handle_ = display.CreateWindowHandle({"Demo Window", 800, 600, 100, 100});
        display.Show(window_handle_);
    }

    virtual void Shutdown() override {
        PLOG_INFO("Demo Module", "Shutdown demo module.");
    }

    virtual ~DemoModule() override {}

private:
    WindowHandle window_handle_;
};

PULSAR_ADD_MODULE("DemoModule", DemoModule)
