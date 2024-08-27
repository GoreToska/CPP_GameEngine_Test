#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context) {}

DeviceContext::~DeviceContext() {}

bool DeviceContext::Release()
{
	m_device_context->Release();
	delete this;
	return true;
}

bool DeviceContext::ClearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a)
{
	FLOAT clear_color[] = { r,g,b,a };
	m_device_context->ClearRenderTargetView(swapChain->m_render_target_view, clear_color);
	return true;
}
