#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"

class SwapChain
{
public:
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system);
	~SwapChain();

	bool present(bool vSync);

private:
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;
	RenderSystem* m_system = nullptr;

	friend class DeviceContext;
};
