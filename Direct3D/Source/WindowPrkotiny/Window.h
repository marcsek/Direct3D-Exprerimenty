#pragma once

#include "LepsiWin.h"
#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"
#include "../Graphics.h"
#include "../Utilities/LepsiaException.h"
#include <optional>
#include <memory>

class Window
{
public:
	class Exception : public LepsiaException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};

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
	Window(int width, int height, const LPCWSTR name);
	~Window();

	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessage();
	bool IsRunning();

	Graphics& Gfx();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgInvoke(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

public:
	Keyboard kbd;
	Mouse mouse;

private:
	int width = 0, height = 0;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;

	bool window_is_running = false;
};

/* pomocné makro na exception */
#define CHWND_EXCEPT( hr ) Window::Exception(__LINE__, __FILE__, hr)
#define CHWND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError())