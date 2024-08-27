#pragma once
#include<d3d11.h>

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	// Initialize graphic engine
	bool Init();
	//Release all loaded resources
	bool Release();
	static GraphicsEngine* Get();
	SwapChain* CreateSwapChain();
	DeviceContext* m_imm_device_context;
	DeviceContext* GetImmediateDeviceContext();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	friend class SwapChain;
};

