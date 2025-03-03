#pragma once
/*
	Cpp files that includes the implementation of some of the functionality required by this class.
	=> Application.cpp - the main cpp file for Application.h
	=> WindowMessageHandler.cpp - stores the code for main application window procedure.
	=> SettingConfiguration.cpp - stores the code for reading, writing application settings.

*/

#include <iostream>
#include <unordered_map>
#include <atlstr.h>
#include <sysinfoapi.h>

#include "resource.h"
#include "utils.h"
#include "TextBox.h"
#include "Console.h"
#include "DirectoryWatcher.h"
#include "Printer.h"
#include "Setting.h"
// FOR DEBUGGING PURPOSE
#include <string>

#define SWM_TRAYMSG WM_APP

extern Console console;
extern TextBox Logger;

class Application
{
public:
	// Delete the default constructor
	Application() = delete;

	Application(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PWSTR);

	// Destructor to clean up memory
	~Application();

public:

	INT Initiate();
	BOOL Start();
	BOOL Pause();
	BOOL Resume();
	BOOL Stop();
	BOOL Exit();
	BOOL CreateSettingWindow();

	BOOL RegisterWindow();
	BOOL CreateClientWindow();
	BOOL InitNotificationIcon(INT nCmdShow, HWND hWnd);
	BOOL UpdateNotificationIcon(INT nIconIndex);
	BOOL AddContextMenu(HWND);
	BOOL PrintFiles();

	BOOL WriteLogFile();

	// Main window procedure handler.
	static LRESULT CALLBACK WndProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);

private:

	// Methods to read, write and verify settings.
	BOOL LoadApplicationSettings(); // Load settings from config file.
	BOOL VerifyApplicationSettings(); // Verify loaded or saved settings.
	BOOL WriteApplicationSettings(); // Write settings to config file
	
	//Re-write new settings to current setting struct.
	//@param 1: CONST AppSettings&: address to the new setting struct which is stored in SettingWindow class.
	BOOL SaveApplicationSettings(CONST AppSettings&); 

	// Loading & destroying of resources i.e. icons, fonts and etc.
	BOOL LoadAssets(HWND hWnd);
	BOOL DestroyAssets();

	// Utility methods that help in writing and reading settings.
	
	// Writes the setting's buffer to the config file.
	BOOL _WriteSettingsToFile(CONST TCHAR* szBuffer, INT nBufferLen);
	TCHAR* _ReadSettingsFromFile();
	INT _GetHeaderLine(CONST TCHAR* szBuffer, INT(&positions)[MAXHEADERVALUES]);
	BOOL _ParseSettings(CONST TCHAR* szBuffer, CONST INT(&positions)[MAXHEADERVALUES]);

private:
	struct StateInfo {
		// Members
		TextBox *textbox = NULL;

	};

	enum STATE {
		RUNNING = 0,
		PAUSED,
		STOPPED
	};

	void SetCurrentState(STATE);


private:
	// The main window class name.
	static TCHAR szWindowClass[];
	// The string that appears in the application's title bar.
	static TCHAR szTitle[];

	// The current INSTANCE of application.
	HINSTANCE m_hInstance;
	// The previous INSTANCE of application.
	HINSTANCE m_hPrevInstance;
	// HWND of the client area of the window.
	HWND m_hWnd;
	// NOTIFYICONDATA to add icon to system tray.
	NOTIFYICONDATA m_Nid;

	DirectoryWatcher m_Watcher;

	// HANDLE of the worker thread. (Directory Watcher)
	HANDLE m_hWatcherThread;

	STATE m_CurrentState;

	HICON m_AppIcons[4];

	TCHAR* m_lpCommandLine;

	SettingWindow* m_SettingWindow;

	AppSettings m_Settings;
};

