#include <DirectXTex.h>

#include "Engine/Graphics/ResourceManager/TextureManager/Texture.hpp"
#include "Engine/Graphics/RenderSystem/DeviceContext/DeviceContext.hpp"
#include "Engine/Graphics/GraphicsEngine.hpp"

Texture::Texture(const wchar_t* fullPath) :
	Resource(fullPath)
{
	DirectX::ScratchImage imageData;
	HRESULT hr = DirectX::LoadFromWICFile(fullPath, DirectX::WIC_FLAGS_NONE, nullptr, imageData);

	if (SUCCEEDED(hr))
	{
		hr = DirectX::CreateTexture(GraphicsEngine::get()->getRenderSystem()->m_d3dDevice, imageData.GetImages(), imageData.GetImageCount(), imageData.GetMetadata(), &m_texture);
		
		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = imageData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::get()->getRenderSystem()->m_d3dDevice->CreateShaderResourceView(m_texture, &desc, &m_shaderResourceView);
	}

	else
	{
		throw std::exception("Texture not created successfully");
	}
}

Texture::~Texture()
{
	m_texture->Release();
}
