#include "utils.h"

TCHAR g_tip[] = L"This is a tip!";

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	int wmId, wmEvent;
	int notifyCode;

	switch (message)
	{
	case WM_CREATE:
	{
		hWndIcon = CreateWindowEx(
			    0, WC_STATIC, NULL,
			    WS_VISIBLE | WS_CHILD | SS_ICON,
			    200, 150, 32, 32,
			    hWnd, NULL, GetModuleHandle(NULL), NULL);

		hIcon = LoadIcon(NULL, IDI_QUESTION);
		SendMessage(hWndIcon, STM_SETICON, (WPARAM)hIcon, 0);

		//CreateToolTip(hWnd, hWndIcon, g_tip);


	}
	break;
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hWnd, &ps);
	//	DrawIconEx(hdc, 200, 150, hIcon, 32, 32, 0, NULL, DI_NORMAL);

	//	EndPaint(hWnd, &ps);
	//}
	//break;
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY:

		// Must Post a quit message, or else the application will still be running.



		PostQuitMessage(0);
		break;
	default:
		// Without the return value here, the creation of window will fail with error code 0.
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}