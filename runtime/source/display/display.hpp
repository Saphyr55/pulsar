#pragma once

#include <cstdint>

#include "runtime_exports.hpp"
#include "string/string_ref.hpp"


namespace pulsar {

struct PULSAR_RUNTIME_API WindowStatues {
    StringRef title;

    float width;
    float height;

    float x;
    float y;
};

using WindowHandle = uint32_t;

class PULSAR_RUNTIME_API Display {
public:
    static Display& Get();

    static constexpr WindowHandle INVALID_WINDOW_HANDLE = UINT32_MAX;
    static constexpr WindowHandle MAIN_WINDOW_HANDLE = 0;

    virtual WindowHandle CreateWindowHandle(const WindowStatues& window_statues) = 0;

    virtual WindowStatues QueryWindowStatues(WindowHandle window) = 0;

    virtual void Show(WindowHandle window) = 0;

    virtual void Hide(WindowHandle window) = 0;

    virtual void Close(WindowHandle window) = 0;

    virtual bool IsValid(WindowHandle window) = 0;

    virtual void PumpsEvents() = 0;

    virtual ~Display() = default;
};

class PULSAR_RUNTIME_API DisplayProvider {
public:
    static Display* GetDisplay();
    static void SetDisplay(Display* display);

private:
    static Display* display_;
};

}  //namespace pulsar
