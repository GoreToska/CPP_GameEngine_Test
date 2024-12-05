#pragma once
#include "Window.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Унаследовано через Window
	void OnCreate() override;
	void OnUpdate() override;
	void OnDestroy() override;

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vertex_buffer;
};

