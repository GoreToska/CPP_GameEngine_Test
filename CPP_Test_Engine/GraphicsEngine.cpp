#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include <iostream>
#include "Logger.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::Init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT number_of_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT number_of_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT result = 0;

	for (UINT driver_type_index = 0; driver_type_index < number_of_driver_types;)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			number_of_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		if (SUCCEEDED(result))
			break;

		++driver_type_index;
	}

	if (FAILED(result))
	{
		Logger::SendError("Can't create device", __FILE__, __LINE__);
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool GraphicsEngine::Release()
{
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vs_blob)m_vs_blob->Release();
	if (m_ps_blob)m_ps_blob->Release();

	m_imm_device_context->Release();
	m_d3d_device->Release();
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	return true;
}

bool GraphicsEngine::CreateShaders()
{
	ID3DBlob* errblob = nullptr;
	std::cout << __FILE__<<"\n";
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vs_blob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_ps_blob, &errblob);
	m_d3d_device->CreateVertexShader(m_vs_blob->GetBufferPointer(), m_vs_blob->GetBufferSize(), nullptr, &m_vs);
	m_d3d_device->CreatePixelShader(m_ps_blob->GetBufferPointer(), m_ps_blob->GetBufferSize(), nullptr, &m_ps);

	return true;
}

bool GraphicsEngine::SetShaders()
{
	m_imm_context->VSSetShader(m_vs, nullptr, 0);
	m_imm_context->PSSetShader(m_ps, nullptr, 0);

	return true;
}

void GraphicsEngine::GetShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_vs_blob->GetBufferPointer();
	*size = (UINT)this->m_vs_blob->GetBufferSize();
}

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}


