#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include <WinUser.h>
#include <atlstr.h>
#include <strsafe.h>
#include <TlHelp32.h>
#include <iostream>
#include <unordered_map>
#include <string>



#define DETECTED 111
#define FILEFOUND 115
#define PRINTERROR 116
#define SWM_TRAYMSG WM_APP

#define SWM_HIDE 112
#define SWM_SHOW 113
#define SWM_EXIT 114

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("ASAP");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("ASAP - Auto Scan And Print");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;
HWND hwndMain;
HWND TextBox = NULL;
HFONT hFont;
HANDLE hThreadWorker;

BOOL bRunning = TRUE;

void Log(std::string text);
void WriteToFile(const CHAR* data);

void WriteLog();

// Make sure to free the buffer of TCHAR* 

struct ArrayHasher {
	std::size_t operator()(const TCHAR* path) const {

		std::size_t h = 0;

		int i = 0;

		while (path[i] != '\0')
		{
			h ^= std::hash<TCHAR>{}(path[i]) + 0x9e3779b9 + (h << 6) + (h >> 2);
			i++;
		}
		return h;
	}
};

struct KeyComparator
{
	bool operator()(const TCHAR* key1, const TCHAR* key2) const
	{
		// _tcscmp, if returns 0, then the values matches.
		return (_tcscmp(key1, key2) == 0) ? true : false;
	}
};

std::unordered_map<TCHAR*, FILETIME, ArrayHasher, KeyComparator> g_paths;

TCHAR g_path_to_watch[_MAX_PATH] = TEXT("C:\\Users\\HIRANI\\Desktop\\Windows API\\ASAP APP\\IN");

NOTIFYICONDATA nid;

HANDLE hDirectory;
OVERLAPPED overlapped;

HANDLE wHwnd;
//HANDLE rHwnd;


LRESULT CALLBACK WndProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);

void AppendTextToEditCtrl(HWND hWndEdit, LPCTSTR pszText);

DWORD WINAPI MonitorDirectory(LPVOID lpParam);
void ReadAndPrint(const CString& filePath);

void Initiate();

BOOL InitNotificationIcon(int nCmdShow);

void ShowContextMenu(HWND hWnd);

void ErrorMessage(const wchar_t* lpszFunction);




