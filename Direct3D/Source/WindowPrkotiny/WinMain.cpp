#include "Window.h"
#include <iostream>

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
	CreateConsole();

	Window wnd(640, 480, L"Direct 3D");

	MSG msg;
	BOOL gResult;
	while((gResult =  GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if(gResult == -1)
	{
		return -1;
	}

	return static_cast<int>(msg.wParam);
}