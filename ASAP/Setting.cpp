#include "Setting.h"



SettingWindow::SettingWindow(HWND hWndParent, CONST AppSettings& settings) : m_hParenthWnd{ hWndParent }, m_hSettinghWnd{ NULL }, CurrentSettings{ settings }
{
	// Set the setting window's class name.
	_tcscpy_s(m_szWindowClass, _MAX_FNAME, TEXT("ASAP - SettingsClass"));

	// Set the setting window's title.
	_tcscpy_s(m_szTitle, _MAX_FNAME, TEXT("ASAP - Settings"));

	m_hInstance = GetModuleHandle(NULL);

	// Register and create setting window.
	RegisterSettingWindow();
	CreateSettingWindow();

	// Initialize the m_ChangedSetting with each bits off.
	m_ChangedSetting = 0b00000000;
}

const HWND SettingWindow::GetSettingWndHandle()
{
	if (m_hSettinghWnd != NULL) return m_hSettinghWnd;

	return NULL;
}

BOOL SettingWindow::RegisterSettingWindow()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = SettingWindow::SettingWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = SettingWindow::m_szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APP_ICON));


	if (!RegisterClassExW(&wcex))
	{
		// Handle error
		return FALSE;
	}

	return TRUE;

	return 0;
}

BOOL SettingWindow::CreateSettingWindow()
{
	RECT parentPosRect;
	GetClientRect(m_hParenthWnd, &parentPosRect);

	//int childX = (parentPosRect.right - parentPosRect.left) / 2;
	//int childY = (parentPosRect.bottom - parentPosRect.top) / 2;
	int childX = parentPosRect.left;
	int childY = parentPosRect.bottom;

	m_hSettinghWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, //
		SettingWindow::m_szWindowClass, // Class Name
		SettingWindow::m_szTitle, // Window Name
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // Startup behaviour i.e should be visible
		CW_USEDEFAULT, // Inital x location of window.
		CW_USEDEFAULT, // Initial y location of window.
		1100, // Initial width of window.
		300, // Initial height of window.
		m_hParenthWnd, // Handle to parent window.
		NULL, // HWND to hMenu
		m_hInstance, // Instance of main window.
		this // lpParam, pass pState
	);

	if (m_hSettinghWnd == NULL)
	{
		// Handle error
		return FALSE;
	}



	return TRUE;
}

BOOL SettingWindow::BrowseDirectory(TCHAR* szNewSelection, CONST TCHAR* szCurrentSelection)
{
	IFileDialog* pFileDialog = nullptr;
	BOOL bSuccess = FALSE;
	
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));
	IShellItem* pInitialFolderItem = NULL;
	if (SUCCEEDED(hr)) {
		// Set options (e.g., FOS_PICKFOLDERS for folder selection)
		pFileDialog->SetOptions(FOS_PICKFOLDERS);
		HRESULT hr2 = SHCreateItemFromParsingName(szCurrentSelection, NULL, IID_PPV_ARGS(&pInitialFolderItem));

		if (SUCCEEDED(hr2))
		{
			pFileDialog->SetFolder(pInitialFolderItem);
			pInitialFolderItem->Release();
		}
	}
	
	if (SUCCEEDED(pFileDialog->Show(nullptr))) {
		IShellItem* pItem;
		if (SUCCEEDED(pFileDialog->GetResult(&pItem))) {
			PWSTR folderPath;
			if (SUCCEEDED(pItem->GetDisplayName(SIGDN_FILESYSPATH, &folderPath))) {
				// Use folderPath (e.g., store it for later use)

				// User has selected the path, copy it to the szNewSelection.
				_tcscpy_s(szNewSelection, MAX_PATH, folderPath);

				CoTaskMemFree(folderPath);
				bSuccess = TRUE;
			}
			else
			{
				bSuccess = FALSE;
			}
			pItem->Release();
		}
		else
		{
			// User canceled the operation.
			bSuccess = FALSE;
		}
	}
	else {
		// Dialog failed to show.
		bSuccess = FALSE;
	}
	pFileDialog->Release();

	return bSuccess;
}

BOOL SettingWindow::BrowsePrinter(TCHAR* szNewSelection, CONST TCHAR* szCurrentSelection)
{
	// Create dialog box that shows list of printers.
	//HWND hDlg = CreateDialog(m_hInstance, MAKEINTRESOURCE(IDD_SELPRINTERDIAG), GetSettingWndHandle(), PrinterDialogProc);
	INT_PTR nResult = DialogBoxParam(m_hInstance, MAKEINTRESOURCE(IDD_SELPRINTERDIAG), GetSettingWndHandle(), PrinterDialogProc, (LPARAM)szCurrentSelection);
	
	// The result is in INT_PTR, convert it to TCHAR*.
	TCHAR* szReturnedSelection = reinterpret_cast<TCHAR*>(nResult);
	

	// Check if the user cancelled the selection.
	if (szReturnedSelection != NULL)
	{
		// Copy the returned result into the szNewSelection.
		_tcscpy_s(szNewSelection, _tcslen(szReturnedSelection) + 1, szReturnedSelection);
		// Free the memory held by szReturnedSelection.
		delete[] szReturnedSelection;

		return TRUE;
	}

	return FALSE;
}

