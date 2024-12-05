#pragma once
#include<d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	// Initialize graphic engine
	bool Init();
	//Release all loaded resources
	bool Release();
	bool CreateShaders();
	bool SetShaders();
	void GetShaderBufferAndSize(void** bytecode, UINT* size);
	static GraphicsEngine* Get();
	SwapChain* CreateSwapChain();
	DeviceContext* m_imm_device_context;
	DeviceContext* GetImmediateDeviceContext();
	VertexBuffer* CreateVertexBuffer();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3DBlob* m_vs_blob = nullptr;
	ID3DBlob* m_ps_blob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
	ID3D11DeviceContext* m_imm_context;

	friend class SwapChain;
	friend class VertexBuffer;
};

