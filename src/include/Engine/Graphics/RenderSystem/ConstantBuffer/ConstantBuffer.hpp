#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class ConstantBuffer
{
public:
	ConstantBuffer(void* buffer, UINT sizeBuffer, RenderSystem* system);
	~ConstantBuffer();
	void update(DeviceContextPtr context, void* buffer);

private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};
