#pragma once

#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	bool init();
	bool broadcast();
	bool release();

	bool isRunning();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	virtual void onCreate() {};
	virtual void onUpdate() {};
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

protected:
	HWND m_hwnd;
	bool m_isRunning;
};
