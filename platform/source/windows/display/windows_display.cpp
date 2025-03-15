#include "windows/display/windows_display.hpp"
#include "display/display.hpp"
#include "windows_display.hpp"

namespace pulsar {

Display& Display::Get() {
    static WindowsDisplay display;
    return display;
}

WindowHandle WindowsDisplay::CreateWindowHandle(const WindowStatues& window_statues) {
    return INVALID_WINDOW_HANDLE;
}

WindowStatues WindowsDisplay::QueryWindowStatues(WindowHandle window) {
    return WindowStatues();
}

void WindowsDisplay::Show(WindowHandle window) {

}

void WindowsDisplay::Hide(WindowHandle window) {

}

}  //namespace pulsar