BOOL SettingWindow::GetWaitingTime(TCHAR* szNewSelection)
{
	// Change waiting time.
	HWND hEditWaitingTime = m_SettingDivision[4].m_Edit;

	// Get the length in characters of the edit control box.
	INT nEditContentLen = GetWindowTextLength(hEditWaitingTime);

	// 0 when the field is empty or if the function fails.
	if (nEditContentLen == 0) return FALSE;

	// Check if the waiting time is between 1000 and 100000.
	if (nEditContentLen < 4) // Less than 1000.
	{
		// Set the szNewSelection text to 1000.
		_tcscpy_s(szNewSelection, 5, L"1000");
		SetWindowText(hEditWaitingTime, L"1000");

		return TRUE;
	}
	if (nEditContentLen > 6) // Greater than 100000.
	{
		// Set the szNewSelection text to 100000.
		_tcscpy_s(szNewSelection, 7, L"100000");
		SetWindowText(hEditWaitingTime, L"100000");

		return TRUE;
	}

	// Returns length of the copied string in characters if successfull,
	// else 0 if the handle is invalid or field is empty.
	INT nSuccess = GetWindowText(hEditWaitingTime, szNewSelection, nEditContentLen + 1); // + 1 for null-terminating char.

	if (nSuccess == 0) return FALSE;

	return TRUE;
}

BOOL SettingWindow::Browse(TCHAR* szNewSelection, CONST TCHAR* szCurrentSelection , INT valueToChange)
{

	if (valueToChange == SWM_CHANGEWT)
		return GetWaitingTime(szNewSelection);
	else if (valueToChange == SWM_CHANGEPRI)
		return BrowsePrinter(szNewSelection, szCurrentSelection);
	else
		return BrowseDirectory(szNewSelection, szCurrentSelection);

	// Probably program will never reach the below line.
	return FALSE;
}

void SettingWindow::SetNewSelection(INT change, TCHAR* path)
{
	switch (change)
	{
	case SWM_CHANGEIN:
	{
		Write(m_SettingDivision[0].m_Edit, path);
		m_ChangedSetting = m_ChangedSetting | MASK_INPUTFLAG;
	}
	break;
	case SWM_CHANGEOUT:
	{
		Write(m_SettingDivision[1].m_Edit, path);
		m_ChangedSetting = m_ChangedSetting | MASK_OUTPUTFLAG;
	}
	break;
	case SWM_CHANGEERR:
	{
		Write(m_SettingDivision[2].m_Edit, path);
		m_ChangedSetting = m_ChangedSetting | MASK_ERRORFLAG;
	}
		break;
	case SWM_CHANGEPRI:
	{
		Write(m_SettingDivision[3].m_Edit, path);
		m_ChangedSetting = m_ChangedSetting | MASK_PRINTERFLAG;
	}
	break;
	case SWM_CHANGEWT:
	{
		Write(m_SettingDivision[4].m_Edit, path);
		m_ChangedSetting = m_ChangedSetting | MASK_WTIMEFLAG;
	}
	break;
	default:
		break;
	}
}

void SettingWindow::DrawDivisionIcon()
{
	for (int i = 0; i < 5; i++)
	{
		PAINTSTRUCT ps;
		HWND hDivStaticIconHwnd = m_SettingDivision[i].m_StaticIcon;
		HDC hdc = BeginPaint(hDivStaticIconHwnd, &ps);
		DrawIconEx(hdc, 0, 0, m_hQuestionMarkIcon, nQuestionMarkSize, nQuestionMarkSize, 0, NULL, DI_NORMAL);
		EndPaint(hDivStaticIconHwnd, &ps);
	}

}

BOOL SettingWindow::Write(HWND hEdit, LPCWSTR lpwText)
{
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)_T(""));
	SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)lpwText);
	return true;
}

