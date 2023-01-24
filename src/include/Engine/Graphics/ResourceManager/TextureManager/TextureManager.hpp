#pragma once

#include "Engine/Graphics/ResourceManager/ResourceManager.hpp"

class TextureManager :
	public ResourceManager
{
public:
	TextureManager();
	~TextureManager();

	TexturePtr createTextureFromFile(const wchar_t* filePath);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath) override;
};
