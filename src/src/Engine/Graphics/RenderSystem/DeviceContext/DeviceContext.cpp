#include "Engine/Graphics/RenderSystem/DeviceContext/DeviceContext.hpp"
#include "Engine/Graphics/RenderSystem/SwapChain/SwapChain.hpp"
#include "Engine/Graphics/RenderSystem/VertexBuffer/VertexBuffer.hpp"
#include "Engine/Graphics/RenderSystem/IndexBuffer/IndexBuffer.hpp"
#include "Engine/Graphics/RenderSystem/ConstantBuffer/ConstantBuffer.hpp"
#include "Engine/Graphics/RenderSystem/VertexShader/VertexShader.hpp"
#include "Engine/Graphics/RenderSystem/PixelShader/PixelShader.hpp"
#include "Engine/Graphics/ResourceManager/TextureManager/Texture.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext, RenderSystem* system) :
	m_deviceContext(deviceContext),
	m_system(system)
{
}

DeviceContext::~DeviceContext()
{
	m_deviceContext->Release();
}

void DeviceContext::clearRenderTargetColor(const SwapChainPtr& swapChain, float red, float green, float blue, float alpha)
{
	FLOAT clearColor[] = { red, green, blue, alpha };
	m_deviceContext->ClearRenderTargetView(swapChain->m_rtv, clearColor);
	m_deviceContext->OMSetRenderTargets(1, &swapChain->m_rtv, NULL);
}

void DeviceContext::setVertexBuffer(const VertexBufferPtr& vertexBuffer)
{
	UINT stride = vertexBuffer->m_sizeVertex;
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->m_buffer, &stride, &offset);
	m_deviceContext->IASetInputLayout(vertexBuffer->m_layout);
}

void DeviceContext::setIndexBuffer(const IndexBufferPtr& indexBuffer)
{
	m_deviceContext->IASetIndexBuffer(indexBuffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_deviceContext->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_deviceContext->RSSetViewports(1, &vp);
}

void DeviceContext::setVertexShader(const VertexShaderPtr& vertexShader)
{
	m_deviceContext->VSSetShader(vertexShader->m_vs, nullptr, 0);
}

void DeviceContext::setPixelShader(const PixelShaderPtr& pixelShader)
{
	m_deviceContext->PSSetShader(pixelShader->m_ps, nullptr, 0);
}

void DeviceContext::setTexture(const VertexShaderPtr& vertexShader, const TexturePtr& texture)
{
	m_deviceContext->VSSetShaderResources(0, 1, &texture->m_shaderResourceView);
}

void DeviceContext::setTexture(const PixelShaderPtr& pixelShader, const TexturePtr& texture)
{
	m_deviceContext->PSSetShaderResources(0, 1, &texture->m_shaderResourceView);
}

void DeviceContext::setConstantBuffer(const VertexShaderPtr& vertexShader, const ConstantBufferPtr& buffer)
{
	m_deviceContext->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

void DeviceContext::setConstantBuffer(const PixelShaderPtr& pixelShader, const ConstantBufferPtr& buffer)
{
	m_deviceContext->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
}
