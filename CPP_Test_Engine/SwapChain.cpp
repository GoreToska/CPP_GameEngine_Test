#include "SwapChain.h"
#include "GraphicsEngine.h"
#include<iostream>

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

bool SwapChain::Init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::Get()->m_d3d_device;
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	// create the swap chain for current window
	HRESULT result = GraphicsEngine::Get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(result))
		return false;

	return true;
}

bool SwapChain::Release()
{
	//m_swap_chain->Release();
	delete this;
	return true;
}
