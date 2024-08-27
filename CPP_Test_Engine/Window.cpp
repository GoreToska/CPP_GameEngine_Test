#include "Window.h"


Window::Window() : m_hwnd(NULL)
{
}

Window::~Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Start events with new window created
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->SetHWND(hwnd);
		window->OnCreate();

		break;
	}
	case WM_DESTROY:
	{
		// Start events with windows closed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::Init()
{
	// create winwow params
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;


	// create window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX App",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	if (!m_hwnd)
		return false;

	// show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_is_running = true;
	return true;
}

bool Window::Release()
{
	// destroy the window
	
	if (!m_hwnd)
		return false;

	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::Broadcast()
{
	MSG msg;

	this->OnUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(0);

	return true;
}

bool Window::IsRunning()
{
	return m_is_running;
}

RECT Window::GetClientWindowRect()
{
	RECT rect;
	::GetClientRect(this->m_hwnd, &rect);
	
	return rect;
}

void Window::SetHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
	m_is_running = false;
}
