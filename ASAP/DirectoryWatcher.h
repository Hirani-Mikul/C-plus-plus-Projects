#pragma once
#include <Windows.h>
#include <unordered_map>
#include <tchar.h>
#include <strsafe.h>

#include "utils.h"
#include "List.h"
#include "FileManager.h"

extern Console console;

/*
	WATCHES FOR CHANGES IN FILES IN THE SPECIFIED DIRECTORY
*/
class DirectoryWatcher
{
public:
	DirectoryWatcher();

	~DirectoryWatcher();

public:
	static DWORD WINAPI Monitor(LPVOID param);

	// Initiate the watcher class.
	BOOL Initiate(HWND*, CONST TCHAR*);

	// Set the current state of the directory watcher.

	BOOL Pause();

	BOOL Resume();

	BOOL Stop();

	void SetWaitingTime(CONST TCHAR*);


private:

	// Monitors directory infinitely.
	DWORD Monitor(void);


private:

	// Handle received from ReadDirectoryChangesW.
	HANDLE m_hDirectory;

	OVERLAPPED m_Overlapped;
	// Handle to the main window.
	HWND* m_MainHwnd;
	// Handle to the event used to trigger pause or resume state.
	HANDLE m_EventPause;
	// The current state of the class; if true, the input directory is being watched.
	BOOL m_isWatching;
	// Number of milliseconds to pause the monitoring thread before reading the next changes in the directory.  
	INT m_WaitingTime;

};

