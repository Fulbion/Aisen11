#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext, RenderSystem* system);
	~DeviceContext();

	void clearRenderTargetColor(SwapChainPtr swapChain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBufferPtr vertexBuffer);
	void setIndexBuffer(IndexBufferPtr indexBuffer);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void setViewportSize(UINT width, UINT height);
	void setVertexShader(VertexShaderPtr vertexShader);
	void setPixelShader(PixelShaderPtr pixelShader);
	void setConstantBuffer(VertexShaderPtr vertexShader, ConstantBufferPtr buffer);
	void setConstantBuffer(PixelShaderPtr pixelShader, ConstantBufferPtr buffer);

private:
	ID3D11DeviceContext* m_deviceContext;
	RenderSystem* m_system = nullptr;

	friend class ConstantBuffer;
};
