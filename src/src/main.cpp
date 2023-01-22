#include "App/AppWindow.hpp"

int main()
{
	AppWindow app;
	
	if (app.init())
	{
		while (app.isRunning())
		{
			app.broadcast();
		}
	}

	return EXIT_SUCCESS;
}