#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"
#include "Engine/Graphics/ResourceManager/TextureManager/TextureManager.hpp"

class GraphicsEngine
{
public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();

	static GraphicsEngine* get();

	static void create();
	static void release();

private:
	GraphicsEngine();
	~GraphicsEngine();

	RenderSystem* m_renderSystem = nullptr;
	TextureManager* m_textureManager = nullptr;
	static GraphicsEngine* m_engine;
};
