#include "Window.h"
#include <iostream>
#include <sstream>

void CreateConsole()
{
	AllocConsole();
	FILE* fpstdin = stdin, * fpstdout = stdout, * fpstderr = stderr;

	freopen_s(&fpstdin, "CONIN$", "r", stdin);
	freopen_s(&fpstdout, "CONOUT$", "w", stdout);
	freopen_s(&fpstderr, "CONOUT$", "w", stderr);

	std::cout << "Console Sucessfully Created\n";
}

int CALLBACK WinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	try
	{
		Window wnd(640, 480, L"Direct 3D");

		CreateConsole();

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (wnd.kbd.KeyIsPressed('A'))
			{
				std::cout << "Space\n";
			}
			std::pair<int, int> pos = wnd.mouse.GetPos();

			std::ostringstream oss;
			oss << "Mouse position: (" << pos.first << "," << pos.second << ")" << std::endl;
			wnd.SetTitle(oss.str());
		}


		if (gResult == -1)
		{
			return -1;
		}

		return static_cast<int>(msg.wParam);
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught: "<< e.what() << std::endl;
	}
}