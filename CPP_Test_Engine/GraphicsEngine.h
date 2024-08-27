#pragma once
#include<d3d11.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	// Initialize graphic engine
	bool Init();
	//Release all loaded resources
	bool Release();
	static GraphicsEngine* Get();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;
};

