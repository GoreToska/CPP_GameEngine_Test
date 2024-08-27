#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	bool Init(HWND hwnd, UINT width, UINT height);
	bool Release();
	bool Present(bool vsync);

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target_view;
	friend class DeviceContext;
};

