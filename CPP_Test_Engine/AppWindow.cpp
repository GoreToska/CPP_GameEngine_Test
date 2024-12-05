#include "AppWindow.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"
#include "Types.cpp"
#include <iostream>

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

	Vertex vertex_list[] =
	{
		// x y z
		Vector3{-0.5f, -0.5f, 0.0f},
		Vector3{0.0f, 0.5f, 0.0f},
		Vector3{0.5f, -0.5f, 0.0f},


	};

	m_vertex_buffer = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT list_size = ARRAYSIZE(vertex_list);

	GraphicsEngine::Get()->CreateShaders();
	void* shader_byte_code = nullptr;
	UINT shader_size = 0;
	GraphicsEngine::Get()->GetShaderBufferAndSize(&shader_byte_code, &shader_size);
	m_vertex_buffer->Load(vertex_list, sizeof(Vertex), list_size, shader_byte_code, shader_size);
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->
		ClearRenderTargetColor(this->m_swap_chain, 0.1f, 0.5f, 1, 1);

	RECT rect = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewportSize(rect.right - rect.left, rect.bottom - rect.top);
	GraphicsEngine::Get()->SetShaders();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vertex_buffer);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangle(m_vertex_buffer->GetVertexListSize(), 0);

	m_swap_chain->Present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vertex_buffer->Release();
	m_swap_chain->Release();
	GraphicsEngine::Get()->Release();
}
