#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class PixelShader
{
public:
	PixelShader(const void* shaderByteCode, size_t byteCodeSize, RenderSystem* system);
	~PixelShader();

private:
	ID3D11PixelShader* m_ps;
	RenderSystem* m_system = nullptr;

	friend class RenderSystem;
	friend class DeviceContext;
};
