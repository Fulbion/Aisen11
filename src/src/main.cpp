#include "App/AppWindow.hpp"
#include "Engine/Input/InputSystem.hpp"

int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
	}

	catch (const std::exception& e)
	{
		return EXIT_FAILURE;
	}

	{
		AppWindow app;

		if (app.init())
		{
			while (app.isRunning())
			{
				app.broadcast();
			}
		}
	}

	GraphicsEngine::release();
	InputSystem::release();

	return EXIT_SUCCESS;
}