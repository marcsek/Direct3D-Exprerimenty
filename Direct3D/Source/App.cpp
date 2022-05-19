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

	for (auto& pd : drawables)
	{
		if (auto pb = dynamic_cast<Box*>(pd.get()))
		{
			boxes.push_back(pb);
		}
	}

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

	SpawnSimulationWindow();

	cam.SpawnControlWindow();

	poLight.SpawnConstrolWindow();

	SpawnBoxManagerWindow();
	
	SpawnBoxWindows();

	wnd.Gfx().EndFrame();
}

void App::SpawnSimulationWindow() noexcept
{
	if (ImGui::Begin("Simulation Settings"))
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

			for (auto& pd : drawables)
			{
				if (auto pb = dynamic_cast<Box*>(pd.get()))
				{
					boxes.push_back(pb);
				}
			}
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
				boxes.clear();
			}
		}
		ImGui::EndGroup();
		ImGui::Spacing();

		ImGui::Text("Simulation status: %s (Press space to pause)", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING");
	}
	ImGui::End();
}

void App::SpawnBoxManagerWindow() noexcept
{
	if (ImGui::Begin("Boxes"))
	{
		using namespace std::string_literals;
		const auto preview = comboBoxIndex ? std::to_string(*comboBoxIndex) : "Choose a box to edit"s;
		if (ImGui::BeginCombo("Box Number", preview.c_str()))
		{
			for (int i = 0; i < boxes.size(); i++)
			{
				const bool selected = comboBoxIndex == i;

				if (ImGui::Selectable(std::to_string(i).c_str(), selected))
				{
					comboBoxIndex = i;
				}
				if (selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		if (ImGui::Button("Spawn Control Window") && comboBoxIndex)
		{
			boxControlIds.insert(*comboBoxIndex);
			comboBoxIndex.reset();
		}
	}
	ImGui::End();
}

void App::SpawnBoxWindows() noexcept
{
	if (boxes.size() <= 0) return;
	for (auto i = boxControlIds.begin(); i != boxControlIds.end();)
	{
		if (!boxes[*i]->SpawnControlWindow(*i, wnd.Gfx()))
		{
			i = boxControlIds.erase(i);
		}
		else
		{
			i++;
		}
	}
}



