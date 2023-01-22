#pragma once

#include <d3d11.h>

#include "Engine/Prerequisites.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool init();
	bool release();

	RenderSystem* getRenderSystem();
	static GraphicsEngine* get();

private:
	RenderSystem* m_renderSystem = nullptr;
};
