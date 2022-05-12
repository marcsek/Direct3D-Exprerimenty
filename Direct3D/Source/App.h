#pragma once
#include "WindowPrkotiny/Window.h"
#include "Utilities/LepsiTimer.h"

class App
{
public:
	App();
	int Create();
	~App();

private:
	void ComposeFrame();

	Window wnd;
	LepsiTimer lTimer;
	LepsiTimer frameTimer;

	/* premenné na loop aplikácie */
	double delta = 0;
	static constexpr double ns = 1 / 60.0;
	std::vector<std::unique_ptr<class Box>> boxes;
};

