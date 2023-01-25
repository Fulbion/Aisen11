#pragma once

#include <set>
#include <unordered_set>
#include <Windows.h>

#include "Engine/Input/InputListener.hpp"

class InputSystem
{
public:
	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void setCursorPosition(const Vector2i& position);
	void showCursor(bool show);

	static InputSystem* get();
	static void create();
	static void release();

private:
	InputSystem();
	~InputSystem();

	static InputSystem* m_system;

	std::unordered_set<InputListener*> m_setListeners;
	BYTE m_keysState[256] = {};
	BYTE m_oldKeysState[256] = {};

	Vector2i m_oldMousePosition;
	bool m_firstTime = true;
};
