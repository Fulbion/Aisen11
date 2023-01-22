#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class IndexBuffer
{
public:
	IndexBuffer(void* listIndices, UINT sizeList, RenderSystem* system);
	~IndexBuffer();

	UINT getSizeIndexList();

private:
	UINT m_sizeList;

	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};
