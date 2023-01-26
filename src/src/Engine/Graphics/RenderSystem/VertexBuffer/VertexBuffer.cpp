#include <exception>

#include "Engine/Graphics/RenderSystem/VertexBuffer/VertexBuffer.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"

VertexBuffer::VertexBuffer(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, size_t sizeByteShader, RenderSystem* system) :
	m_layout(0),
	m_buffer(0),
	m_system(system)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeVertex * sizeList;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = listVertices;

	m_sizeVertex = sizeVertex;
	m_sizeList = sizeList;

	if (FAILED(m_system->m_d3dDevice->CreateBuffer(&bufferDesc, &initData, &m_buffer)))
	{
		throw std::exception("VertexBuffer: failed to create");
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA ,0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA ,0 },
	};

	UINT sizeLayout = ARRAYSIZE(layout);

	if (FAILED(m_system->m_d3dDevice->CreateInputLayout(layout, sizeLayout, shaderByteCode, sizeByteShader, &m_layout)))
	{
		throw std::exception("VertexBuffer: failed to create");
	}
}

VertexBuffer::~VertexBuffer()
{
	m_layout->Release();
	m_buffer->Release();
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->m_sizeList;
}
