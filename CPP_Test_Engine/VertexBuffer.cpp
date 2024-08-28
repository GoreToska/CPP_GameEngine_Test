#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include <iostream>
#include "Logger.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
}

bool VertexBuffer::Release()
{
	return true;
}

bool VertexBuffer::Load(void* list_vertices, UINT vertex_size, UINT list_size)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = vertex_size * list_size;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_vertex_size = vertex_size;
	m_list_size = list_size;

	HRESULT result = GraphicsEngine::Get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer);

	if (FAILED(result))
	{
		Logger::SendError("Can't create buffer", __FILE__, __LINE__);
		return false;
	}

	return true;
}
