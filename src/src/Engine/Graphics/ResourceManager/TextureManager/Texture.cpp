#include <DirectXTex.h>

#include "Engine/Graphics/ResourceManager/TextureManager/Texture.hpp"
#include "Engine/Graphics/GraphicsEngine.hpp"

Texture::Texture(const wchar_t* fullPath) :
	Resource(fullPath)
{
	DirectX::ScratchImage imageData;
	HRESULT hr = DirectX::LoadFromWICFile(fullPath, DirectX::WIC_FLAGS_NONE, nullptr, imageData);

	if (SUCCEEDED(hr))
	{
		hr = DirectX::CreateTexture(GraphicsEngine::get()->getRenderSystem()->m_d3dDevice, imageData.GetImages(), imageData.GetImageCount(), imageData.GetMetadata(), &m_texture);
	}

	else
	{
		throw std::exception("Texture not created successfully");
	}
}

Texture::~Texture()
{
}
