#include "DirectoryWatcher.h"

DirectoryWatcher::DirectoryWatcher() : m_hDirectory{ INVALID_HANDLE_VALUE }, m_Overlapped{ { 0 } }, m_MainHwnd{ NULL }, m_WaitingTime { 1000 }
{
	/*
		- The default waiting time is 2000 millisecond.
		- During the launch, m_isWatching is FALSE.
	*/
	m_EventPause = CreateEventA(
		NULL, 
		TRUE, // Creates a manual-reset event object.
		TRUE, // Initial state of the event object is signaled.
		NULL
	);


	m_isWatching = FALSE;
}

DirectoryWatcher::~DirectoryWatcher()
{
	if (!MONITORMODE) return;
	// Make sure the event is signalled.
	CloseHandle(m_Overlapped.hEvent);

	if (m_hDirectory != INVALID_HANDLE_VALUE)
		CloseHandle(m_hDirectory);
}

DWORD DirectoryWatcher::Monitor()
{
	if (!MONITORMODE) return 0;

	DWORD buffer[1024]; // Buffer to store file changes.

	DWORD dwBytesReturned; // Number of bytes written to buffer.

	BOOL bSuccess = ReadDirectoryChangesW(
		m_hDirectory,
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
		&m_Overlapped,
		NULL
	);

	/*
		THE FOLLOWING EVENTS ARE TRIGGERED:


		Event: 2 - FILE_ACTION_REMOVED

		Event: 1 - FILE_ACTION_ADDED

		Event: 3 - FILE_ACTION_MODIFIED

		Event: 3 - FILE_ACTION_MODIFIED
	
	*/

	while (m_isWatching) // Must be checked using some variable.
	{
		if (!bSuccess) break;

		Sleep(m_WaitingTime);

		// Wait for change notification from ReadDirectoryChangesW.
		DWORD dwWaitResult;
		
		dwWaitResult = WaitForSingleObject(m_Overlapped.hEvent, INFINITE);



		// If the above is triggered due to pause or stop mechanism, then GetOverlapped Result will return false.
		// Need to handle this.

		if (dwWaitResult == WAIT_OBJECT_0)
			_Write("\nEvent is successfull.\n");
		else
			_Write("\nEvent was stopped!\n");


		DWORD dwBytesTransferred;

		// Get the result after successfull notification receieved.
		bSuccess = GetOverlappedResult(m_hDirectory, &m_Overlapped, &dwBytesTransferred, FALSE);

		if (!bSuccess)
		{
			// Throw error.
			//break;
		}
		else
		{
			// Retrieve buffer data and store it in following structure.
			PFILE_NOTIFY_INFORMATION pNotify = (PFILE_NOTIFY_INFORMATION)buffer;

			// Multiple changes may be detected for a single file.
			while (pNotify)
			{
				_Write("Event: ", pNotify->Action);
				// The program only cares for new added files.
				if (pNotify->Action == FILE_ACTION_ADDED)
				{
					TCHAR szFile[MAX_PATH + 1];
					memcpy(szFile, pNotify->FileName, min(MAX_PATH, pNotify->FileNameLength));
					szFile[min((pNotify->FileNameLength / sizeof(TCHAR)), MAX_PATH)] = 0;

					// Send the main application message to process the detected file.
					PostMessage(*m_MainHwnd, FILEFOUND, NULL, (LPARAM)szFile);

				}

				if (pNotify->NextEntryOffset == 0) break; // No other changes found.

				// Other changes were also detected. Move to those changes.
				// Find out if this is necessary.
				pNotify = (PFILE_NOTIFY_INFORMATION)((LPBYTE)pNotify + pNotify->NextEntryOffset);
			}
		}

		ResetEvent(m_Overlapped.hEvent); // Reset the event to non-signalled.

		// Pause Mechanism: Pause before reading next change.
		WaitForSingleObject(m_EventPause, INFINITE);


		// Read the next file.
		bSuccess = ReadDirectoryChangesW(
			m_hDirectory,
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
			&m_Overlapped,
			NULL
		);
	}

	return 0;
}

DWORD WINAPI DirectoryWatcher::Monitor(LPVOID param)
{
	if (!MONITORMODE) return 0;
	DirectoryWatcher* This = (DirectoryWatcher*)param;
	return This->Monitor();
}

BOOL DirectoryWatcher::Initiate(HWND* mainHwnd, CONST TCHAR* szWaitingTime)
{
	if (!MONITORMODE) return TRUE;
	m_MainHwnd = mainHwnd;

	SetWaitingTime(szWaitingTime);

	m_hDirectory = CreateFile(
		(LPCWSTR)FileManager::GetInputPath(),
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		NULL
	);

	if (m_hDirectory == INVALID_HANDLE_VALUE)
	{
		ErrorMessage(L"DirectoryWatcher::Initiate(): CreateFile failed!");
		return FALSE; // Program should not proceed.
	}

	m_Overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// Start watching the directory.
	m_isWatching = TRUE;

	return TRUE;
}

BOOL DirectoryWatcher::Pause()
{
	// Thread must stop waiting for new changes. 
	SetEvent(m_Overlapped.hEvent);

	// WaitForSingleObject will start waiting.
	ResetEvent(m_EventPause);

	return TRUE;
}

BOOL DirectoryWatcher::Resume()
{
	// m_Overlapped.hEvent is already reset.
	return SetEvent(m_EventPause);
}

BOOL DirectoryWatcher::Stop()
{
	// Exit while loop in the MonitorDirectory.
	m_isWatching = FALSE;

	// If the monitor is paused, then first trigger the m_EventPause.
	// Else need to trigger m_Overlapped.hEvent first.
	// However, call to trigger any event is okay.

	SetEvent(m_Overlapped.hEvent);
	SetEvent(m_EventPause);

	// Close the file handle.
	if (m_hDirectory != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hDirectory);
		m_hDirectory = INVALID_HANDLE_VALUE;
	}

	return 0;
}

void DirectoryWatcher::SetWaitingTime(CONST TCHAR* szNewWaitingTime)
{
	/*
		=> CONVERT TCHAR TO INTEGER
			TCHAR sznum[] = L"10320";
			auto num = _tstoi(sznum);
	*/
	INT nSzNewWaitingTime = _tstoi(szNewWaitingTime);
	if (nSzNewWaitingTime == 0) return;

	m_WaitingTime = nSzNewWaitingTime;
}


/*
if (pNotify->Action == FILE_ACTION_ADDED)
			{
				// Get the file name.
				TCHAR szFileName[MAX_PATH + 1];

				// Allocate memory buffer to store file name plus 2 for terminating character.
				TCHAR* szFileName2 = new TCHAR[pNotify->FileNameLength + 2];

				// Copy file name from the pNotify structure to the buffer.
				memcpy(szFileName, pNotify->FileName, min(MAX_PATH, pNotify->FileNameLength));
				memcpy(szFileName2, pNotify->FileName, pNotify->FileNameLength);

				// pNotify->FileName is not null-terminated.
				szFileName[min((pNotify->FileNameLength / sizeof(TCHAR)), MAX_PATH)] = 0;

				szFileName2[pNotify->FileNameLength] = L'\0';


				delete[] szFileName2;
				// Make the buffer to hold the ANSI version of szFileName + m_path_to_watch.

				// Send the main application message to process the detected file.
				PostMessage(*m_MainHwnd, FILEFOUND, NULL, (LPARAM)szFileName);
			}
*/