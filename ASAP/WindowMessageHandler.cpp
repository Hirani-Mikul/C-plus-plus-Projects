#include "Application.h"

/*
	MAIN WINDOW PROCEDURE HANDLER.

	-> Handles all messages sent to the main window.
*/

LRESULT CALLBACK Application::WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	//StateInfo* pState = NULL;
	Application* pAppState = NULL;

	int wmId, wmEvent;

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		pAppState = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pAppState == NULL) break;
		pAppState->CreateSettingWindow();

		break;
	}
	case CLOSESETTING:
	{
		// Delete the dynamically created setting object and set it to null.
		pAppState = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pAppState != NULL)
		{
			delete pAppState->m_SettingWindow;
			pAppState->m_SettingWindow = NULL;
			EnableWindow(hWnd, TRUE);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
		}

		Logger.Write("Setting window closed!");
		break;
	}
	case SWM_SAVENEWSETTINGS:
	{
		// Save the settings to the current setting.
		CONST AppSettings* sat1 = (AppSettings*)(lParam);
		// Represents the flags for each setting changed.
		CHAR ChangedSetting = (CHAR)(wParam);
		pAppState = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pAppState == NULL) break;

		// Write the settings to the config file.
		pAppState->SaveApplicationSettings(*sat1);

		// If input path or waiting time was changed, returns 1 else 0.
		if ((ChangedSetting & MASK_INPUTFLAG) || (ChangedSetting & MASK_WTIMEFLAG)) 
		{
			// Need to restart the directory watcher.

		}
	}
	break;
	case SWM_TRAYMSG: // Triggered when system tray icon is hovered over.
		switch (lParam)
		{
		case WM_LBUTTONDBLCLK:
			ShowWindow(hWnd, SW_RESTORE);
			break;
		case WM_RBUTTONDOWN:
		case WM_CONTEXTMENU:
		{
			pAppState = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pAppState != NULL)
			{
				pAppState->AddContextMenu(hWnd);
			}
		}
		default:
			break;
		}
		break; 

	case FILEFOUND:
	{

		/****************************** IMPORTANT **************************/
		/*
					IF THE APPLICATION IS IN PAUSE STATE:
					THEN IT SHOULD JUST RETURN AND NOT PROCESS ANY FILE.

					HOWEVER, WHEN RESUMED, IT SHOULD CHECK FOR THE FILES IN THE LIST.
					IF ANY FILE EXISTS, IT SHOULD BE PRINTED.
		*/
		
		Logger.Write((LPCWSTR)lParam);

		// Insert the file name into the list.
		FileManager::InsertFile((LPCWSTR)lParam);

		pAppState = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		pAppState->PrintFiles();
	
		// int num = 1, 2, 3, 4, 5
	}
	break;
		case WM_COMMAND:
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			pAppState = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pAppState == NULL) break;

			switch (wmId)
			{
				case SWM_SHOW:
					ShowWindow(hWnd, SW_RESTORE);
					Logger.Write("Window restored!");
					break;
				case SWM_HIDE:
				case IDOK:
					Logger.Write("Window minimized!");
					ShowWindow(hWnd, SW_HIDE);
					break;
				case SWM_PAUSE:
					pAppState->SetCurrentState(PAUSED);
					break;
				case SWM_RESUME:
					pAppState->SetCurrentState(RUNNING);
					break;
				case SWM_RESTART:
					// Post message to the WndProc to close with lParam as 99.
					Exit_Code = (DWORD)99;
					PostMessage(hWnd, WM_CLOSE, NULL, NULL);
					break;
				case SWM_SETTING:
					pAppState->CreateSettingWindow();

					break;
				case SWM_EXIT:
					Logger.Write("Application about to close!");
					PostMessage(hWnd, WM_CLOSE, NULL, NULL);
					break;
				default:
					break;
			}
			return 1; 
	case WM_CREATE:
	{
		// lParam is the current state of the application.
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pAppState = reinterpret_cast<Application*>(pCreate->lpCreateParams);

		// Save the pAppState in the window's user data.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pAppState);

		//bSuccess = InitNotificationIcon(1);
		// Load assets.
		pAppState->LoadAssets(hWnd);

		pAppState->InitNotificationIcon(1, hWnd);

		// Create a TextBox to replicate the design of console application.
		// The TextBox is read-only 

		Logger.CreateEdit(hWnd);

		//Logger.Write("Program Started!");
		//Logger.Write(L"UTF-8: Program Started!");
		Logger.Write(pAppState->m_lpCommandLine);
		//SendMessage(hWnd, WM_COMMAND, SWM_SETTING, NULL);

		//pAppState->m_TextBox.setEdit(CreateWindow(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | ES_READONLY | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hWnd, NULL, NULL, NULL));

		//pAppState->m_TextBox.Write("Program Started!");
		//pAppState->m_TextBox.Write(L"UTF-8: Program Started!");


		//std::function<BOOL(LPCWSTR)> Logger = std::bind(&TextBox::Log, &pAppState->m_TextBox, std::placeholders::_1);

		//Printer::Initialize(std::bind(&TextBox::Log, &pAppState->m_TextBox, std::placeholders::_1));

	}
	break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hdc = (HDC)wParam;

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));
		return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));
	}

	case WM_CLOSE:
	{

		pAppState = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pAppState != NULL)
		{
			pAppState->Exit();

		}

		DestroyWindow(hWnd);
		//Sleep(3000);
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

