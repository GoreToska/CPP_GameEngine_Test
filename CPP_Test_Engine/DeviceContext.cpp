#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) : m_device_context(device_context) {}

DeviceContext::~DeviceContext() {}

bool DeviceContext::Release()
{
	m_device_context->Release();
	delete this;
	return true;
}

void DeviceContext::ClearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a)
{
	FLOAT clear_color[] = { r,g,b,a };
	m_device_context->ClearRenderTargetView(swapChain->m_render_target_view, clear_color);
	m_device_context->OMSetRenderTargets(1, &swapChain->m_render_target_view, NULL);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_vertex_size;
	UINT offset = 0;

	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(vertex_buffer->m_input_layout);
}

void DeviceContext::DrawTriangle(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::SetViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_device_context->RSSetViewports(1, &viewport);
}
