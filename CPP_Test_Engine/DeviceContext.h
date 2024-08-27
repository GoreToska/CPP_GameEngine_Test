#pragma once
#include<d3d11.h>
#include "SwapChain.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	bool Release();
	bool ClearRenderTargetColor(SwapChain* swapChain,float r, float g, float b, float a);

private:
	ID3D11DeviceContext* m_device_context;
};

