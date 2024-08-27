#pragma once
#include"Window.h"
#include "GraphicsEngine.h"


class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Унаследовано через Window
	void OnCreate() override;
	void OnUpdate() override;
	void OnDestroy() override;
};

