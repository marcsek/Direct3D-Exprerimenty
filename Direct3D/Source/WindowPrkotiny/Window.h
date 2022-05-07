#pragma once

#include "LepsiWin.h"
#include "../Input/Keyboard.h"

class Window
{
private:
	class WindowClass
	{
	public:
		static const LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;

		static constexpr const LPCWSTR wndClassName = L"Direct 3D";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const LPCWSTR name) noexcept;
	~Window();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgInvoke(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
	Keyboard kbd;

private:
	int width = 0, height = 0;
	HWND hWnd;
};