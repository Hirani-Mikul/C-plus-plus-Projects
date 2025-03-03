#pragma once
#include <Windows.h>
#include <tchar.h>
#include <Shlwapi.h>



#include "List.h"
#include "MyQueue.h"
#include "utils.h"

// SINGLETON
// MANAGE FILE SYSTEM


extern TextBox Logger;

class FileManager
{
public:
	FileManager(const FileManager&) = delete;

	static FileManager& Get()
	{
		static FileManager Instance;

		return Instance;
	}

public:
	static void Initiate(CONST TCHAR* input_path, CONST TCHAR* output_path, CONST TCHAR* error_path) 
	{ Get()._Initiate(input_path, output_path, error_path); }

	static void InsertFile(CONST TCHAR* szFile) { Get()._InsertFile(szFile); }
	static CONST TCHAR* GetFirstFile() { return Get()._GetFirstFile(); }
	//static TCHAR* GetFullPath(CONST TCHAR* szFile, BOOL isInputPath = TRUE) { return Get()._GetFullPath(szFile, isInputPath); }
	static TCHAR* GetInputPath(CONST TCHAR* szFile) { return Get()._GetInputPath(szFile); }
	static TCHAR* GetOutputPath(CONST TCHAR* szFile) { return Get()._GetOutputPath(szFile); }
	
	static BOOL MoveTheFile(CONST TCHAR* szFile, BOOL bStatus) { return Get()._MoveTheFile(szFile, bStatus); }

	static CONST TCHAR* GetInputPath() { return Get().szInputDirectory; }

	static void ClearAllFiles() { Get()._ClearAllFiles(); }



private:
	void _Initiate(CONST TCHAR* input_path, CONST TCHAR* output_path, CONST TCHAR* error_path)
	{
		szInputDirectory = input_path;
		szOutputDirectory = output_path;
		szErrorDirectory = error_path;
	}

	// Returns a full path to the first file inserted into the list.
	TCHAR* _GetFileFullPath(CONST TCHAR* szFile, short path_to_get = 0)
	{
		CONST TCHAR* path = NULL;


		if (path_to_get == 0) path = szInputDirectory;
		else if (path_to_get == 1) path = szOutputDirectory;
		else path = szErrorDirectory;

		// Get the length of the string of both path and file.
		size_t dir_str_len = _tcslen(path);
		size_t file_str_len = _tcslen(szFile);

		// Allocate buffer to store the fullpath. Plus 2 for '\' and terminating character.
		TCHAR* szFullPath = new TCHAR[dir_str_len + file_str_len + 2];

		// First copy the path.
		// _tcscpy_s automatically null terminates the string.
		_tcscpy_s(szFullPath, dir_str_len + 1, path);

		// Insert '\' character.
		szFullPath[dir_str_len] = L'\\';

		// Copy the file name.
		_tcscpy_s(szFullPath + dir_str_len + 1, file_str_len + 1, szFile);

		// Release the memory after printing.
		return szFullPath;
	}

	// Returns a pointer to full path, needs to be released once the required operation is complete.
	TCHAR* _GetInputPath(CONST TCHAR* szFile) { return _GetFileFullPath(szFile, 0); }
	TCHAR* _GetOutputPath(CONST TCHAR* szFile) { return _GetFileFullPath(szFile, 1); }
	TCHAR* _GetErrorPath(CONST TCHAR* szFile) { return _GetFileFullPath(szFile, 2); }


	CONST TCHAR* _GetFirstFile() {
		// Get the first file inserted in the list.
		return m_Files.front();

	}


	void _RemoveFirstFile() {
		// Removes the first file inserted in the list.
		m_Files.pop_front();
	}

	void _InsertFile(LPCWSTR szFile)
	{

		size_t len = _tcslen(szFile);

		TCHAR* szFileName = new TCHAR[ len + 1 ];

		//std::copy() : alternative
		// Copy file name from the szFile to the buffer.
		_tcsncpy_s(szFileName, len + 1, szFile, len);
		
		m_Files.push_back(szFileName);
	}


	BOOL _MoveSuccessFile(CONST TCHAR* szFile)
	{
		// Get the full output path.
		CONST TCHAR* szOriginalPath = _GetInputPath(szFile);
		CONST TCHAR* szNewPath = _GetOutputPath(szFile);
		
		BOOL bSuccess = MoveFile(szOriginalPath, szNewPath);

		delete[] szOriginalPath;
		delete[] szNewPath;

		Logger.Write("Successfully moved the passed file");

		_RemoveFirstFile();

		return bSuccess;
	}
	BOOL _MoveFailedFile(CONST TCHAR* szFile)
	{
		// Get the full output path.
		CONST TCHAR* szOriginalPath = _GetInputPath(szFile);
		CONST TCHAR* szNewPath = _GetErrorPath(szFile);
		
		BOOL bSuccess = MoveFile(szOriginalPath, szNewPath);

		delete[] szOriginalPath;
		delete[] szNewPath;

		Logger.Write("Successfully moved the failed file");

		_RemoveFirstFile();

		return bSuccess;
	}

	BOOL _MoveTheFile(CONST TCHAR* szFile, BOOL bStatus)
	{
		// If the file was successfully printed, then move the file to the output folder, else error folder.

		if (bStatus) return _MoveSuccessFile(szFile);
		else return _MoveFailedFile(szFile);
	}

	void _ClearAllFiles()
	{
		m_Files.clear();
	}

	// Write application setting on hard disk in a config file inform of text.
	BOOL _WriteApplicationSetting() 
	{
		HANDLE hFile = CreateFile(
			L".\\config.txt",     // Config file location.
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			Logger.Write("Error: Unable to open file.\n");
			return FALSE;
		}

		/*
			Need to parse the settings in the correct format.
		*/
		return TRUE; 
	}

	// Read application setting from hard disk from config file inform of text.
	BOOL _ReadApplicationSetting() { return TRUE; }

private:
	FileManager() : szInputDirectory{ NULL }, szOutputDirectory{ NULL }, szErrorDirectory{ NULL } {}

	// Pointers to the memory location allocated by main application.
	CONST TCHAR* szInputDirectory;
	CONST TCHAR* szOutputDirectory;
	CONST TCHAR* szErrorDirectory;

	// List to store the files.

	MyQueue m_Files;
};