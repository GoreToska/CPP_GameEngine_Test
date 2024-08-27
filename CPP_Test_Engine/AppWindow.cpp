#include "AppWindow.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"


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
	m_swap_chain->Init(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top);
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, 0.1f,0.5f,1,1);
	m_swap_chain->Present(false);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();

	m_swap_chain->Release();
	GraphicsEngine::Get()->Release();
}
