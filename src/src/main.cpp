#include "App/AppWindow.hpp"
#include "Engine/Input/InputSystem.hpp"

int main()
{
	GraphicsEngine::create();
	InputSystem::create();

	try
	{
		AppWindow app;

		while (app.isRunning())
		{
		}
	}

	catch (const std::exception& e)
	{
		InputSystem::release();
		GraphicsEngine::release();
		return EXIT_FAILURE;
	}

	InputSystem::release();
	GraphicsEngine::release();

	return EXIT_SUCCESS;
}