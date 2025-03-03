#pragma once
#include "utils.h"



void Initiate()
{
	memcpy(chWindowClass, "MIKUL", 5);
	chWindowClass[5] = '\0';
	memcpy(chTitle, "MYTOOLTIP - TEXT", 16);
	chTitle[16] = '\0';

	//memcpy(g_chTip, "This is a client area of Application!", 37);
	//g_chTip[37] = '\0';

}
BOOL RegisterWindow()
{
	WNDCLASSA wc;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(wc.hInstance, IDI_QUESTION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = chWindowClass;
	
	if (!RegisterClassA(&wc)) return FALSE;
	else return TRUE;
}
BOOL CreateClientWindow()
{
	g_hWnd = CreateWindowExA(
		WS_EX_OVERLAPPEDWINDOW,
		chWindowClass, // Class Name
		chTitle, // Window Name
		WS_VISIBLE | WS_OVERLAPPEDWINDOW, // Startup behaviour i.e should be visible
		CW_USEDEFAULT, // Inital x location of window.
		CW_USEDEFAULT, // Initial y location of window.
		CW_USEDEFAULT, // Initial width of window.
		CW_USEDEFAULT, // Initial height of window.
		NULL, // Handle to parent window.
		NULL, // HWND to hMenu
		g_hInstance, // Instance of main window.
		NULL // lpParam, pass pState
	);

	if (g_hWnd == NULL) return FALSE;
	else return TRUE;
}

void CreateToolTip(HWND hWnd, HWND hToolHwnd, TCHAR* szText)
{
	hWndToolTip = CreateWindowEx(
		0,
		TOOLTIPS_CLASS,
		NULL,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON | TTS_NOPREFIX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hWnd,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	if (!hWndToolTip) return;

	TOOLINFO toolInfo = { 0 };
	//toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.cbSize = TTTOOLINFOA_V1_SIZE;
	toolInfo.hwnd = hWnd;
	toolInfo.hinst = GetModuleHandle(NULL);
	toolInfo.uId = (UINT_PTR)hToolHwnd;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.lpszText = szText;
	GetClientRect(hToolHwnd, &toolInfo.rect);
	

	// Return value is either TRUE if successfull else FALSE.
	BOOL bSuccess = SendMessage(hWndToolTip, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFOA)&toolInfo);
	if (!bSuccess)
	{
		MessageBox(NULL, L"FAILED TO ADD TOOL!", L"ERROR", MB_OK);
	}

	// No return value.
	SendMessage(hWndToolTip, TTM_ACTIVATE, TRUE, 0);
}

/*
	OLD & WORKING CREATETOOLTIP FUNCTION:

	void CreateToolTip(HWND hWnd, INT toolId, TCHAR* szText)
{

	HWND hwndTool;
	if (toolId == NULL) hwndTool = hWnd;
	else hwndTool = GetDlgItem(hWnd, toolId);

	hWndToolTip = CreateWindowEx(
		0,
		TOOLTIPS_CLASS,
		NULL,
		WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON | TTS_NOPREFIX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hWnd,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	if (!hWndToolTip) return;

	TOOLINFO toolInfo = { 0 };
	//toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.cbSize = TTTOOLINFOA_V1_SIZE;
	toolInfo.hwnd = hWnd;
	toolInfo.hinst = GetModuleHandle(NULL);
	toolInfo.uId = (UINT_PTR)hwndTool;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.lpszText = szText;
	GetClientRect(hwndTool, &toolInfo.rect);


	// Return value is either TRUE if successfull else FALSE.
	BOOL bSuccess = SendMessage(hWndToolTip, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFOA)&toolInfo);
	if (!bSuccess)
	{
		MessageBox(NULL, L"FAILED TO ADD TOOL!", L"ERROR", MB_OK);
	}

	// No return value.
	SendMessage(hWndToolTip, TTM_ACTIVATE, TRUE, 0);
}

*/