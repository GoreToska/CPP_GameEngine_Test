#pragma once
#include<d3d11.h>
#include "SwapChain.h"
#include "VertexBuffer.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();

	bool Release();
	void ClearRenderTargetColor(SwapChain* swapChain,float r, float g, float b, float a);
	void SetVertexBuffer(VertexBuffer* vertex_buffer);
	void DrawTriangle(UINT vertex_count, UINT start_vertex_index);
	void SetViewportSize(UINT width, UINT height);

private:
	ID3D11DeviceContext* m_device_context;
};

