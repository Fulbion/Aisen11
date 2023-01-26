#include <d3dcompiler.h>

#include "Engine/Graphics/GraphicsEngine.hpp"

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	m_renderSystem = new RenderSystem();
	m_textureManager = new TextureManager();
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_textureManager;
	delete m_renderSystem;
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine) throw std::exception("Graphics Engine already created");
	GraphicsEngine::m_engine = new GraphicsEngine();
}

void GraphicsEngine::release()
{
	if (!GraphicsEngine::m_engine) return;
	delete GraphicsEngine::m_engine;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_renderSystem;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_textureManager;
}
