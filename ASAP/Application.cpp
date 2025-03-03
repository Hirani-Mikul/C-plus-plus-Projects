#include "Application.h"


TCHAR Application::szWindowClass[] = _T("ASAP");
TCHAR Application::szTitle[] = _T("ASAP - Auto Scan And Print");


Application::Application(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR  lpCmdLine) : m_hInstance{ hInstance }, m_hPrevInstance{ hPrevInstance }, m_lpCommandLine{ NULL }, m_SettingWindow{ NULL } {

	m_hWnd = NULL;
	m_hWatcherThread = INVALID_HANDLE_VALUE;
	m_Nid = { };

	m_CurrentState = STATE::STOPPED;

	if (DEBUGMODEON)
	{
		console.Create();
	}


	size_t len = _tcslen(lpCmdLine);
	m_lpCommandLine = new TCHAR[len + 1];

	_tcscpy_s(m_lpCommandLine, len + 1, lpCmdLine);

}

Application::~Application() {
}

INT Application::Initiate() {

	BOOL bSuccess = FALSE;

	m_CurrentState = STATE::RUNNING;
	 
	bSuccess = RegisterWindow();
	if (!bSuccess) return 1; // 1 Represents error in Registering Window.
	
	bSuccess = CreateClientWindow();
	if (!bSuccess) return 2; // 2 Represents error in Creating Client Window.

	//bSuccess = InitNotificationIcon(1, m_hWnd, NULL);
	//if (!bSuccess) return 3; // 3 Represents error in Initiating System Tray Icon.

	// Load application settings from config file.
	LoadApplicationSettings();

	// Initiate the Printer by giving it access to application printer.
	Printer::Initiate(m_Settings.current_printer);

	// Initiate the FileManager by giving access to application's 'IN', 'OUT', & 'ERROR' directory.
	FileManager::Initiate(
		m_Settings.input_directory,    // INPUT PATH
		m_Settings.output_directory,   // OUTPUT PATH
		m_Settings.error_directory     // ERROR PATH
	);
	
	// Initiate the DirectoryWatcher object with application's handle and waiting time.
	BOOL bSuccess2 = m_Watcher.Initiate(&m_hWnd, m_Settings.waiting_time);

	if (!bSuccess2)
	{
		return 4; // 4. Represents error in creating directory to watch.
	}

	return 0; // 0 Represents success.
}

BOOL Application::Start()
{
	if (!MONITORMODE) return TRUE;

	// Initiate the m_hWatcherThread to monitor the directory.
	m_hWatcherThread = CreateThread(
		NULL,
		0,
		DirectoryWatcher::Monitor,
		(LPVOID)&m_Watcher,
		0,
		NULL
	);

	_Write("Successfully created thread!");

	if (m_hWatcherThread == NULL) return FALSE;

	return TRUE;
}

BOOL Application::Pause()
{
	UpdateNotificationIcon(2);

	m_Watcher.Pause();
	
	Shell_NotifyIcon(NIM_MODIFY, &m_Nid);

	Logger.Write("Application paused!");
	return 0;
}

BOOL Application::Resume()
{
	UpdateNotificationIcon(1);

	m_Watcher.Resume();

	// Check for files in the list.
	PrintFiles();

	Logger.Write("Application resumed!");
	return 0;
}

BOOL Application::Stop()
{
	// Clear the list of files.
	FileManager::ClearAllFiles();

	// Clear any memory.

	// Stop and exit from the watcher thread.
	m_Watcher.Stop();


	// Write a Log File.
	BOOL bSuccess = WriteLogFile();

	// Clean the content of edit control.
	Logger.Clear();

	if (!MONITORMODE) return TRUE;
	// Wait for the m_hWatcherThread to finish the task.
	WaitForSingleObject(m_hWatcherThread, INFINITE);

	CloseHandle(m_hWatcherThread);

	if (m_lpCommandLine != NULL)
		delete[] m_lpCommandLine;

	return 0;
}

BOOL Application::Exit()
{
	Stop();

	Shell_NotifyIcon(NIM_DELETE, &m_Nid);

	DestroyAssets();

	return 0;
}

BOOL Application::CreateSettingWindow()
{
	// Check if the setting window is already open. If NULL, then it's not open.
	if (m_SettingWindow != NULL)
	{
		// It's open, set the focus.
		SetFocus(m_SettingWindow->GetSettingWndHandle());
		return FALSE;
	}
	// Need to free the memory once the setting window closes.
	m_SettingWindow = new SettingWindow(m_hWnd, m_Settings);
	EnableWindow(m_hWnd, FALSE);
	return TRUE;
}

BOOL Application::RegisterWindow()
{


	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Application::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	
	
	// Load Main App Icon
	m_AppIcons[0] = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APP_ICON));


	wcex.hIcon = m_AppIcons[0];
	//wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = Application::szWindowClass;
	//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wcex.hIconSm = m_AppIcons[0];

	if (!RegisterClassExW(&wcex))
	{
		// Handle error
		ErrorMessage(L"RegisterWindow(): Call to RegisterClassEx failed!");
		return FALSE;
	}
	return TRUE;
}

INT Application::CreateClientWindow()
{
	m_hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, //
		Application::szWindowClass, // Class Name
		Application::szTitle, // Window Name
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // Startup behaviour i.e should be visible
		CW_USEDEFAULT, // Inital x location of window.
		CW_USEDEFAULT, // Initial y location of window.
		CW_USEDEFAULT, // Initial width of window.
		CW_USEDEFAULT, // Initial height of window.
		NULL, // Handle to parent window.
		NULL, // HWND to hMenu
		m_hInstance, // Instance of main window.
		this // lpParam, pass pState
	);

	if (m_hWnd == NULL)
	{
		// Handle error
		ErrorMessage(L"CreateClientWindow(): CreateWindowEx failed!");
		return FALSE;
	}


	return TRUE;
}

