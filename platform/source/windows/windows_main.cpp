#include "platform.hpp"
#include "windows_app.hpp"
#ifdef _WIN32

#include <cstdlib>
#include <cstdint>

#include <Windows.h>

#include "windows/windows_app.hpp"

using namespace pulsar;

bool WindowsPreInit(WindowsAppContext* out_context) {
    if (!WindowsAppContextInitClass(out_context)) {
        return false;
    }
}

int32_t WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32_t nShowCmd) {

    static WindowsAppContext context(hInstance, nShowCmd);

    WindowsPreInit(&context);    

    return EXIT_SUCCESS;
}

#endif
