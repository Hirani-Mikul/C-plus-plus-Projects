#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

void RefreshDirectory(LPTSTR);
void RefreshTree(LPTSTR);
void WatchDirectory(LPTSTR);

int main()
{
	std::string str_path = "C:\\Users\\HIRANI\\Desktop\\C++\\MultipleConsole\\IN";

	TCHAR* path = new TCHAR[str_path.size() + 1];

	path[str_path.size()] = 0;

	std::copy(str_path.begin(), str_path.end(), path);



	WatchDirectory(path);
	//WatchDirectory((LPTSTR)str_path.c_str());
	
	delete[] path;
	
	return 0;
}



void WatchDirectory(LPTSTR lpDir)
{
	std::wstring wstr(lpDir);

	std::cout << "Directory path: " << std::string(wstr.begin(), wstr.end()) << "\n";

	DWORD dwWaitStatus;

	/*
		Two separate handles
		1. One for directory
		2. Another for subtree
	*/
	HANDLE dwChangeHandles[2];

	/*
		lpDrive[0] = Drive letter e.g 'C'
		lpDrive[1] = :
		lpDrive[2] = \
		lpDrive[3] = \0 - End line character

		lpDrive = "C:\"
	*/
	TCHAR lpDrive[4];
	TCHAR lpFile[_MAX_FNAME];
	TCHAR lpExt[_MAX_EXT];

	_tsplitpath_s(
		lpDir,        // Full path
		lpDrive,      // Drive letter e.g 'C:\'
		4,            // driveNumberOfElements - the size of the drive buffer
		NULL,         // Direcory path
		0,			  // dirNumberOfElements - the size of the dir buffer
		lpFile,       // Base filename (without extension)
		_MAX_FNAME,   // nameNumberOfElements - the size of the fname buffer
		lpExt,        // Filename extension
		_MAX_EXT      // extNumberOfElements - the size of ext buffer
	);

	lpDrive[2] = (TCHAR)'\\';
	lpDrive[3] = (TCHAR)'\0';

	// Watch the directory for file creation and deletion

	//dwChangeHandles[0] = FindFirstChangeNotification(
	//	lpDir,                          // Directory to watch
	//	FALSE,							// Do not watch subtree
	//	FILE_NOTIFY_CHANGE_FILE_NAME    // Watch file name change
	//);

	dwChangeHandles[0] = FindFirstChangeNotification(
		lpDir,                          // Directory to watch
		FALSE,							// Do not watch subtree
		FILE_NOTIFY_CHANGE_LAST_WRITE    // Watch file name change
	);


	if (dwChangeHandles[0] == INVALID_HANDLE_VALUE)
	{
		std::cout << "\n ERROR 1: FindFirstChangeNotification function failed.\n";
		ExitProcess(GetLastError());
	}

	// Watch the subtree for directory creation and deletion

	dwChangeHandles[1] = FindFirstChangeNotification(
		lpDir,                          // Directory to watch
		TRUE,							// watch the subtree
		FILE_NOTIFY_CHANGE_DIR_NAME    // Watch dir name change
	);


	if (dwChangeHandles[1] == INVALID_HANDLE_VALUE)
	{
		std::cout << "\n ERROR 2: FindFirstChangeNotification function failed.\n";
		ExitProcess(GetLastError());
	}

	// Make a final validation check on our handles

	if (dwChangeHandles[0] == NULL || dwChangeHandles[1] == NULL)
	{
		std::cout << "\n ERROR 3: Unexpected NULL from FindFirstChangeNotification.\n";
		ExitProcess(GetLastError());
	}

	// Change notification is set. Now wait on both notification
	// handles and refresh accordingly.

	while (TRUE)
	{
		// Wait for notification
		std::cout << "\nWaiting for notification...\n";

		dwWaitStatus = WaitForMultipleObjects(2, dwChangeHandles, FALSE, INFINITE);

		switch (dwWaitStatus)
		{
		case WAIT_OBJECT_0:

			// A file was created, renamed, or deleted in the directory.
			// Refresh this directory and restart the notification.


			RefreshDirectory(lpDir);

			if (FindNextChangeNotification(dwChangeHandles[0]) == FALSE)
			{
				std::cout << "\n ERROR 4: FindNextChangeNotification function failed.\n";
				ExitProcess(GetLastError());
			}

			break;

		case WAIT_OBJECT_0 + 1:

			// A directory was created, renamed, or deleted.
			// Refresh the tree and restart the notification

			RefreshTree(lpDrive);

			if (FindNextChangeNotification(dwChangeHandles[1]) == FALSE)
			{
				std::cout << "\n ERROR 5: FindNextChangeNotification function failed.\n";
				ExitProcess(GetLastError());
			}
			break;

		case WAIT_TIMEOUT:

			// A timeout occured, this would happen if some value other
			// than INFINITE is used in the Wait call and no changes occur.
			// In a single-threaded environment you might not want an
			// INFINITE wait.

			std::cout << "\nNO changes in the timeout period.\n";
			break;
		default:
			std::cout << "\n ERROR 6: Unhandled dwWaitStatus.\n";
			ExitProcess(GetLastError());
			break;
		}
	}

}

void RefreshDirectory(LPTSTR lpDir) {
	// This is where you might place code to refresh your
	// directory listing, but not the subtree because it
	// would not be necessary.

	std::wstring wstr(lpDir);

	std::cout << "Directory " << std::string(wstr.begin(), wstr.end()) << " changed.\n";
}

void RefreshTree(LPTSTR lpDrive) {

	// This is where you might place code to refresh your
	// directory listing, including the subtree.

	std::wstring wstr(lpDrive);
	std::cout << "Directory tree " << std::string(wstr.begin(), wstr.end()) << " changed.\n";
}

/*
#include <iostream>
#include "ConsoleLogger.h"

int main()
{
	std::cout << "This is the main console." << std::endl;

	CConsoleLogger output_console;

	output_console.Create("ASAP Messages");
	output_console.printf("The file moved to out folder");

	std::cout << "Exiting the main console." << std::endl;

}
*/