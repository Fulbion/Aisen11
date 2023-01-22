#pragma once

#include "Engine/Math/Vector2D.hpp"

class InputListener
{
public:
	InputListener()
	{
	}

	~InputListener()
	{
	}

	virtual void onKeyPressed(int key) = 0;
	virtual void onKeyReleased(int key) = 0;
	
	virtual void onMouseMove(const Vector2i& mousePosition) = 0;

	virtual void onMouseLeftButtonPressed(const Vector2i& MousePosition) = 0;
	virtual void onMouseLeftButtonReleased(const Vector2i& MousePosition) = 0;
	virtual void onMouseMiddleButtonPressed(const Vector2i& MousePosition) = 0;
	virtual void onMouseMiddleButtonReleased(const Vector2i& MousePosition) = 0;
	virtual void onMouseRightButtonPressed(const Vector2i& MousePosition) = 0;
	virtual void onMouseRightButtonReleased(const Vector2i& MousePosition) = 0;

private:

};
