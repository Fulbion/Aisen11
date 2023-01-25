#include "Engine/Input/InputSystem.hpp"

InputSystem* InputSystem::m_system = nullptr;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	InputSystem::m_system = nullptr;
}

void InputSystem::update()
{
	POINT currentMousePosition = {};
	GetCursorPos(&currentMousePosition);

	if (m_firstTime)
	{
		m_oldMousePosition = Vector2i(currentMousePosition.x, currentMousePosition.y);
		m_firstTime = false;
	}

	if (currentMousePosition.x != m_oldMousePosition.x || currentMousePosition.y != m_oldMousePosition.y)
	{
		std::unordered_set<InputListener*>::iterator it = m_setListeners.begin();

		while (it != m_setListeners.end())
		{
			(*it)->onMouseMove(Vector2i(currentMousePosition.x, currentMousePosition.y));
			it++;
		}
	}

	m_oldMousePosition = Vector2i(currentMousePosition.x, currentMousePosition.y);

	if (GetKeyboardState(m_keysState))
	{
		for (UINT i = 0; i < 256; i++)
		{
			if (m_keysState[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = m_setListeners.begin();

				while (it != m_setListeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keysState[i] != m_oldKeysState[i])
							(*it)->onMouseLeftButtonPressed(Vector2i(currentMousePosition.x, currentMousePosition.y));
					}

					else if (i == VK_MBUTTON)
					{
						if (m_keysState[i] != m_oldKeysState[i])
							(*it)->onMouseMiddleButtonPressed(Vector2i(currentMousePosition.x, currentMousePosition.y));
					}

					else if (i == VK_RBUTTON)
					{
						if (m_keysState[i] != m_oldKeysState[i])
							(*it)->onMouseRightButtonPressed(Vector2i(currentMousePosition.x, currentMousePosition.y));
					}

					(*it)->onKeyPressed(i);
					it++;
				}
			}

			else
			{
				if (m_keysState[i] != m_oldKeysState[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_setListeners.begin();

					while (it != m_setListeners.end())
					{
						if (i == VK_LBUTTON)
						{
							(*it)->onMouseLeftButtonReleased(Vector2i(currentMousePosition.x, currentMousePosition.y));
						}

						else if (i == VK_MBUTTON)
						{
							(*it)->onMouseMiddleButtonReleased(Vector2i(currentMousePosition.x, currentMousePosition.y));
						}

						else if (i == VK_RBUTTON)
						{
							(*it)->onMouseRightButtonReleased(Vector2i(currentMousePosition.x, currentMousePosition.y));
						}

						(*it)->onKeyReleased(i);
						it++;
					}
				}
			}
		}

		memcpy(m_oldKeysState, m_keysState, sizeof(BYTE) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_setListeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	std::unordered_set<InputListener*>::iterator it = m_setListeners.find(listener);

	if (it != m_setListeners.end())
	{
		m_setListeners.erase(it);
	}
}

void InputSystem::setCursorPosition(const Vector2i& position)
{
	SetCursorPos(position.x, position.y);
}

void InputSystem::showCursor(bool show)
{
	ShowCursor(show);
}

InputSystem* InputSystem::get()
{
	return m_system;
}

void InputSystem::create()
{
	if (InputSystem::m_system) return;
	InputSystem::m_system = new InputSystem();
}

void InputSystem::release()
{
	if (!InputSystem::m_system) return;
	delete InputSystem::m_system;
}
