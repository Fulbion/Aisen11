#include <iostream>
#include <d3dcompiler.h>
#include <exception>

#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"
#include "Engine/Graphics/RenderSystem/SwapChain/SwapChain.hpp"
#include "Engine/Graphics/RenderSystem/DeviceContext/DeviceContext.hpp"
#include "Engine/Graphics/RenderSystem/VertexBuffer/VertexBuffer.hpp"
#include "Engine/Graphics/RenderSystem/IndexBuffer/IndexBuffer.hpp"
#include "Engine/Graphics/RenderSystem/ConstantBuffer/ConstantBuffer.hpp"
#include "Engine/Graphics/RenderSystem/VertexShader/VertexShader.hpp"
#include "Engine/Graphics/RenderSystem/PixelShader/PixelShader.hpp"

RenderSystem::RenderSystem()
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	HRESULT hr = 0;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes;)
	{
		hr = D3D11CreateDevice(NULL, driverTypes[driverTypeIndex], NULL, NULL, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &m_d3dDevice, &m_featureLevel, &m_immContext);
		if (SUCCEEDED(hr))
			break;
		driverTypeIndex++;
	}

	if (FAILED(hr))
	{
		throw std::exception("RenderSystem failed to initialize");
	}

	m_immDeviceContext = std::make_shared<DeviceContext>(m_immContext, this);

	m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgiDevice);
	m_dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgiAdapter);
	m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgiFactory);
}

RenderSystem::~RenderSystem()
{
	// if (m_vs) m_vs->Release();
	// if (m_ps) m_ps->Release();

	if (m_vsblob) m_vsblob->Release();
	if (m_psblob) m_psblob->Release();

	m_dxgiDevice->Release();
	m_dxgiAdapter->Release();
	m_dxgiFactory->Release();

	m_d3dDevice->Release();
}

SwapChainPtr RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChainPtr sc = nullptr;

	try
	{
		sc = std::make_shared<SwapChain>(hwnd, width, height, this);
	}

	catch (const std::exception& e)
	{
		std::wcerr << e.what() << std::endl;
	}

	return sc;
}

DeviceContextPtr RenderSystem::getImmediateDeviceContext()
{
	return this->m_immDeviceContext;
}

VertexBufferPtr RenderSystem::createVertexBuffer(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, size_t sizeByteShader)
{
	VertexBufferPtr vb = nullptr;

	try
	{
		vb = std::make_shared<VertexBuffer>(listVertices, sizeVertex, sizeList, shaderByteCode, sizeByteShader, this);
	}

	catch (const std::exception& e)
	{
		std::wcerr << e.what() << std::endl;
	}

	return vb;
}

IndexBufferPtr RenderSystem::createIndexBuffer(void* listIndices, UINT sizeList)
{
	IndexBufferPtr ib = nullptr;

	try
	{
		ib = std::make_shared<IndexBuffer>(listIndices, sizeList, this);
	}

	catch (const std::exception& e)
	{
		std::wcerr << e.what() << std::endl;
	}

	return ib;
}

ConstantBufferPtr RenderSystem::createConstantBuffer(void* buffer, UINT sizeBuffer)
{
	ConstantBufferPtr cb = nullptr;

	try
	{
		cb = std::make_shared<ConstantBuffer>(buffer, sizeBuffer, this);
	}

	catch (const std::exception& e)
	{
		std::wcerr << e.what() << std::endl;
	}

	return cb;
}

VertexShaderPtr RenderSystem::createVertexShader(const void* shaderByteCode, size_t byteCodeSize)
{
	VertexShaderPtr vs = nullptr;

	try
	{
		vs = std::make_shared<VertexShader>(shaderByteCode, byteCodeSize, this);
	}

	catch (const std::exception& e)
	{
		std::wcerr << e.what() << std::endl;
	}

	return vs;
}

PixelShaderPtr RenderSystem::createPixelShader(const void* shaderByteCode, size_t byteCodeSize)
{
	PixelShaderPtr ps = nullptr;

	try
	{
		ps = std::make_shared<PixelShader>(shaderByteCode, byteCodeSize, this);
	}

	catch (const std::exception& e)
	{
		std::wcerr << e.what() << std::endl;
	}

	return ps;
}

bool RenderSystem::compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByte_code, size_t* byteCodeSize)
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &m_blob, &errorBlob)))
	{
		if (errorBlob) errorBlob->Release();
		return false;
	}

	*shaderByte_code = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();

	return true;
}

bool RenderSystem::compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &m_blob, &errorBlob)))
	{
		if (errorBlob) errorBlob->Release();
		return false;
	}

	*shaderByteCode = m_blob->GetBufferPointer();
	*byteCodeSize = m_blob->GetBufferSize();

	return true;
}

void RenderSystem::releaseCompiledShader()
{
	if (m_blob) m_blob->Release();
}