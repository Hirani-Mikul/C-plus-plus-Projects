#include "Application.h"

#include <thread>

#pragma comment(lib, "comctl32.lib")

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR  lpCmdLine, _In_ int nCmdShow)
{
	// Initialize common controls
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(icex);
	icex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icex);

	// Read notes on how to restart the entire application.

	Application app(hInstance, hPrevInstance, lpCmdLine);

	if (app.Initiate() != 0)
	{
		return 0;
	}

	if (!app.Start()) return 0;


	MSG msg = {};


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return Exit_Code;
}
