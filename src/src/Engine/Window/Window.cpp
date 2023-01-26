#include "Engine/Window/Window.hpp"

LRESULT __stdcall WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        
        break;
    }

    case WM_SETFOCUS:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (window) window->onFocus();
        break;
    }

    case WM_KILLFOCUS:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->onKillFocus();
        break;
    }

    case WM_DESTROY:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    }

    default:
        return ::DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return NULL;
}

Window::Window()
{
    const wchar_t CLASS_NAME[] = L"Aisen";

    WNDCLASSEX wc = { };
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpfnWndProc = &WndProc;
    wc.lpszClassName = CLASS_NAME;
    wc.lpszMenuName = L"";
    wc.style = NULL;

    if (!RegisterClassEx(&wc))
        throw std::exception("Window failed to initialize.");

    RECT rc = { 0, 0, 1600, 900 };
    AdjustWindowRect(&rc, WS_TILEDWINDOW, false);

    m_hwnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        CLASS_NAME,
        L"Aisen 11",
        WS_TILEDWINDOW,

        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,

        NULL,
        NULL,
        NULL,
        NULL
    );

    if (!m_hwnd)
        throw std::exception("Window failed to initialize.");

    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

    m_isRunning = true;
}

Window::~Window()
{
    // if (!DestroyWindow(m_hwnd))
    //     throw std::exception("Window failed to destroy.");
}

bool Window::broadcast()
{
    MSG msg;

    if (!this->m_isInitialized)
    {
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
        this->onCreate();
        this->m_isInitialized = true;
    }

    this->onUpdate();
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Sleep(0);

    return true;
}

bool Window::isRunning()
{
    if (m_isRunning)
        broadcast();
    return m_isRunning;
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    GetClientRect(this->m_hwnd, &rc);
    return rc;
}

// void Window::setHWND(HWND hwnd)
// {
//     this->m_hwnd = hwnd;
// }

void Window::onDestroy()
{
    m_isRunning = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}