int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(ID_MYAPPLICATION_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(ID_MYAPPLICATION_ICON));

	if (!RegisterClassEx(&wcex))
	{
		ErrorMessage(L"Call to RegisterClassEx failed!");

		return 1;
	}

	// Store instance handle in our global variable
	hInst = hInstance;

	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	Initiate();

	hwndMain = hWnd;

	AllocConsole();

	wHwnd = GetStdHandle(STD_OUTPUT_HANDLE);

	InitNotificationIcon(1);

	hThreadWorker = CreateThread(
		NULL,
		0,
		MonitorDirectory,
		NULL,
		0,
		NULL
	);

	if (hThreadWorker == NULL)
		ExitProcess(3);

	if (!hWnd)
	{
		ErrorMessage(L"Call to CreateWindowEx failed!");

		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	WaitForSingleObject(hThreadWorker, INFINITE);

	CloseHandle(hThreadWorker);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PAINTSTRUCT ps;
	TCHAR lpszText[] = L"Program started.";

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

		default:
			break;
		}
		break;
	case FILEFOUND:
		//AppendTextToEditCtrl(TextBox, (LPCTSTR)lParam);
		break;
	case PRINTERROR:
		AppendTextToEditCtrl(TextBox, (LPCTSTR)lParam);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId)
		{
		case SWM_SHOW:
			ShowWindow(hWnd, SW_RESTORE);
			AppendTextToEditCtrl(TextBox, (LPCTSTR)TEXT("Windows restored."));
			break;
		case SWM_HIDE:
		case IDOK:
			AppendTextToEditCtrl(TextBox, (LPCTSTR)TEXT("Windows minimized."));
			ShowWindow(hWnd, SW_HIDE);
			break;
		case SWM_EXIT:
			AppendTextToEditCtrl(TextBox, (LPCTSTR)TEXT("Windows about to exit."));
			break;
		default:
			break;
		}
		return 1;
	case WM_CTLCOLORSTATIC:
	{
		HDC hdc = (HDC)wParam;

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));
		return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));
	}
	case WM_CREATE:
		RECT rect;

		GetClientRect(hWnd, &rect);

		TextBox = CreateWindow(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | ES_READONLY | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hWnd, NULL, NULL, NULL);

		hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

		SendMessage(TextBox, WM_SETTEXT, 0, (LPARAM)lpszText);
		SendMessage(TextBox, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		break;
	case WM_PAINT:

		break;
	case WM_CLOSE:

		bRunning = FALSE;
		SetEvent(overlapped.hEvent);
		//SendMessage(TextBox, EM_REPLACESEL, 0, (LPARAM)message_state);
		//SendMessage(TextBox, EM_REPLACESEL, 0, (LPARAM)TEXT("Application is about to close."));
		AppendTextToEditCtrl(TextBox, TEXT("Application is about to close."));

		CloseHandle(overlapped.hEvent);
		CloseHandle(hDirectory);

		WriteLog();

		if (g_paths.size() > 0)
		{
			for (auto& el : g_paths)
			{
				delete[] el.first;
			}
		}

		Sleep(1000);
		DestroyWindow(hWnd);
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	//case WM_PARENTNOTIFY:
	//{
	//	if (LOWORD(wParam) == WM_LBUTTONDOWN)
	//	{
	//		
	//		//AppendTextToEditCtrl(TextBox, change);
	//	}

	//}
	case DETECTED:
	{
		AppendTextToEditCtrl(TextBox, (LPCTSTR)lParam);
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}

void AppendTextToEditCtrl(HWND hWndEdit, LPCTSTR pszText)
{
	int nLength = GetWindowTextLength(hWndEdit) + 2;
	SendMessage(hWndEdit, EM_SETSEL, (WPARAM)nLength, (LPARAM)nLength);
	SendMessage(hWndEdit, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)TEXT("\r\n"));
	SendMessage(hWndEdit, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)pszText);
}

bool contains(TCHAR *key)
{
	Log("FINDING KEY");
	//std::unordered_map<TCHAR*, FILETIME, ArrayHasher, KeyComparator>::const_iterator el = g_paths.find(key);
	auto el = g_paths.find(key);

	Log("KEY SEARCHED.");

	return el != g_paths.end();

}

