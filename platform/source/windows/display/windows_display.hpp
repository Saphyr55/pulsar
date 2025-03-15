#pragma once

#ifdef _WIN32
#include <Windows.h>

#include "collection/hash_map.hpp"
#include "display/display.hpp"
#include "memory/shared_ref.hpp"
#include "windows/windows_app.hpp"


namespace pulsar {

struct WindowsWindowHandle {
    HWND hwnd;
    WNDCLASSEX wc;
};

class WindowsDisplay : public Display {
public:
    static Display& Get();

    virtual WindowHandle CreateWindowHandle(const WindowStatues& window_statues) override;

    virtual WindowStatues QueryWindowStatues(WindowHandle window) override;

    virtual void Show(WindowHandle window) override;

    virtual void Hide(WindowHandle window) override;

    virtual void Close(WindowHandle window) override;

    virtual bool IsValid(WindowHandle window) override {
        return window != INVALID_WINDOW_HANDLE || windows_.Contains(window);
    }
    
    virtual void PumpsEvents() override {
        RunMessageLoop();
    }

private:
    void RunMessageLoop() const;

public:
    WindowsDisplay(WindowsAppContext* context)
        : context_(context) {}

    ~WindowsDisplay() = default;

private:
    WindowsAppContext* context_;
    HashMap<WindowHandle, SharedRef<WindowsWindowHandle>> windows_;
};

}  //namespace pulsar

#endif
