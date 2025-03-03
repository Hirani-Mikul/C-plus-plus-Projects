#pragma once
#include <ShObjIdl.h>

#include "resource.h"
#include "utils.h"
#include "Printer.h"

class SettingWindow
{
public:
	// There is no default constructor.
	SettingWindow() = delete;

	// Requires handle to the parent window and current setting's reference.
	SettingWindow(_In_ HWND, _In_ CONST AppSettings&);

public:
	CONST HWND GetSettingWndHandle();
private:
	BOOL RegisterSettingWindow();
	BOOL CreateSettingWindow();

private:

	//Browse windows directory to select paths.
	//@param 1: TCHAR*: address of the memory to store new retrieved selected path.
	//@param 2: CONST TCHAR*: pointer to the current path stored in the app settings struct.
	BOOL BrowseDirectory(TCHAR*, CONST TCHAR*);

	//Browse mounted printers to select one printer.
	//@param 1: TCHAR*: address of the memory to store new retrieved selected printer.
	//@param 2: CONST TCHAR*: pointer to the current printer stored in the app settings struct.
	BOOL BrowsePrinter(TCHAR*, CONST TCHAR*);

	//Get the content of the edit control box of waiting time.
	//@param 1: TCHAR*: address of the memory to store new retrieved waiting time.
	BOOL GetWaitingTime(TCHAR*);

	//Intermidiary method to either select path or printer.
	//@param 1: TCHAR*: address of the memory to store new retrieved selected value.
	//@param 2: CONST TCHAR*: pointer to the current value stored in the app settings struct.
	//@param 2: INT - represents which edit control box needs to be updated i.e printer or paths.
	BOOL Browse(TCHAR*, CONST TCHAR*, INT);

	// Once the path or printer is fetched, the edit control boxes are updated.
	// m_ChangedSetting is masked to turn on the flag for corresponding setting value change.
	// @param 1: INT - represents which edit control box needs to be updated.
	// @param 2: TCHAR* - stores new selected path.
	void SetNewSelection(INT, TCHAR*);

	// Draw question mark after each lable for every division.
	void DrawDivisionIcon();

	// Used to fetch the current settings of the application i.e. paths and printer.
	//BOOL LoadCurrentSettings();

	// Used to save the new settings to the config file.
	//BOOL SaveNewSettings();

	// Used to write to edit controls.
	// @param 1: HWND - edit control in which to write.
	// @param 2: LPCWSTR - text which needs to be written. 
	BOOL Write(HWND, LPCWSTR);

	// Load fonts, brushes, and icon. Executed under WM_CREATE.
	void LoadAssets();
	// Release fonts, brushes, and icon. Executed under WM_CLOSE.
	void ReleaseAssets();

	// Creates a tool tip for each lable.
	// @param 1: HWND - window handle of the dialog box.
	// @param 3: HWND - window handle of icon container.	
	// @param 4: LPWSTR - string to use as the tooltip text.	
	void AddToolTipInfo(HWND, HWND, LPWSTR);
	
	// Create content to display on client area.
	// @param 1: HWND - window handle of the dialog box.	
	BOOL CreateSettingPage(HWND);

	// Setting window procedure handler.
	static INT_PTR CALLBACK SettingWndProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);

	// Printer selection dialog box procedure handler.
	static INT_PTR CALLBACK PrinterDialogProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);

private:
	// Container for lable, static edit/edit control, and an action button.
	// Each setting parameter has it's own container.
	CONST INT nQuestionMarkSize = 16;

	struct SettingDivision
	{
		HWND m_Lable = NULL; // Lable for the field.
		HWND m_Edit = NULL; // Field to show the current value/setting.
		HWND m_Button = NULL; // Action button to change the current value/setting.
		HWND m_StaticIcon = NULL; // Static handle to the container of the question mark icon.
	};

private:
	// The setting window's class name. Maximum length 256.
	TCHAR m_szWindowClass[_MAX_FNAME];
	
	// The string that appears in the setting window's title bar. Maximum length 256.
	TCHAR m_szTitle[_MAX_FNAME];

	// The current INSTANCE of setting window.
	HINSTANCE m_hInstance;
	// The previous INSTANCE of setting window.
	HINSTANCE m_hPrevInstance;
	
	// HWND to the parent of setting window.
	HWND m_hParenthWnd;
	
	// HWND of the client area of the setting window.
	HWND m_hSettinghWnd;

	// Content of the setting window.
	HWND m_Buttons[2]; // Buttons for apply and cancle action.
	SettingDivision m_SettingDivision[5];

	// Fonts and brushes to paint setting window's content.
	HFONT m_Fonts[2]; 
	HBRUSH m_Brushes[2];


	HICON m_hQuestionMarkIcon; // Icon for question mark symbol.
	HWND m_hToolTip; // Handle to the tooltip window.

	// To store changed settings.
	AppSettings m_NewSettings;

	// Constant pointer to the current application settings.
	CONST AppSettings &CurrentSettings;

	// Used for storing state of which setting was changed.
	// Last 5 bits represents whether any of the setting value was changed.
	// First 3 are not used.
	CHAR m_ChangedSetting;

};