DWORD WINAPI MonitorDirectory(LPVOID lpParam)
{
	//DWORD buffer[sizeof(FILE_NOTIFY_INFORMATION)] = { 0 };
	DWORD buffer[1024];

	DWORD dwBytesReturned;

	BOOL success = ReadDirectoryChangesW(
		hDirectory,
		buffer,
		sizeof(buffer),
		FALSE,
		FILE_NOTIFY_CHANGE_FILE_NAME |
		FILE_NOTIFY_CHANGE_DIR_NAME |
		FILE_NOTIFY_CHANGE_ATTRIBUTES |
		FILE_NOTIFY_CHANGE_SIZE |
		FILE_NOTIFY_CHANGE_LAST_WRITE |
		FILE_NOTIFY_CHANGE_LAST_ACCESS |
		FILE_NOTIFY_CHANGE_CREATION |
		FILE_NOTIFY_CHANGE_SECURITY,
		&dwBytesReturned,
		&overlapped,
		NULL
	);

	while (bRunning)
	{

		if (!success) break;

		WaitForSingleObject(overlapped.hEvent, INFINITE);

		DWORD bytesTransferred;

		success = GetOverlappedResult(hDirectory, &overlapped, &bytesTransferred, FALSE);

		if (!success)
		{
			ErrorMessage(L"GetOverlappedResult failed!");
			break;
		}
	
		PFILE_NOTIFY_INFORMATION pNotify = (PFILE_NOTIFY_INFORMATION)buffer;

		while (pNotify)
		{
			if (pNotify->Action == FILE_ACTION_ADDED)
			{
				Log("FILE_ACTION_ADDED");
				TCHAR szFileName[MAX_PATH + 1];
				memcpy(szFileName, pNotify->FileName, min(MAX_PATH, pNotify->FileNameLength));
				szFileName[min((pNotify->FileNameLength / sizeof(TCHAR)), MAX_PATH)] = 0;

				size_t dir_len = _tcslen(g_path_to_watch);
				size_t file_len = _tcslen(szFileName);

				TCHAR* fullPath = new TCHAR[dir_len + file_len + 2];
				Log("CREATED BUFFER FOR FULLPATH");

				_tcscpy_s(fullPath, dir_len + 1, g_path_to_watch);
				fullPath[dir_len] = '\\';
				_tcscpy_s(fullPath + dir_len + 1, file_len + 1, szFileName);

				Sleep(1000);
				Log("COPIED THE FULLPATH");

				HANDLE hFile = CreateFile(fullPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

				if (hFile == INVALID_HANDLE_VALUE)
				{
					ErrorMessage(L"CreateFile failed.");
					break;
				}

				FILETIME ftWrite;
				GetFileTime(hFile, NULL, NULL, &ftWrite);

				Log("GOT THE LAST_WRITE_TIME");

				if (!contains(fullPath))
				{
					Log("INSERTING FILE DATA TO MAP.");
					g_paths[fullPath] = ftWrite;

					PostMessage(hwndMain, DETECTED, NULL, (LPARAM)fullPath);
				}
				else
					Log("FILE ALREADY EXISTS IN THE CONTAINER.");

				CloseHandle(hFile);
				
				//PostMessage(hwndMain, DETECTED, NULL, (LPARAM)filePath.GetString());
				// Print the file here
				
				// Create a file to get it's last write time

				

				PostMessage(hwndMain, DETECTED, NULL, (LPARAM)L"Successfully stored the value in map.");

				Sleep(2000);
				ReadAndPrint(fullPath);
			}

			if (pNotify->NextEntryOffset == 0) break;

			pNotify = (PFILE_NOTIFY_INFORMATION)((LPBYTE)pNotify + pNotify->NextEntryOffset);
		}

		ResetEvent(overlapped.hEvent);

		success = ReadDirectoryChangesW(
			hDirectory,
			buffer,
			sizeof(buffer),
			FALSE,
			FILE_NOTIFY_CHANGE_FILE_NAME |
			FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_ATTRIBUTES |
			FILE_NOTIFY_CHANGE_SIZE |
			FILE_NOTIFY_CHANGE_LAST_WRITE |
			FILE_NOTIFY_CHANGE_LAST_ACCESS |
			FILE_NOTIFY_CHANGE_CREATION |
			FILE_NOTIFY_CHANGE_SECURITY,
			&dwBytesReturned,
			&overlapped,
			NULL
		);
	}

	return 0;
}

void ReadAndPrint(const CString& filePath)
{

	//LPCTSTR hFileOutPath = L"C:\\Users\\HIRANI\\Desktop\\Windows API\\ASAP APP\\TEMP\\OUT";
	HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		PostMessage(hwndMain, PRINTERROR, NULL, (LPARAM)TEXT("ReadAndPrint: Failed to CreateFile."));
		ErrorMessage(L"Failed to CreateFile");
		return;
	}
	DWORD fileSize = 0;
	DWORD dwBytesRead = 0;

	fileSize = GetFileSize(hFile, NULL);

	CHAR* data = new CHAR[fileSize];

	BOOL bSuccess = ReadFile(hFile, data, fileSize, &dwBytesRead, NULL);

	if (!bSuccess)
	{
		PostMessage(hwndMain, PRINTERROR, NULL, (LPARAM)TEXT("Failed to ReadFile."));
		CloseHandle(hFile);
		return;
	}
	else
	{
		if (dwBytesRead > 0 && dwBytesRead <= fileSize)
			data[dwBytesRead] = '\0';
		else {
			return;
		}

		PostMessage(hwndMain, PRINTERROR, NULL, (LPARAM)TEXT("\r\nSuccessfully created and read the file."));

		//PostMessage(hwndMain, FILEFOUND, NULL, (LPARAM)data);

		//HANDLE hFileOut = CreateFileA();

		//DWORD cBytesWritten = 0;
		//WriteFile(wHwnd, data, fileSize, &cBytesWritten, NULL);
		WriteToFile(data);
	}

	delete[] data;

	CloseHandle(hFile);
	//ErrorMessage(L"Handle closed!");
}

