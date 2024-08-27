#include "GraphicsEngine.h"
#include "SwapChain.h"


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
	for (UINT driver_type_index = 0; driver_type_index < number_of_driver_types; driver_type_index)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			number_of_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		if (SUCCEEDED(result))
			break;

		driver_type_index++;
	}

	if (FAILED(result))
	{
		return false;
	}


	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool GraphicsEngine::Release()
{
	m_imm_context->Release();
	m_d3d_device->Release();
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	return true;
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
