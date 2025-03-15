#ifdef _WIN32

#include <Windows.h>

#include "main/main.hpp"
#include "windows/windows_app.hpp"
#include "windows/display/windows_display.hpp"
#include "windows/windows_app.hpp"

using namespace pulsar;


int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nShowCmd) {
    
    WindowsAppContext windows_app_context(hInstance, nShowCmd);
    g_windows_app_context = &windows_app_context;
    WindowsDisplay windows_display(&windows_app_context);

    DisplayProvider::SetDisplay(&windows_display);

    // Use command line arguments to initialize the engine.
    int32_t argc = 1;
    const char* argv[] = {lpCmdLine};

    return PulsarMain(argc, argv);
}

#endif
