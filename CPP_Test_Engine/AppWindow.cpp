#include "AppWindow.h"


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::OnCreate()
{
	Window::OnCreate();
	GraphicsEngine::Get()->Init();
	m_swap_chain = GraphicsEngine::Get()->CreateSwapChain();

	RECT rect = this->GetClientWindowRect();

	m_swap_chain->Init(this->m_hwnd, rect.right - rect.left, rect.top - rect.bottom);
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();

	m_swap_chain->Release();
	GraphicsEngine::Get()->Release();
}
