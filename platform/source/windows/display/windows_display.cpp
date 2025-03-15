#include "windows/display/windows_display.hpp"
#include <winuser.h>
#include "defines.hpp"
#include "display/display.hpp"
#include "memory/shared_ref.hpp"
#include "windows/windows_app.hpp"
#include "windows_display.hpp"

namespace pulsar {

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void WindowsDisplay::RunMessageLoop() const {
    MSG msg = {};
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void* WindowsDisplay::GetNativeWindowHandle(WindowHandle window) {
    PCHECK_MSG(IsValid(window), "Invalid window handle.");
    return reinterpret_cast<void*>(windows_[window]->hwnd);
}

WindowHandle WindowsDisplay::CreateWindowHandle(const WindowStatues& window_statues) {
    static WindowHandle last_window_handle = MAIN_WINDOW_HANDLE;

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = context_->hinstance;
    wc.lpszClassName = g_class_name;

    if (!RegisterClassEx(&wc)) {
        return false;
    }

    HWND hwnd = CreateWindowExA(
        0,                             // Optional window styles.
        g_class_name,                  // Window class.
        window_statues.title.Data(),  // Window text.
        WS_OVERLAPPEDWINDOW,           // Window style.
        // Position.
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        // Size.
        window_statues.width,
        window_statues.height,
        NULL,                 // Parent window.
        NULL,                 // Menu.
        context_->hinstance,  // Instance handle.
        NULL                  // Additional application data.
    );

    if (hwnd == NULL) {
        return INVALID_WINDOW_HANDLE;
    }

    auto window_handle = MakeSharedRef<WindowsWindowHandle>();
    window_handle->hwnd = hwnd;
    window_handle->wc = wc;

    return windows_.Insert(last_window_handle++, window_handle).key;
}

WindowStatues WindowsDisplay::QueryWindowStatues(WindowHandle window) {
    PCHECK_MSG(IsValid(window), "Invalid window handle.");
    RECT rect;
    GetWindowRect(windows_[window]->hwnd, &rect);

    WindowStatues window_statues;
    window_statues.width = rect.right - rect.left;
    window_statues.height = rect.bottom - rect.top;
    window_statues.x = rect.left;
    window_statues.y = rect.top;

    return window_statues;
}

void WindowsDisplay::Show(WindowHandle window) {
    PCHECK_MSG(IsValid(window), "Invalid window handle.");
    ShowWindow(windows_[window]->hwnd, SW_SHOW);
}

void WindowsDisplay::Hide(WindowHandle window) {
    PCHECK_MSG(IsValid(window), "Invalid window handle.");
    ShowWindow(windows_[window]->hwnd, SW_HIDE);
}

void WindowsDisplay::Close(WindowHandle window) {
    PCHECK_MSG(IsValid(window), "Invalid window handle.");
    DestroyWindow(windows_[window]->hwnd);
    windows_.Remove(window);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(EXIT_FAILURE);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
            return 0;
        }
        default:
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

}  //namespace pulsar