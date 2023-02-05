#include "Engine/Graphics/ResourceManager/TextureManager/TextureManager.hpp"
#include "Engine/Graphics/ResourceManager/TextureManager/Texture.hpp"

TextureManager::TextureManager() :
	ResourceManager()
{
}

TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* filePath)
{
	return std::static_pointer_cast<Texture>(createResourceFromFile(filePath));
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
	Texture* texture = nullptr;

	try
	{
		texture = new Texture(filePath);
	}

	catch (const std::exception& e)
	{

	}

	return texture;
}
