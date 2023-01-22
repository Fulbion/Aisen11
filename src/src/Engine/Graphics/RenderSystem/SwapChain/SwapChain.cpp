#include <exception>

#include "Engine/Graphics/RenderSystem/SwapChain/SwapChain.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"

SwapChain::SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system) :
	m_system(system)
{
	ID3D11Device* device = m_system->m_d3dDevice;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = m_system->m_dxgiFactory->CreateSwapChain(device, &desc, &m_swapChain);

	if (FAILED(hr))
	{
		throw std::exception("SwapChain: failed to create");
	}

	ID3D11Texture2D* buffer = NULL;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		throw std::exception("SwapChain: failed to create");
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		throw std::exception("SwapChain: failed to create");
	}
}

SwapChain::~SwapChain()
{
	m_swapChain->Release();
}

bool SwapChain::present(bool vsync)
{
	m_swapChain->Present(vsync, NULL);

	return true;
}