void SettingWindow::LoadAssets()
{
	// Fonts for lables i.e. Input path and Output path.
	m_Fonts[0] = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
	// Fonts for text inside the edit control boxes.
	m_Fonts[1] = CreateFont(20, 0, 0, 0, FW_NORMAL, TRUE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Consolas"));

	// Color for lables i.e. Input path and Output path.
	m_Brushes[0] = CreateSolidBrush(RGB(255, 255, 255));

	// Color for text inside the edit control boxes.
	m_Brushes[1] = CreateSolidBrush(RGB(240, 240, 240));

	// Load the question mark icon.
	m_hQuestionMarkIcon = (HICON)LoadImage(
		m_hInstance,
		MAKEINTRESOURCE(IDI_QUESTION_MARK),
		IMAGE_ICON,
		nQuestionMarkSize,
		nQuestionMarkSize,
		LR_SHARED
	);


}

void SettingWindow::ReleaseAssets()
{
	// Delete font objects.
	DeleteObject(m_Fonts[0]);
	DeleteObject(m_Fonts[1]);

	// Delete brush objects.
	DeleteObject(m_Brushes[0]);
	DeleteObject(m_Brushes[1]);

	// Delete question mark icon.
	DestroyIcon(m_hQuestionMarkIcon);

}

void SettingWindow::AddToolTipInfo(HWND hDlg, HWND hTool, LPWSTR pszTip)
{	
	TOOLINFO toolInfo = { 0 };
	toolInfo.cbSize = TTTOOLINFO_V1_SIZE;
	toolInfo.hwnd = hDlg;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.uId = (UINT_PTR)hTool;
	toolInfo.lpszText = pszTip;
	toolInfo.hinst = GetModuleHandle(NULL);

	// Get the coordinates of the tool
	GetClientRect(hTool, &toolInfo.rect);
	// Associate the tooltip with the tool.
	if (!SendMessage(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo))
	{
		MessageBox(NULL, TEXT("TTM_ADDTOOL failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
	}

}

BOOL SettingWindow::CreateSettingPage(HWND hWnd)
{
	// Create a tooltip window.
	 // Create the tooltip window
	m_hToolTip = CreateWindow(
		TOOLTIPS_CLASS, NULL,
		WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hWnd, NULL, GetModuleHandle(NULL), NULL);

	if (!m_hToolTip)
	{
		MessageBox(NULL, TEXT("Tooltip creation failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
	}
	else
	{
		// Activate the tooltip.
		SendMessage(m_hToolTip, TTM_ACTIVATE, TRUE, 0);
	}


	// Get the parent (setting window)'s height and width.
	RECT rect; // To store the size of the client area of the setting window.
	GetClientRect(hWnd, &rect);

	// Positions, height and width.
	// Initial X position of first element in the page.
	INT initXpos = 50;
	// Current X position.
	INT currentXpos = initXpos;
	// Initial Y position of all elements in the page.
	INT initYpos = 20;
	// Width of the lable static edit control.
	INT lableWidth = 100;
	// Width of the question mark icon.
	INT iconWidth = 16;
	// Width of the edit control, which is 50% of the parent window.
	INT editWidth = .6 * (rect.right - rect.left);
	// Width of the buttons.
	INT buttonWidth = 100;
	// Default height of all elements in the page.
	INT defHeight = 25;
	// Vertical gap between elements.
	INT defVerticalGap = 10;
	// Horizontal gap between elements.
	INT defHorizontalGap = 50;

	// For Apply and Cancle button only.
	INT actionButtonX = initXpos + lableWidth + editWidth - (buttonWidth / 2);
	INT actionButtonY= rect.bottom - defHeight * 2;

	// lpSTYLE is used to create either read only or read and write only.
	auto DrawElements = [&](INT index, CONST TCHAR* lableText, CONST TCHAR* lableValue, int buttonAction, long lpSTYLE = ES_READONLY)
	{
		// Create lable.
		m_SettingDivision[index].m_Lable = CreateWindow(TEXT("STATIC"), lableText, WS_CHILD | WS_VISIBLE | ES_READONLY, currentXpos, initYpos, lableWidth, defHeight, hWnd, (HMENU)IDC_SETTINGLABLE, NULL, NULL);

		// Change current x position, to create distance between lable and question mark icon.
		// No space between lable and question mark icon.
		currentXpos += lableWidth;

		// Create a container on which the icon is drawn and tooltip is shown.
		m_SettingDivision[index].m_StaticIcon = CreateWindow(
			WC_STATIC,
			NULL,
			WS_VISIBLE | WS_CHILD | SS_ICON | SS_NOTIFY,
			currentXpos,
			initYpos + 2,
			nQuestionMarkSize,
			nQuestionMarkSize,
			hWnd,
			NULL,
			NULL,
			NULL
		);

		// Load the text from string table to display as tip.
		TCHAR szTip[200]; // Need to decide the maximum buffer size.
		LoadString(GetModuleHandle(NULL), IDS_SETTINGTIP + index, szTip, 200);

		// Add the tool info to the tooltip.
		AddToolTipInfo(hWnd, m_SettingDivision[index].m_StaticIcon, szTip);

		// Change current x position, to create distance between lable/icon and edit control.
		currentXpos += iconWidth + defHorizontalGap;

		// Create edit controls.
		m_SettingDivision[index].m_Edit = CreateWindow(_T("EDIT"), lableValue, WS_CHILD | WS_VISIBLE | lpSTYLE | ES_LEFT | WS_BORDER, currentXpos, initYpos, editWidth, defHeight, hWnd, (HMENU)IDC_SETTINGEDITBOX, NULL, NULL);

		// Change current x position, to create distance between edit control and button.
		currentXpos += editWidth + defHorizontalGap;

		// Create buttons.
		m_SettingDivision[index].m_Button = CreateWindow(L"BUTTON", L"Change", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, currentXpos, initYpos, buttonWidth, defHeight, hWnd, (HMENU)buttonAction, NULL, NULL);

		// Change y position after every lable, edit, and button drawn horizontally.
		initYpos += defHeight + defVerticalGap;

		// Reset the current x position to initial x position, for next drawing of lable, edit, and button.
		currentXpos = initXpos;

		// Change the fonts of lables, edit controls, and buttons.
		SendMessage(m_SettingDivision[index].m_Lable, WM_SETFONT, (WPARAM)m_Fonts[0], MAKELPARAM(TRUE, 0));
		SendMessage(m_SettingDivision[index].m_Edit, WM_SETFONT, (WPARAM)m_Fonts[1], MAKELPARAM(TRUE, 0));
		SendMessage(m_SettingDivision[index].m_Button, WM_SETFONT, (WPARAM)m_Fonts[0], MAKELPARAM(TRUE, 0));
	};

	DrawElements(0, TEXT("Input path:"), CurrentSettings.input_directory, SWM_CHANGEIN);
	DrawElements(1, TEXT("Output path:"), CurrentSettings.output_directory, SWM_CHANGEOUT);
	DrawElements(2, TEXT("Error path:"), CurrentSettings.error_directory, SWM_CHANGEERR);
	DrawElements(3, TEXT("Printer:"), CurrentSettings.current_printer, SWM_CHANGEPRI);
	DrawElements(4, TEXT("Time:"), CurrentSettings.waiting_time, SWM_CHANGEWT, ES_NUMBER);

	m_Buttons[0] = CreateWindow(L"BUTTON", L"Apply", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, actionButtonX, actionButtonY, buttonWidth, defHeight, hWnd, (HMENU)SWM_APPLYSET, NULL, NULL);
	// Increment the actionButtonX to space between Apply & Cancle button
	actionButtonX += defHorizontalGap + buttonWidth;
	m_Buttons[1] = CreateWindow(L"BUTTON", L"Cancle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, actionButtonX, actionButtonY, buttonWidth, defHeight, hWnd, (HMENU)SWM_CANCLESET, NULL, NULL);

	// Change the fonts of the remaining two buttons.
	SendMessage(m_Buttons[0], WM_SETFONT, (WPARAM)m_Fonts[0], MAKELPARAM(TRUE, 0));
	SendMessage(m_Buttons[1], WM_SETFONT, (WPARAM)m_Fonts[0], MAKELPARAM(TRUE, 0));

	// Initially, disable the apply button.
	EnableWindow(m_Buttons[0], FALSE);

	return TRUE;
}



/*
BOOL SettingWindow::GetWaitingTime(TCHAR* szNewSelection)
{
	// Change waiting time.
	HWND hEditWaitingTime = m_SettingDivision[4].m_Edit;

	// Get the length in characters of the edit control box.
	INT nEditContentLen = GetWindowTextLength(hEditWaitingTime);

	// 0 when the field is empty or if the function fails.
	if (nEditContentLen == 0) return FALSE;

	// Check if the waiting time is between 1000 and 100000.
	if (nEditContentLen < 4) // Less than 1000.
	{
		// Set the szNewSelection text to 1000.
		_tcscpy_s(szNewSelection, 5, L"1000");

		return TRUE;
	}
	if (nEditContentLen > 6) // Greater than 100000.
	{
		// Set the szNewSelection text to 100000.
		_tcscpy_s(szNewSelection, 7, L"100000");

		return TRUE;
	}


	// Incase, if the waiting time was out of range then get the new length after setting the values.
	nEditContentLen = GetWindowTextLength(hEditWaitingTime);

	// Returns length of the copied string in characters if successfull,
	// else 0 if the handle is invalid or field is empty.
	INT nSuccess = GetWindowText(hEditWaitingTime, szNewSelection, nEditContentLen + 1); // + 1 for null-terminating char.

	if (nSuccess == 0) return FALSE;

	return TRUE;
}

*/