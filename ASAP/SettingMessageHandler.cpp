#include "Setting.h"

/*
	SETTING WINDOW PROCEDURE HANDLER.

	-> Handles all messages sent to the setting window.
*/


LRESULT CALLBACK SettingWindow::SettingWndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	SettingWindow* pSettingState = NULL;

	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case SWM_CHANGEIN:
		case SWM_CHANGEOUT:
		case SWM_CHANGEERR:
		case SWM_CHANGEPRI:
		case SWM_CHANGEWT:
		{

			pSettingState = (SettingWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pSettingState == NULL) break;

			// Pointer to the already declared variable, where changed path will be stored.
			TCHAR* szNewSelection = 
				wmId == SWM_CHANGEIN ? pSettingState->m_NewSettings.input_directory :
				(wmId == SWM_CHANGEOUT ? pSettingState->m_NewSettings.output_directory :
					(wmId == SWM_CHANGEERR ? pSettingState->m_NewSettings.error_directory :
						(wmId == SWM_CHANGEPRI ? pSettingState->m_NewSettings.current_printer : 
							(wmId == SWM_CHANGEWT ? pSettingState->m_NewSettings.waiting_time : NULL))));

			// The current text in the edit control box is the starting location when browsing.
			CONST TCHAR* szCurrentSelection = 
				wmId == SWM_CHANGEIN ? pSettingState->CurrentSettings.input_directory :
				(wmId == SWM_CHANGEOUT ? pSettingState->CurrentSettings.output_directory :
					(wmId == SWM_CHANGEERR ? pSettingState->CurrentSettings.error_directory :
						(wmId == SWM_CHANGEPRI ? pSettingState->CurrentSettings.current_printer : 
							(wmId == SWM_CHANGEWT ? pSettingState->CurrentSettings.waiting_time : TEXT("C:\\")))));

			BOOL bStatus = pSettingState->Browse(szNewSelection, szCurrentSelection, wmId);
			
			// Disable setting window when browsing directory, to aviod browsing another setting.
			EnableWindow(pSettingState->m_hSettinghWnd, FALSE);

			if (bStatus)
			{
				// Compare if the new value is same as current using _tcscmp().
				// < 0: means szNewSelection is less than szCurrentSelection.
				// 0: means both values are identical.
				// > 0: means szNewSelection is greater than szCurrentSelection.
				if (_tcscmp(szNewSelection, szCurrentSelection) != 0) 
				{
					pSettingState->SetNewSelection(wmId, szNewSelection);
					// Enable the apply button.
					EnableWindow(pSettingState->m_Buttons[0], TRUE);
				}

			}

			// Enable setting window after browsing directory, to browse another setting.
			EnableWindow(pSettingState->m_hSettinghWnd, TRUE);
			SetFocus(pSettingState->m_hSettinghWnd);
			SetForegroundWindow(pSettingState->m_hSettinghWnd);
		}
			break;
		case SWM_APPLYSET:
		{
			pSettingState = (SettingWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (pSettingState == NULL) break;
			// Send message to main window handler to save settings.
			SendMessage(pSettingState->m_hParenthWnd, SWM_SAVENEWSETTINGS, (WPARAM)pSettingState->m_ChangedSetting, (LPARAM) & (pSettingState->m_NewSettings));
			// After applying the setting, disable the button again.
			EnableWindow(pSettingState->m_Buttons[0], FALSE);

			// Reset the new setting values.
			pSettingState->m_NewSettings.input_directory[0] = L'\0';
			pSettingState->m_NewSettings.output_directory[0] = L'\0';
			pSettingState->m_NewSettings.error_directory[0] = L'\0';
			pSettingState->m_NewSettings.current_printer[0] = L'\0';
			pSettingState->m_NewSettings.waiting_time[0] = L'\0';

			// Reset the bits to 0 of m_ChangedSetting.
			pSettingState->m_ChangedSetting = 0b00000000;
			
		}
			break;
		case SWM_CANCLESET:
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;
		default:
			break;
		}
		break;
	case WM_CREATE:
	{
		// lParam is the current state of the settings.
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		// Store the current state in the pSettingState pointer.
		pSettingState = reinterpret_cast<SettingWindow*>(pCreate->lpCreateParams);

		// If the state cannot be retrieved, close the window.
		if (pSettingState == NULL)
		{
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;
		}

		// Save the pSettingState in the setting window's user data.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pSettingState);




		// Load fonts, brushes, and icons.
		pSettingState->LoadAssets();

		// Create setting page contents.
		pSettingState->CreateSettingPage(hWnd);


		// Write the current settings in the edit control boxes.
		//pSettingState->Write(pSettingState->m_Edits[0], L"C:\\Users\\HIRANI\\Desktop\\Windows API\\Test\\IN");
		//pSettingState->Write(pSettingState->m_Edits[1], L"C:\\Users\\HIRANI\\Desktop\\Windows API\\Test\\OUT");
		//pSettingState->Write(pSettingState->m_Edits[2], L"C:\\Users\\HIRANI\\Desktop\\Windows API\\Test\\ERROR");
		//pSettingState->Write(pSettingState->m_Edits[3], L"Microsoft XPS Document Writer");
		// Disable the apply button.
	}
	break;
	case WM_CTLCOLORSTATIC:
	{
		//IDC_SETTINGLABLE
		//	IDC_SETTINGEDITBOX
		//	IDC_SETTINGBUTTON
		pSettingState = (SettingWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pSettingState == NULL) return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));

		HDC hdc = (HDC)wParam; // HDC object of control.
		HWND hwnd = (HWND)lParam; // HANDLE of control.

		INT controlId = GetDlgCtrlID(hwnd); // Returns the unique identifier for each contorl. i.e. if it's IDC_SETTINGLABLE or IDC_SETTINGEDITBOX

		if (controlId == IDC_SETTINGLABLE)
		{
			SetTextColor(hdc, RGB(0, 0, 0));

			return (INT_PTR)pSettingState->m_Brushes[0];
		}
		else if (controlId == IDC_SETTINGEDITBOX)
		{
			SetTextColor(hdc, RGB(80, 80, 80));

			return (INT_PTR)pSettingState->m_Brushes[1];
		}

		return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));
	}

	case WM_PAINT:
	{
		pSettingState = (SettingWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pSettingState != NULL)
		{
			// Draw icons on the setting page.
			pSettingState->DrawDivisionIcon();
		}
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
	case WM_CLOSE:
	{
		pSettingState = (SettingWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pSettingState != NULL)
		{
			pSettingState->ReleaseAssets();
			//EnableWindow(pSettingState->m_hParenthWnd, TRUE);
			SendMessage(pSettingState->m_hParenthWnd, CLOSESETTING, NULL, NULL);
		}
		DestroyWindow(hWnd);
		break;
	}
	default:
		// Without the return value here, the creation of window will fail with error code 0.
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
