#pragma once
#include"Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"

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
};

