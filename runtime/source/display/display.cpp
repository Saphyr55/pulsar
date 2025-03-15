#include "defines.hpp"
#include "display/display.hpp"

namespace pulsar {

Display* DisplayProvider::display_ = nullptr;

Display* DisplayProvider::GetDisplay() {
    return display_;
}

void DisplayProvider::SetDisplay(Display* display) {
    display_ = display;
}

Display& Display::Get() {
    Display* display = DisplayProvider::GetDisplay();
    PCHECK_MSG(display != nullptr, "Display is not initialized.");
    return *display;
}

}  //namespace pulsar