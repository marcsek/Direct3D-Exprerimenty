#include "App.h"

#include <iomanip>

#include "Drawable/Box.h"
#include <memory>

#include "Drawable/Melon.h"
#include "Drawable/Pyramide.h"
#include "Drawable/Sheet.h"
#include "Drawable/SkinnedBox.h"
#include "Utilities/LepsiaMath.h"
#include "GDI/GDIPManager.h"
#include "Vendor/ImGui/imgui.h"
#include "Vendor/ImGui/imgui_impl_win32.h"
#include "Vendor/ImGui/imgui_impl_dx11.h"


GDIPManager g;

App::App()
	:
	wnd(1152, 864, L"Direct 3D"), poLight(wnd.Gfx())
{
	Factory fac(wnd.Gfx());
	drawables.reserve(200);
	std::generate_n(std::back_inserter(drawables), 200, fac);

	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, Window::screen_width / Window::screen_height, 0.5f, 70.0f));
}

int App::Create()
{
	while(wnd.IsRunning())
	{
		if (const auto ecode = Window::ProcessMessage())
		{
			return *ecode;
		}
		ComposeFrame();
	}
	return 0;
}

App::~App()
{}


void App::ComposeFrame()
{
	auto dt = lTimer.Mark() * simulation_speed;

	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());
	poLight.Bind(wnd.Gfx(), cam.GetMatrix());

	for(const auto& drawable : drawables)
	{
		drawable->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		drawable->Draw(wnd.Gfx());
	}
	poLight.Draw(wnd.Gfx());

	if(ImGui::Begin("Simulation Settings"))
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::SliderFloat("Speed factor", &simulation_speed, 0.0f, 4.0f);

		ImGui::Spacing();
		ImGui::Text("Drawable amount %d", drawables.size());

		ImGui::BeginGroup();
		
			if (ImGui::Button("Add random")) {
				Factory fac(wnd.Gfx());
				drawables.push_back(fac());
			}
			ImGui::SameLine();
			if (ImGui::Button("Add 100")) {
				Factory fac(wnd.Gfx());
				drawables.reserve(100);
				std::generate_n(std::back_inserter(drawables), 100, fac);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete last")) {
				if (drawables.size() > 0)
				{
					drawables.pop_back();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete all")) {
				if (drawables.size() > 0)
				{
					drawables.clear();
				}
			}
			ImGui::EndGroup();
			ImGui::Spacing();

			ImGui::Text("Simulation status: %s (Press space to pause)", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING");
	}
	ImGui::End();

	cam.SpawnControlWindow();

	poLight.SpawnConstrolWindow();

	wnd.Gfx().EndFrame();
}



