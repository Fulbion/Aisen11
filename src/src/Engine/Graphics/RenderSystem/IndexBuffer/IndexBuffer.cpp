#include <exception>

#include "Engine/Graphics/RenderSystem/IndexBuffer/IndexBuffer.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"

IndexBuffer::IndexBuffer(void* listIndices, UINT sizeList, RenderSystem* system) :
	m_buffer(0),
	m_system(system)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = 4 * sizeList;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = listIndices;

	m_sizeList = sizeList;

	if (FAILED(m_system->m_d3dDevice->CreateBuffer(&bufferDesc, &initData, &m_buffer)))
	{
		throw std::exception("IndexBuffer: failed to create");
	}
}

IndexBuffer::~IndexBuffer()
{
	m_buffer->Release();
}

UINT IndexBuffer::getSizeIndexList()
{
	return this->m_sizeList;
}
