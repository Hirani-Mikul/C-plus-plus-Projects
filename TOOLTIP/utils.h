#pragma once
#include <Windows.h>
#include <tchar.h>
#include <shlobj_core.h>
#include <ostream>
#include <strsafe.h>



#define CONTROLTOOLTIP (WM_APP + 0x0002)


static CHAR chWindowClass[6];
static CHAR chTitle[17];
//static CHAR g_chTip[38];

static HINSTANCE g_hInstance;
static HWND g_hWnd;

static HWND hWndIcon;
static HWND hWndToolTip;
static HICON hIcon;


void Initiate();
BOOL RegisterWindow();
BOOL CreateClientWindow();
void CreateToolTip(HWND hWnd, HWND hToolHwnd, TCHAR* szText);

extern LRESULT CALLBACK WndProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);

/*
#include "App.h"

#pragma comment(lib,"comctl32.lib")

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_BAR_CLASSES | ICC_TAB_CLASSES | ICC_WIN95_CLASSES;

	InitCommonControlsEx(&icc);

	g_hInstance = hInstance;
	Initiate();

	if (!RegisterWindow()) return 0;
	if (!CreateClientWindow()) return 0;


	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return 0;
}
*/