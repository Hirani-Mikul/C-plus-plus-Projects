#include "resource.h"
#include "stdafx.h"

#include <iostream>

#define MY_TRAY_ICON_ID 1
#define SWM_TRAYMSG WM_APP
#define SWM_SHOW WM_APP + 1
#define SWM_HIDE WM_APP + 2
#define SWM_EXIT WM_APP + 3


HINSTANCE hInst;
NOTIFYICONDATA nid;

HWND hWnd = GetConsoleWindow();

BOOL OnInitDialog(HWND hWnd);

BOOL InitInstance(HINSTANCE, int);


void ShowContextMenu(HWND hWnd)
{
    POINT pt;
    GetCursorPos(&pt);
    HMENU hMenu = CreatePopupMenu();
    // Create or load menu

    if (hMenu)
    {
        if (IsWindowVisible(hWnd))
            InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_HIDE, _T("Hide"));
        else InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SHOW, _T("Open"));

        InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, _T("Exit"));

        SetForegroundWindow(hWnd);

        TrackPopupMenu(hMenu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);
        DestroyMenu(hMenu);
    }

}

INT_PTR CALLBACK MyDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;

    switch (message)
    {
    case SWM_TRAYMSG:
        switch (lParam)
        {
        case WM_LBUTTONDBLCLK:
            ShowWindow(hWnd, SW_RESTORE);
            break;
        case WM_RBUTTONDOWN:
        case WM_CONTEXTMENU:
            ShowContextMenu(hWnd);
            break;
        default:
            break;
        }
        break;
    case WM_SYSCOMMAND:
        if ((wParam & 0xFFF0) == SC_MINIMIZE)
        {
            ShowWindow(hWnd, SW_HIDE);
            return 1;
        }
        break;
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        switch (wmId)
        {
        case SWM_SHOW:
            ShowWindow(hWnd, SW_RESTORE);
            break;
        case SWM_HIDE:
        case IDOK:
            ShowWindow(hWnd, SW_HIDE);
            break;
        case SWM_EXIT:
            DestroyWindow(hWnd);
            break;
        }
        return 1;

    case WM_INITDIALOG:
        return 0;
    case WM_CLOSE:
        DestroyWindow(hWnd);
    case WM_DESTROY:
        nid.uFlags = 0;
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;
    }
    return 0;
}

BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
    char mesg[128];
    switch (CEvent)
    {

    case CTRL_C_EVENT:
        MessageBox(NULL,
            L"CTRL+C received!", L"CEvent", MB_OK);
        break;
    case CTRL_BREAK_EVENT:
        MessageBox(NULL,
            L"CTRL+BREAK received!", L"CEvent", MB_OK);
        break;
    case CTRL_CLOSE_EVENT:

        ShellExecuteW(NULL, L"open", L"yourexe.exe", NULL, NULL, SW_MINIMIZE);

        break;
    case CTRL_LOGOFF_EVENT:
        MessageBox(NULL,
            L"User is logging off!", L"CEvent", MB_OK);
        break;
    case CTRL_SHUTDOWN_EVENT:
        MessageBox(NULL,
            L"User is logging off!", L"CEvent", MB_OK);
        break;
    }
    return TRUE;
}

int main()
{
    std::cout << "Program running..." << std::endl;

    MSG msg;
    HACCEL hAccelTable;


    if (!InitInstance((HINSTANCE)GetModuleHandle(NULL), SW_NORMAL)) return FALSE;
    hAccelTable = LoadAccelerators(hInst, (LPCTSTR)IDC_STEALTHDIALOG);


    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg) || !IsDialogMessage(msg.hwnd, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    std::cout << "Program Ended..." << std::endl;

    return (int)msg.wParam;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // InitCommonControls();
    InitCommonControls();
    hInst = hInstance;
    //HWND hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DLG_DIALOG), NULL, (DLGPROC)MyDlgProc);


    //if (!hwnd)
    //{
    //    std::cout << "Invalid hWnd. " << GetLastError() << "\n";
    //    return FALSE;
    //}
    ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.uID = MY_TRAY_ICON_ID;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

    nid.hIcon = (HICON)LoadImage(NULL, L"./icons/printer2.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    nid.hWnd = hWnd;
    nid.uCallbackMessage = SWM_TRAYMSG;
    nid.uVersion = NOTIFYICON_VERSION_4;

    lstrcpyn(nid.szTip, _T("Auto Print And Scan"), sizeof(nid.szTip) / sizeof(TCHAR));

    Shell_NotifyIcon(NIM_ADD, &nid);

    if (nid.hIcon && DestroyIcon(nid.hIcon))
        nid.hIcon = NULL;

    return TRUE;
}


/*
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = MY_TRAY_ICON_ID;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    //trayIcon.hIcon = LoadIcon(hInst)
    nid.hIcon = (HICON)LoadImage(NULL, L"./icons/printer2.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    nid.uCallbackMessage = WM_USER + 1;
    nid.uCallbackMessage = SWM_TRAYMSG;
    nid.uVersion = NOTIFYICON_VERSION_4;

    Shell_NotifyIcon(NIM_ADD, &nid);

    if (nid.hIcon && DestroyIcon(nid.hIcon))
        nid.hIcon = NULL;





            if (SetConsoleCtrlHandler(
        (PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
    {

        printf("Unable to install handler!\n");
        return -1;
    }
    else printf("Successfully installed the handler.\n");
    
*/