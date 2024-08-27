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
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	GraphicsEngine::Get()->Release();
}
