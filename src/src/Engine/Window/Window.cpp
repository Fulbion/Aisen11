#include "Engine/Window/Window.hpp"

LRESULT __stdcall WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        Window* window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
        window->setHWND(hwnd);
        window->onCreate();
        break;
    }

    case WM_SETFOCUS:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->onFocus();
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
}

Window::~Window()
{
}

bool Window::init()
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
        return false;

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
        this
    );

    if (!m_hwnd)
        return false;

    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

    m_isRunning = true;

	return true;
}

bool Window::broadcast()
{
    MSG msg;

    this->onUpdate();
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Sleep(0);

    return true;
}

bool Window::release()
{
    if (!DestroyWindow(m_hwnd))
        return false;
        
	return true;
}

bool Window::isRunning()
{
    return m_isRunning;
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    GetClientRect(this->m_hwnd, &rc);
    return rc;
}

void Window::setHWND(HWND hwnd)
{
    this->m_hwnd = hwnd;
}

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
