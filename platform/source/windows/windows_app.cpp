#ifdef _WIN32

#include <cstdlib>

#include "windows/windows_app.hpp"

namespace pulsar {

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool WindowsAppContextInitClass(WindowsAppContext* out_context) {

    out_context->wc = {};
    out_context->wc.cbSize = sizeof(WNDCLASSEX);
    out_context->wc.style = 0;
    out_context->wc.cbClsExtra = 0;
    out_context->wc.cbWndExtra = 0;
    out_context->wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    out_context->wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    out_context->wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    out_context->wc.lpszMenuName = NULL;
    out_context->wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    out_context->wc.lpfnWndProc = WindowProc;
    out_context->wc.hInstance = out_context->hinstance;
    out_context->wc.lpszClassName = AppClassName;

    if (!RegisterClassEx(&out_context->wc)) {
        return false;
    }

    return true;
}

bool WindowsAppContextInitWindow(const char* title, WindowsAppContext* out_context) {
    out_context->hwnd = CreateWindowEx(
        0,                    // Optional window styles.
        AppClassName,         // Window class
        title,                // Window text
        WS_OVERLAPPEDWINDOW,  // Window style
        // Size and position
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        800, 
        600,
        NULL,                    // Parent window
        NULL,                    // Menu
        out_context->hinstance,  // Instance handle
        NULL                     // Additional application data
    );

    return title != nullptr;
}

void WindowsAppContextShowWindow(const WindowsAppContext* context) {
    ShowWindow(context->hwnd, context->ncmd);
}

void WindowsAppContextRunMessageLoop(const WindowsAppContext* context) {
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
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

#endif