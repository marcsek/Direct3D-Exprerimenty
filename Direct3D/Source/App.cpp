#include "App.h"

#include "Drawable/Box.h"
#include <memory>

App::App()
	:
	wnd(640, 470, L"Direct 3D")
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);

	for (auto i = 0; i < 80; i++)
	{
		boxes.push_back
		(
			std::make_unique<Box>
			(
				wnd.Gfx(),
				rng,
				adist,
				ddist,
				odist,
				rdist
			)
		);
	}
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

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

App::~App()
{}


void App::ComposeFrame()
{
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	auto dt = lTimer.Mark();

	for(auto& b : boxes)
	{
		b->Update(dt);
		b->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
}



