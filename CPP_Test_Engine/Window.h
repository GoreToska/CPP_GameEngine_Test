#pragma once
#include <Windows.h>


class Window
{
public:
	Window();
	~Window();
	bool Init();
	bool Release();
	bool Broadcast();
	bool IsRunning();

	//On window create event
	virtual void OnCreate() = 0;
	//On window update event
	virtual void OnUpdate() = 0;
	//On window destroy event
	virtual void OnDestroy();

private:
	HWND m_hwnd;
	bool m_is_running;
};
