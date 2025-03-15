#pragma once

#include <cstdint>
#include "defines.hpp"
#include "string/string.hpp"

namespace pulsar {

struct WindowStatues {
    String title;

    float width;
    float height;

    float x;
    float y;
};

using WindowHandle = uint32_t;

class Display {
public:
    static constexpr WindowHandle INVALID_WINDOW_HANDLE = UINT32_MAX;
    
    static Display& Get();

    virtual WindowHandle CreateWindowHandle(const WindowStatues& window_statues) = 0;

    virtual WindowStatues QueryWindowStatues(WindowHandle window) = 0;

    virtual void Show(WindowHandle window) = 0;

    virtual void Hide(WindowHandle window) = 0;
};

}  //namespace pulsar
