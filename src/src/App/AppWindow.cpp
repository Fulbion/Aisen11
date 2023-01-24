#include "App/AppWindow.hpp"
#include <Windows.h>

struct Vertex
{
	float3 position;
	float3 color;
	float3 color1;
};

__declspec(align(16))
struct constant
{
	float4x4 m_world;
	float4x4 m_view;
	float4x4 m_projection;
	UINT m_angle;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::update()
{
	constant cc;
	cc.m_angle = GetTickCount();

	float4x4 temp;

	m_deltaPos += m_deltaTime / 10.0f;
	if (m_deltaPos > 1.0f) m_deltaPos = 0;

	m_deltaScale += m_deltaTime / 0.5f;

	cc.m_world.setIdentity();

	float4x4 worldCamera;
	worldCamera.setIdentity();

	temp.setIdentity();
	temp.rotateX(m_rotationX);
	worldCamera *= temp;

	temp.setIdentity();
	temp.rotateY(m_rotationY);
	worldCamera *= temp;

	Vector3f newPosition = m_worldCamera.getTranslation() + worldCamera.getZDirection() * (m_forward * 0.025f);
	newPosition = newPosition + worldCamera.getXDirection() * (m_rightward * 0.025f);

	worldCamera.translate(newPosition);
	m_worldCamera = worldCamera;
	worldCamera.inverse();

	cc.m_view = worldCamera;
	
	// cc.m_projection.setOrthoLH
	// (
	// 	(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
	// 	(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
	// 	-4.0f,
	// 	4.0f
	// );

	UINT width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	UINT height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	cc.m_projection.setPrespectiveFovLH(degToRad(90), ((float)width / (float)height), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onCreate()
{
	Window::onCreate();

	UINT width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	UINT height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;
	InputSystem::get()->setCursorPosition(Vector2i(width / 2.0f, height / 2.0f));

	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);
	
	TexturePtr m_brickTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"resources/images/textures/brick.png");

	RECT rc = this->getClientWindowRect();
	m_swapChain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_worldCamera.translate(Vector3f(0, 0, -2));

	Vertex vertexList[] =
	{
		{ float3(-0.5f, -0.5f, -0.5f),  float3(1, 1, 0),  float3(0.33f, 0.33f, 0) },
		{ float3(-0.5f, 0.5f, -0.5f),   float3(0, 1, 1),  float3(0, 0.33f, 0.33f) },
		{ float3(0.5f, 0.5f, -0.5f),    float3(1, 0, 1),  float3(0.33f, 0, 0.33f) },
		{ float3(0.5f, -0.5f, -0.5f),   float3(1, 1, 1),  float3(0.33f, 0.33f, 0.33f) },
		
		{ float3(0.5f, -0.5f, 0.5f),    float3(1, 1, 0),  float3(0.33f, 0.33f, 0) },
		{ float3(0.5f, 0.5f, 0.5f),     float3(0, 1, 1),  float3(0, 0.33f, 0.33f) },
		{ float3(-0.5f, 0.5f, 0.5f),    float3(1, 0, 1),  float3(0.33f, 0, 0.33f) },
		{ float3(-0.5f, -0.5f, 0.5f),   float3(1, 1, 1),  float3(0.33f, 0.33f, 0.33f) }
	};

	UINT sizeList = ARRAYSIZE(vertexList);

	UINT indexList[] =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		1, 6, 5,
		5, 2, 1,

		7, 0, 3,
		3, 4, 7,

		3, 2, 5,
		5, 4, 3,

		7, 6, 1,
		1, 0, 7
	};

	UINT sizeIndexList = ARRAYSIZE(indexList);
	
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(indexList, sizeIndexList);

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"resources/shaders/VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shaderByteCode, sizeShader);
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertexList, sizeof(Vertex), sizeList, shaderByteCode, sizeShader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"resources/shaders/PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swapChain,
		0.1f, 0.1f, 0.1f, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	m_swapChain->present(true);

	m_oldTime = m_newTime;
	m_newTime = GetTickCount();

	m_deltaTime = (m_oldTime) ? ((m_newTime - m_oldTime) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	// delete m_vb;
	// delete m_ib;
	// delete m_cb;
	// delete m_swapChain;
	// delete m_vs;
	// delete m_ps;
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyPressed(int key)
{
	if (key == 'Z')
	{
		m_forward = 1.0f;
	}

	if (key == 'S')
	{
		m_forward = -1.0f;
	}

	if (key == 'Q')
	{
		m_rightward = -1.0f;
	}

	if (key == 'D')
	{
		m_rightward = 1.0f;
	}
}

void AppWindow::onKeyReleased(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Vector2i& mousePosition)
{
	UINT width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	UINT height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;

	m_rotationX += (mousePosition.y - (height / 2.0f)) * m_deltaTime * 0.5f;
	m_rotationY += (mousePosition.x - (width / 2.0f)) * m_deltaTime * 0.5f;

	InputSystem::get()->setCursorPosition(Vector2i(width / 2.0f, height / 2.0f));
}

void AppWindow::onMouseLeftButtonPressed(const Vector2i& MousePosition)
{
}

void AppWindow::onMouseLeftButtonReleased(const Vector2i& MousePosition)
{
}

void AppWindow::onMouseMiddleButtonPressed(const Vector2i& MousePosition)
{
}

void AppWindow::onMouseMiddleButtonReleased(const Vector2i& MousePosition)
{
}

void AppWindow::onMouseRightButtonPressed(const Vector2i& MousePosition)
{
}

void AppWindow::onMouseRightButtonReleased(const Vector2i& MousePosition)
{
}
