#pragma once
#ifdef _WIN32

#include <Windows.h>
#include "defines.hpp"

namespace pulsar {

struct WindowsAppContext {
    WindowsAppContext(HINSTANCE in_hinstance, int32_t in_ncmd)
        : hinstance(in_hinstance)
        , ncmd(in_ncmd) {}

    HINSTANCE hinstance;
    int32_t ncmd;
};

inline constexpr const char g_class_name[] = "Pulsar Engine";
inline WindowsAppContext* g_windows_app_context = nullptr;



}  //namespace pulsar

#endif