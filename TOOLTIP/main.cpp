#include <windows.h>
#include <commctrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")

#define ICONCONTAINER 110
#define ICONSIZE 32
#define PAINTICON 1

HINSTANCE ggInstance;
LRESULT CALLBACK WndProce(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void AddToolInfo(HWND hwnd, HWND hwndToolTip, HWND hwndTool, LPWSTR pszText);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    ggInstance = hInstance;

    // Register window class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProce;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = TEXT("TooltipExample");
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL, TEXT("RegisterClassEx failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // Create window
    HWND hwnd = CreateWindow(
        TEXT("TooltipExample"), TEXT("Tooltip Example"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 600, 500,
        NULL, NULL, hInstance, NULL);

    if (!hwnd)
    {
        MessageBox(NULL, TEXT("CreateWindow failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // Show window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProce(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND staticIconCtl[5];
    static HWND hwndTooltip;
    static HICON hIconI;

    switch (message)
    {
    case WM_CREATE:
    {
        // Create an icon control
        INT initXpos = 50;
        INT initYpos = 50;
        for (int i = 0; i < 5; i++)
        {
            staticIconCtl[i] = CreateWindowEx(
                0, WC_STATIC, NULL,
                WS_VISIBLE | WS_CHILD | SS_ICON | SS_NOTIFY,
                initXpos, initYpos, ICONSIZE, ICONSIZE,
                hwnd, (HMENU)(ICONCONTAINER + i), ggInstance, NULL);

            initYpos += 45;
        }


        // Load an icon and set it to the static control
        //HICON hIconI = LoadIcon(NULL, IDI_INFORMATION); // You can use your own icon

        hIconI = (HICON)LoadImage(
            NULL,
            IDI_INFORMATION,
            IMAGE_ICON,
            ICONSIZE,
            ICONSIZE,
            LR_SHARED
        );


        if (!PAINTICON)
        {
            for (int i = 0; i < 5; i++)
            {
                SendMessage(staticIconCtl[i], STM_SETICON, (WPARAM)hIconI, 0);
            }
            
        }


        // Create the tooltip window
        hwndTooltip = CreateWindowEx(
            0, TOOLTIPS_CLASS, NULL,
            WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            hwnd, NULL, GetModuleHandle(NULL), NULL);

        if (!hwndTooltip)
        {
            MessageBox(hwnd, TEXT("Tooltip creation failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
            return -1;
        }
        

        for (int i = 0; i < 5; i++)
        {
            TCHAR tip[150];
            LoadString(ggInstance, IDI_TIP1 + i, tip, 150);
            AddToolInfo(hwnd, hwndTooltip, staticIconCtl[i], tip);
        }

        // Activate tooltip.
        SendMessage(hwndTooltip, TTM_ACTIVATE, TRUE, 0);

        break;
    }

    case WM_PAINT:
    {
        if (!PAINTICON) return DefWindowProc(hwnd, message, wParam, lParam);

        for (int i = 0; i < 5; i++)
        {
            HWND hwndStatic = staticIconCtl[i];
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwndStatic, &ps);
            DrawIconEx(hdc, 0, 0, hIconI, ICONSIZE, ICONSIZE, 0, NULL, DI_NORMAL);
            EndPaint(hwndStatic, &ps);
        }



        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    break;
    /*case WM_CTLCOLORSTATIC:
    {
        int controlId = GetDlgCtrlID((HWND)lParam);

        if (controlId == ICONCONTAINER) {
            HDC hdcStatic = (HDC)wParam;
            SetBkMode(hdcStatic, TRANSPARENT);
            return (INT_PTR)GetStockObject(NULL_BRUSH);
        }

        //return DefWindowProc(hwnd, message, wParam, lParam);
        return (INT_PTR)CreateSolidBrush(RGB(255, 0, 0));
    }
    break;*/
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void AddToolInfo(HWND hwnd, HWND hwndToolTip, HWND hwndTool, LPWSTR pszText)
{
    TOOLINFO ti2 = { 0 };
    ti2.cbSize = TTTOOLINFO_V1_SIZE;
    ti2.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
    ti2.hwnd = hwnd;
    ti2.hinst = GetModuleHandle(NULL);
    ti2.uId = (UINT_PTR)hwndTool;
    ti2.lpszText = pszText;


    // Get the coordinates of the tool
    GetClientRect(hwndTool, &ti2.rect);

    // Associate the tooltip with the tool
    if (!SendMessage(hwndToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti2))
    {
        MessageBox(hwnd, TEXT("TTM_ADDTOOL failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
    }

}