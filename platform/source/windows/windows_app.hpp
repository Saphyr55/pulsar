#pragma once
#ifdef _WIN32

#include "defines.hpp"
#include <Windows.h>

namespace pulsar {

constexpr char AppClassName[] = "Pulsar Engine";

struct WindowsAppContext {
    
    WindowsAppContext(HINSTANCE in_hinstance, int32_t in_ncmd) 
        : hinstance(in_hinstance)
        , ncmd(in_ncmd) { } 

    HINSTANCE hinstance;
    HWND hwnd;
    WNDCLASSEX wc;
    int32_t ncmd;
};

bool WindowsAppContextInitClass(WindowsAppContext* out_context);

bool WindowsAppContextInitWindow(const char* title, WindowsAppContext* out_context);

void WindowsAppContextShowWindow(const WindowsAppContext* context);

void WindowsAppContextRunMessageLoop(const WindowsAppContext* context);

}  //namespace pulsar

#endif