#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class VertexShader
{
public:
	VertexShader(const void* shaderByteCode, size_t byteCodeSize, RenderSystem* system);
	~VertexShader();

private:	
	ID3D11VertexShader* m_vs;
	RenderSystem* m_system = nullptr;

	friend class RenderSystem;
	friend class DeviceContext;
};
