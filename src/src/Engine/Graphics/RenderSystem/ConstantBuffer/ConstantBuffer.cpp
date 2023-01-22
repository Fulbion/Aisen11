#include <exception>

#include "Engine/Graphics/RenderSystem/ConstantBuffer/ConstantBuffer.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"
#include "Engine/Graphics/RenderSystem/DeviceContext/DeviceContext.hpp"

ConstantBuffer::ConstantBuffer(void* buffer, UINT sizeBuffer, RenderSystem* system) :
	m_system(system)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeBuffer;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = buffer;

	if (FAILED(m_system->m_d3dDevice->CreateBuffer(&bufferDesc, &initData, &m_buffer)))
	{
		throw std::exception("ConstantBuffer: failed to create");
	}
}

ConstantBuffer::~ConstantBuffer()
{
	if (m_buffer) m_buffer->Release();
}

void ConstantBuffer::update(DeviceContextPtr context, void* buffer)
{
	context->m_deviceContext->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}

