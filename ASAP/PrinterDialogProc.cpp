#include "Setting.h"

INT_PTR CALLBACK SettingWindow::PrinterDialogProc(_In_ HWND hDlg, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	int wmId, wmEvent;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{

		// lParam is the pointer to the address where the current selected printer is stored.
		// Store the current state in the szCurrentSelection pointer.

		CONST TCHAR* szCurrentSelection = reinterpret_cast<CONST TCHAR*>(lParam);

		// If the state cannot be retrieved, close the window.
		if (szCurrentSelection == NULL)
		{
			SendMessage(hDlg, WM_CLOSE, (WPARAM)NULL, lParam);
			break;
		}
		
		// Get the handle to the list box.
		HWND hWndList = GetDlgItem(hDlg, IDC_LISTBOX);

		// Get the mounted printers.
		MountedPrinters printers;
		BOOL bStatus = Printer::GetMountedPrinters(printers);

		if (bStatus) // True then show printers list else show no printers present on the system or try again.
		{
			for (int i = 0; i < printers.m_Entries; i++)
			{
				// Add the item string
				int pos = (int)SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)printers.m_PrinterList[i]);

				// Set the item data to the item index
				SendMessage(hWndList, LB_SETITEMDATA, pos, (LPARAM)i);
			}

			// Clear the memory held by printers structure.
			for (int i = 0; i < printers.m_Entries; i++)
			{
				delete[] printers.m_PrinterList[i];
			}

			delete printers.m_PrinterList;
		}
		else
		{
			int pos = (int)SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)L"No printers found!");

			// Set the item data to the item index
			SendMessage(hWndList, LB_SETITEMDATA, pos, (LPARAM)0);
		}

		SetFocus(hWndList);
		SendMessage(hWndList, LB_SETCURSEL, 0, 0);

		return FALSE;
	}
	case WM_VKEYTOITEM:
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case 0x1B:
		{
			MessageBox(NULL, L"ESC key pressed.", L"Info", MB_OK);
			break;
		}
		default:
			return -1;
		}

		return -2;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_CANPRINTERBTN:
		{

			SendMessage(hDlg, WM_CLOSE, (WPARAM)NULL, lParam);
			return TRUE;
		}
		case IDC_SELPRINTERBTN:
		{
			// Get the handle of the list box.
			HWND hwndList = GetDlgItem(hDlg, IDC_LISTBOX);

			//Get the index of the selected item.
			int index = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);

			// Allocate memory to store the printer name.
			// The memory will be released later outside of this dialog box.
			TCHAR* szNewSelection = new TCHAR[_MAX_PATH];

			// Get the selection and store it, will automatically be null terminated.
			SendMessage(hwndList, LB_GETTEXT, index, (LPARAM)szNewSelection);

			// Close the dialog box and return the new selections as INT_PTR.
			SendMessage(hDlg, WM_CLOSE, (WPARAM)szNewSelection, lParam);
			return TRUE;
		}
		case IDC_LISTBOX:
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK:
				SendMessage(GetDlgItem(hDlg, IDC_SELPRINTERBTN), BM_CLICK, NULL, NULL);
				break;
			default:
				break;
			}

			break;
		}
		}
		return FALSE;
	}
	case WM_CTLCOLORLISTBOX:
	{
		SetBkColor((HDC)wParam, RGB(240, 240, 240));
		// Set the font to Arial bold 20
		// Return the handle of the white brush
		return (INT_PTR)CreateSolidBrush(RGB(240, 240, 240));
	}
	return FALSE;
	case WM_CLOSE:
		EndDialog(hDlg, wParam);
		return TRUE;
	default:
		return FALSE;
	}
}