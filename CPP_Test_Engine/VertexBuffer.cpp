#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include <iostream>
#include "Logger.h"

VertexBuffer::VertexBuffer() : m_input_layout(0), m_buffer(0)
{
}

VertexBuffer::~VertexBuffer()
{
}

UINT VertexBuffer::GetVertexListSize()
{
	return this->m_list_size;
}

bool VertexBuffer::Release()
{
	m_input_layout->Release();
	delete this;
	return true;
}

bool VertexBuffer::Load(void* list_vertices, UINT vertex_size, UINT list_size, void* shader_byte_code, UINT byte_shader_size)
{
	if (m_buffer)
		m_buffer->Release();

	if (m_input_layout)
		m_input_layout->Release();

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

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// semantic name, semantic index, format, input slot, 
		// aligned byte offset, input slot class, instance data step rate

		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT layout_size = ARRAYSIZE(layout);

	result = GraphicsEngine::Get()->m_d3d_device->CreateInputLayout(layout, layout_size, shader_byte_code, byte_shader_size, &m_input_layout);

	if (FAILED(result))
	{
		Logger::SendError("Can't create input layout", __FILE__, __LINE__);
		return false;
	}

	return true;
}
