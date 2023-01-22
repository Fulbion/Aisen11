#include <exception>

#include "Engine/Graphics/RenderSystem/PixelShader/PixelShader.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"

PixelShader::PixelShader(const void* shaderByteCode, size_t byteCodeSize, RenderSystem* system) :
	m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3dDevice->CreatePixelShader(shaderByteCode, byteCodeSize, nullptr, &m_ps)))
		throw std::exception("PixelShader: failed to create");
}

PixelShader::~PixelShader()
{
	m_ps->Release();
}
