#pragma once

#include <unordered_set>
#include <Windows.h>

#include "Engine/Input/InputListener.hpp"

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Vector2i& position);
	void showCursor(bool show);

	static InputSystem* get();

private:
	std::unordered_set<InputListener*> m_setListeners;
	BYTE m_keysState[256] = {};
	BYTE m_oldKeysState[256] = {};

	Vector2i m_oldMousePosition;
	bool m_firstTime = true;
};