void WriteToFile(const CHAR* data)
{
//C:\Users\HIRANI\Desktop\Windows API\ASAP APP\OUT
	const CHAR FileOut[] = "C:\\Users\\HIRANI\\Desktop\\Windows API\\ASAP APP\\OUT\\out.txt\0";

	HANDLE hFileOut = CreateFileA(
		(LPCSTR)FileOut,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if(hFileOut == INVALID_HANDLE_VALUE)
	{
		Log("WriteToFile: CreateFileA failed.");
		return;
	}

	DWORD dwBytesWritten = 0;

	BOOL bSuccess = WriteFile(
		hFileOut,
		data,
		strlen(data),
		&dwBytesWritten,
		NULL
	);

	if (bSuccess == FALSE)
	{
		Log("WriteToFile: Failed to write data.");
		
	}
	else
	{
		if (dwBytesWritten != strlen(data))
		{
			Log("WriteToFile: dwBytesWritten != strlen(data)");

		}
	}

	CloseHandle(hFileOut);
}

void Initiate()
{
	hDirectory = CreateFile(
		(LPCWSTR)g_path_to_watch,
		GENERIC_READ,
		//FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		NULL
	);
	overlapped = { 0 };

	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return;
	}

	overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

BOOL InitNotificationIcon(int nCmdShow)
{
	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uID = ID_MYAPPLICATION_ICON;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(ID_MYAPPLICATION_ICON), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);

	nid.hWnd = hwndMain;
	nid.uCallbackMessage = SWM_TRAYMSG;

	Shell_NotifyIcon(NIM_ADD, &nid);

	return TRUE;
}

void ShowContextMenu(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);

	HMENU hMenu = CreatePopupMenu();

	if (hMenu)
	{
		if (IsWindowVisible(hWnd))
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_HIDE, _T("Hide"));
		else
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SHOW, _T("Show"));

		InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, _T("Exit"));

		SetForegroundWindow(hWnd);

		TrackPopupMenu(hMenu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);

		DestroyMenu(hMenu);
	}
}

void ErrorMessage(const wchar_t* lpszFunction)
{
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;

	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
	);

	lpDisplayBuf = (LPVOID)LocalAlloc(
		LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)
	);

	StringCchPrintf(
		(LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction,
		dw,
		lpMsgBuf
	);

	MessageBox(
		NULL,
		(LPCTSTR)lpDisplayBuf,
		TEXT("Error"),
		MB_OK
	);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}


void Log(std::string text)
{
	size_t len = text.size();

	WriteFile(wHwnd, text.c_str(), len, NULL, NULL);
	WriteFile(wHwnd, "\n", 1, NULL, NULL);
}

void WriteLog()
{
	if (g_paths.size() == 0) return;

	LPCTSTR path = TEXT("C:\\Users\\HIRANI\\Desktop\\Windows API\\ASAP APP\\Log\\log.txt");
	HANDLE hFile = CreateFile(path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		Log("CreateFile failed : WriteLog()");
		return;
	}

	DWORD dwBytesWritten = 0;

	for (auto& el : g_paths)
	{
		size_t fileNameSize = (_tcslen(el.first) + 1) * 2;
		CHAR* nString = new CHAR[fileNameSize];
		wcstombs_s(NULL, nString, fileNameSize, el.first, _TRUNCATE);
		BOOL bSuccess = WriteFile(hFile, nString, strlen(nString), &dwBytesWritten, NULL);
		//SetEndOfFile(hFile);
		bSuccess = WriteFile(hFile, "\n", 1, NULL, NULL);
		//SetEndOfFile(hFile);

		delete[] nString;
	}
	Log("Successfully Written Log File.");

	CloseHandle(hFile);
}