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
		using LepsiaException::LepsiaException;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;

		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
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

		static constexpr LPCWSTR wndClassName = L"Direct 3D";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const LPCWSTR name);
	~Window();

	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessage() noexcept;
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