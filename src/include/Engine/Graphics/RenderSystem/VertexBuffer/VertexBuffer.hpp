#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class VertexBuffer
{
public:
	VertexBuffer(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, size_t sizeByteShader, RenderSystem* system);
	~VertexBuffer();

	UINT getSizeVertexList();

private:
	UINT m_sizeVertex;
	UINT m_sizeList;

	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};
