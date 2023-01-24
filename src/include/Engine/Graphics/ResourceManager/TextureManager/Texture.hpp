#pragma once

#include <d3d11.h>

#include "Engine/Graphics/ResourceManager/Resource.hpp"

class Texture :
	public Resource
{
public:
	Texture(const wchar_t* fullPath);
	~Texture();

private:
	ID3D11Resource* m_texture = nullptr;
};
