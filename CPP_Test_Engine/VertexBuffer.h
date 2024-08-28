#pragma once
#include <d3d11.h>

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	bool Release();
	bool Load(void* list_vertices, UINT vertex_size, UINT list_size);

private:
	UINT m_vertex_size;
	UINT m_list_size;
	ID3D11Buffer* m_buffer;
};

