#include <d3dcompiler.h>

#include "Engine/Graphics/GraphicsEngine.hpp"

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	m_renderSystem = new RenderSystem();
	m_renderSystem->init();
	return true;
}

bool GraphicsEngine::release()
{
	m_renderSystem->release();
	delete m_renderSystem;
	return true;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_renderSystem;
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}