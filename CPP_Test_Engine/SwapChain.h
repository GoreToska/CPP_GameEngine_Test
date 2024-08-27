#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	bool Init(HWND hwnd, UINT width, UINT height);
	bool Release();

private:
	IDXGISwapChain* m_swap_chain;
};

