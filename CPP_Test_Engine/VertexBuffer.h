#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	UINT GetVertexListSize();
	bool Release();
	bool Load(void* list_vertices, UINT vertex_size, UINT list_size, void* shader_byte_code, UINT byte_shader_size);

private:
	UINT m_vertex_size;
	UINT m_list_size;
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_input_layout;
	friend class DeviceContext;
};

