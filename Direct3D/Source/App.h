#pragma once
#include "WindowPrkotiny/Window.h"
#include "Utilities/LepsiTimer.h"

class App
{
public:
	App();
	int Create();

private:
	void ComposeFrame();

	Window wnd;
	LepsiTimer lTimer;

	/* premenné na loop aplikácie */
	double delta = 0;
	static constexpr double ns = 1 / 60.0;
	
};

