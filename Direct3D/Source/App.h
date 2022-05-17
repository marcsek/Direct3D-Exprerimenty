#pragma once
#include "Camera.h"
#include "Drawable/Box.h"
#include "Drawable/Cylinder.h"
#include "Drawable/Melon.h"
#include "Drawable/Pyramide.h"
#include "Drawable/Sheet.h"
#include "Drawable/SkinnedBox.h"
#include "Utilities/LepsiaMath.h"
#include "WindowPrkotiny/Window.h"
#include "Utilities/LepsiTimer.h"
#include "Vendor/ImGui/ImGuiManager.h"
#include "Lights/PointLight.h" 
#include <set>

class Drawable;

class App
{
public:
	App();
	int Create();
	~App();

private:
	void ComposeFrame();

	void SpawnSimulationWindow() noexcept;
	void SpawnBoxManagerWindow() noexcept;
	void SpawnBoxWindows() noexcept;

	ImGuiManager im_gui_manager;
	inline static bool show_demo_window = true;

	Window wnd;
	LepsiTimer lTimer;
	Camera cam;
	PointLight poLight;

	std::vector<std::unique_ptr<class Drawable>> drawables;

	std::vector<class Box*> boxes;
	std::optional<int> comboBoxIndex;
	std::set<int> boxControlIds;
	float simulation_speed = 1.0f;

private:
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:gfx(gfx)
		{}

		std::unique_ptr<Drawable> operator()()
		{
			const DirectX::XMFLOAT3 mat = { cdist(rng), cdist(rng), cdist(rng) };
			switch (sdist(rng))
			{
			case 0:
				/*return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 1:*/
				return std::make_unique<Box>(
					gfx, rng, adist, ddist,
					odist, rdist, bdist, mat
					);
			case 1:
				return std::make_unique<Cylinder>(
					gfx, rng, adist, ddist, 
					odist, rdist, bdist, tdist
					);
			case 2:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist,
					odist, rdist, tdist
					);
			case 3:
				return std::make_unique<SkinnedBox>(
					gfx, rng, adist, ddist,
					odist, rdist
					);

				/*
				return std::make_unique<Melon>(
					gfx, rng, adist, ddist,
					odist, rdist, longdist, latdist
					);
			case 3:
				return std::make_unique<Sheet>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 4:
				return std::make_unique<SkinnedBox>(
					gfx, rng, adist, ddist,
					odist, rdist
					);*/
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> sdist{ 0, 3 };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_real_distribution<float> cdist{ 0.0f, 1.0f };
		std::uniform_int_distribution<int> tdist{ 10, 30 };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0, 4 };
	};
};

