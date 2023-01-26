#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	SwapChainPtr createSwapChain(HWND hwnd, UINT width, UINT height);
	DeviceContextPtr getImmediateDeviceContext();
	VertexBufferPtr createVertexBuffer(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, size_t sizeByteShader);
	IndexBufferPtr createIndexBuffer(void* listIndices, UINT sizeList);
	ConstantBufferPtr createConstantBuffer(void* buffer, UINT sizeBuffer);
	VertexShaderPtr createVertexShader(const void* shaderByteCode, size_t byteCodeSize);
	PixelShaderPtr createPixelShader(const void* shaderByteCode, size_t byteCodeSize);

	bool compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	bool compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader();

private:
	DeviceContextPtr m_immDeviceContext;

	ID3D11Device* m_d3dDevice;
	D3D_FEATURE_LEVEL m_featureLevel;

	IDXGIDevice* m_dxgiDevice;
	IDXGIAdapter* m_dxgiAdapter;
	IDXGIFactory* m_dxgiFactory;
	ID3D11DeviceContext* m_immContext;

	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class Texture;
};
