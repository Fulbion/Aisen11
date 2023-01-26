#pragma once

#include "Engine/Prerequisites.hpp"
#include "Engine/Window/Window.hpp"
#include "Engine/Input/InputListener.hpp"
#include "Engine/Input/InputSystem.hpp"
#include "Engine/Graphics/GraphicsEngine.hpp"
#include "Engine/Graphics/RenderSystem/RenderSystem.hpp"
#include "Engine/Graphics/RenderSystem/SwapChain/SwapChain.hpp"
#include "Engine/Graphics/RenderSystem/DeviceContext/DeviceContext.hpp"
#include "Engine/Graphics/RenderSystem/VertexBuffer/VertexBuffer.hpp"
#include "Engine/Graphics/RenderSystem/IndexBuffer/IndexBuffer.hpp"
#include "Engine/Graphics/RenderSystem/ConstantBuffer/ConstantBuffer.hpp"
#include "Engine/Graphics/RenderSystem/VertexShader/VertexShader.hpp"
#include "Engine/Graphics/RenderSystem/PixelShader/PixelShader.hpp"
#include "Engine/Math/ConvertAngles.hpp"
#include "Engine/Math/Vector2D.hpp"
#include "Engine/Math/Vector3D.hpp"
#include "Engine/Math/Vector4D.hpp"
#include "Engine/Math/Matrix4x4.hpp"

class AppWindow :
	public Window,
	public InputListener
{
public:
	AppWindow();
	~AppWindow();

	void update();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyPressed(int key) override;
	virtual void onKeyReleased(int key) override;
	
	virtual void onMouseMove(const Vector2i& mousePosition) override;

	virtual void onMouseLeftButtonPressed(const Vector2i& MousePosition) override;
	virtual void onMouseLeftButtonReleased(const Vector2i& MousePosition) override;
	virtual void onMouseMiddleButtonPressed(const Vector2i& MousePosition) override;
	virtual void onMouseMiddleButtonReleased(const Vector2i& MousePosition) override;
	virtual void onMouseRightButtonPressed(const Vector2i& MousePosition) override;
	virtual void onMouseRightButtonReleased(const Vector2i& MousePosition) override;

private:
	SwapChainPtr m_swapChain;
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
	ConstantBufferPtr m_cb;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	TexturePtr m_testTexture;
	
	float m_oldDelta = 0;
	float m_newDelta = 0;
	float m_deltaTime = 0;

	float m_deltaPos = 0;
	float m_deltaScale = 0;

	float m_rotationX = 0;
	float m_rotationY = 0;
	float m_rotationZ = 0;
	float m_scale = 1;
	float m_forward = 0.0f;
	float m_upward = 0.0f;
	float m_rightward = 0.0f;

	Matrix4x4<float> m_worldCamera;
};
