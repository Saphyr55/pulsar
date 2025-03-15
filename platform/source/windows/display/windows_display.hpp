#pragma once

#include "display/display.hpp"

namespace pulsar {

class WindowsDisplay : public Display {
public:
    static Display& Get();

    virtual WindowHandle CreateWindowHandle(const WindowStatues& window_statues) override;

    virtual WindowStatues QueryWindowStatues(WindowHandle window) override;

    virtual void Show(WindowHandle window) override;

    virtual void Hide(WindowHandle window) override;

private:
    
};

}