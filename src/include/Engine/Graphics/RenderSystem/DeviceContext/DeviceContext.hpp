#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext, RenderSystem* system);
	~DeviceContext();

	void clearRenderTargetColor(const SwapChainPtr& swapChain, float red, float green, float blue, float alpha);
	void setVertexBuffer(const VertexBufferPtr& vertexBuffer);
	void setIndexBuffer(const IndexBufferPtr& indexBuffer);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void setViewportSize(UINT width, UINT height);
	void setVertexShader(const VertexShaderPtr& vertexShader);
	void setPixelShader(const PixelShaderPtr& pixelShader);
	void setTexture(const VertexShaderPtr& vertexShader, const TexturePtr& texture);
	void setTexture(const PixelShaderPtr& pixelShader, const TexturePtr& texture);
	void setConstantBuffer(const VertexShaderPtr& vertexShader, const ConstantBufferPtr& buffer);
	void setConstantBuffer(const PixelShaderPtr& pixelShader, const ConstantBufferPtr& buffer);

private:
	ID3D11DeviceContext* m_deviceContext;
	RenderSystem* m_system = nullptr;

	friend class ConstantBuffer;
};
