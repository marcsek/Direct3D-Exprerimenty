#include <iostream>
#include "../App.h"

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
		CreateConsole();

		App{}.Create();
	}
	catch (const LepsiaException& e)
	{
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard", MB_OK | MB_ICONEXCLAMATION);
	}
	catch(...)
	{
		MessageBoxA(nullptr, "No message", "Unknown", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}