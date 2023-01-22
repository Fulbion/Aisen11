#include <exception>

#include "Engine/Graphics/RenderSystem/VertexShader/VertexShader.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"

VertexShader::VertexShader(const void* shaderByteCode, size_t byteCodeSize, RenderSystem* system) :
	m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3dDevice->CreateVertexShader(shaderByteCode, byteCodeSize, nullptr, &m_vs)))
		throw std::exception("VertexShader: failed to create");
}

VertexShader::~VertexShader()
{
	m_vs->Release();
}
