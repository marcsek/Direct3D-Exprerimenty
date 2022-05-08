#include "App.h"

#include <iomanip>
#include <iostream>

App::App()
	:
	wnd(640, 470, L"Direct 3D")
{}

int App::Create()
{
	while(wnd.IsRunning())
	{
		//float duration = lTimer.Mark();
		//delta += duration / ns;

		//while(delta >= 1.0)
		//{
			if (const auto ecode = Window::ProcessMessage())
			{
				return *ecode;
			}
		/*	std::cout << "\rNepresnost delty: " << std::setprecision(10) << std::fixed << delta - 1.0;
			delta -= 1.0;
		}*/
		ComposeFrame();
	}
	return 0;
}

void App::ComposeFrame()
{
	const float c = sin(lTimer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().EndFrame();
}