INT Application::InitNotificationIcon(INT nCmdShow, HWND hWnd)
{
	/***************************************************************************
	------------------------------ IMPORTANT ------------------------------------

				THIS METHOD SHOULD BE CALLED WHEN "WM_CREATE" IS TRIGGERED.
				FETCH THE ICON FIRST.
				THEN ADD ICON TO THE SYSTEM TRAY.


				CHECK IN PHONE'S NOTES. TO SEE THE CODE PROVIDED BY THE CHAT-GPT


	****************************************************************************/
	ZeroMemory(&m_Nid, sizeof(NOTIFYICONDATA));

	m_Nid.cbSize = sizeof(NOTIFYICONDATA);
	m_Nid.uID = IDI_APP_ICON;
	m_Nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	//m_Nid.hIcon = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_APP_ICON), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	m_Nid.hIcon = m_AppIcons[1];
	m_Nid.hWnd = hWnd;
	m_Nid.uCallbackMessage = SWM_TRAYMSG;

	// Adding icon to system tray. Remove when closing window.
	return (INT)Shell_NotifyIcon(NIM_ADD, &m_Nid); 

}

BOOL Application::UpdateNotificationIcon(INT nIconIndex)
{
	// 1 - Active State Icon
	// 2 - Paused State Icon
	// 3 - Stopped State Icon
	m_Nid.hIcon = m_AppIcons[nIconIndex];
	Shell_NotifyIcon(NIM_MODIFY, &m_Nid);

	return 0;
}

BOOL Application::AddContextMenu(HWND hWnd)
{
	// To store the cursor position when hovered over the menu.
	POINT pt;

	GetCursorPos(&pt);

	HMENU hMenu = CreatePopupMenu();

	// MENU OPTIONS:
	/*
		1. Show/Hide
		2. Pause
		3. Resume
		4. Restart
		5. Exit
	*/
	/**/
	if (hMenu)
	{
		if (IsWindowVisible(hWnd))
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_HIDE, _T("Hide"));
		else
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SHOW, _T("Show"));

		if (m_CurrentState == RUNNING)
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_PAUSE, _T("Pause"));
		else
			InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_RESUME, _T("Resume"));
		
		InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_RESTART, _T("Restart"));
		InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_SETTING, _T("Setting"));
		InsertMenu(hMenu, -1, MF_BYPOSITION, SWM_EXIT, _T("Exit"));

		SetForegroundWindow(hWnd);
		TrackPopupMenu(hMenu, TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);
		DestroyMenu(hMenu);
	}

	return 0;
}

void Application::SetCurrentState(STATE newState)
{
	if (newState == m_CurrentState) return;

	m_CurrentState = newState;

	switch (m_CurrentState)
	{
	case Application::RUNNING:
		Resume();
		break;
	case Application::PAUSED:
		Pause();
		break;
	case Application::STOPPED:
		Stop();
		break;
	default:
		break;
	}
}
BOOL Application::LoadAssets(HWND hWnd)
{
	// Need to DESTROY THIS ICON BEFORE EXIT.


	// Active State Icon
	m_AppIcons[1] = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_APP_ICON_ACTIVE), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	// Paused State Icon
	m_AppIcons[2] = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_APP_ICON_PAUSED), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	// Stopped State Icon
	m_AppIcons[3] = (HICON)LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_APP_ICON_STOPPED), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
}
BOOL Application::DestroyAssets()
{
	DestroyIcon(m_AppIcons[0]);
	DestroyIcon(m_AppIcons[1]);
	DestroyIcon(m_AppIcons[2]);
	DestroyIcon(m_AppIcons[3]);
}

BOOL Application::PrintFiles()
{
	if (m_CurrentState != RUNNING) return 0;

	// After resuming, there may exist only one file to process.

	// Fetch the file.
	CONST TCHAR* szFile = FileManager::GetFirstFile();

	// If it's NULL, then the list is empty.
	if (szFile == NULL)	return 0;

	BOOL bStatus = Printer::PrintFile(szFile);

	FileManager::MoveTheFile(szFile, bStatus);

	return 1;
}

BOOL Application::WriteLogFile()
{
	CONST CHAR* pszTextContent = Logger.GetTextContent();

	if (!pszTextContent) return FALSE;

	// Get current date and time.

	// WORD == unsigned short
	SYSTEMTIME localTime;
	GetLocalTime(&localTime);

	// Format: DD-MM-YYYY_HH-MM

	CStringA Path;
	Path.Format(
		"C:\\Users\\HIRANI\\Desktop\\Project\\ASAP\\Logs\\Log %d-%d-%d_%d-%d.txt",
		localTime.wDay, 
		localTime.wMonth, 
		localTime.wYear, 
		localTime.wHour, 
		localTime.wMinute
	);

	// Write the content to a text file.
	
	HANDLE hFile = CreateFileA(Path, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	DWORD dwBytesWritten = 0;
	size_t BytesToWrite = strlen(pszTextContent);

	BOOL bSuccess = WriteFile(hFile, pszTextContent, BytesToWrite, &dwBytesWritten, NULL);

	if (dwBytesWritten != BytesToWrite)
	{
		CloseHandle(hFile);
		delete[] pszTextContent;
		return FALSE;
	}

	CloseHandle(hFile);
	delete[] pszTextContent;

	return TRUE;
}



