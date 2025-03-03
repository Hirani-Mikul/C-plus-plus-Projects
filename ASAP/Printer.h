#pragma once
#include <Windows.h>
#include <winspool.h>
#include <tchar.h>
#include <Shlwapi.h>

#include <iostream>
#include <functional>

#include "utils.h"
#include "FileManager.h"

// SINGLETON
// MANAGES PRINTING FILES.

/*
	User can request to fetch mounted printers.
	User can change the default printer.


	System must choose the default printer if it is unset.
	System must display the fetched printer to the user.
	System must print a file given.

*/

class Printer
{
public:
	Printer(const Printer&) = delete;

	static Printer& Get()
	{
		static Printer Instance;

		return Instance;
	}
	
	// Static methods to allow other parts of application to use the member function.
	static void Initiate(CONST TCHAR* szCurrentPrinter) { Get().szAppCurrentPrinter = szCurrentPrinter; }
	static BOOL PrintFile(CONST TCHAR* szFile) { return Get()._PrintFile(szFile); }
	static BOOL GetMountedPrinters(MountedPrinters& printers) { return Get()._GetMountedPrinters(printers); }
	static BOOL VerifyPrinter(CONST TCHAR* szPrinter) { return Get()._VerifyPrinter(szPrinter); }
	static BOOL GetSystemDefaultPrinter(TCHAR* szPrinter) { return Get()._GetSystemDefaultPrinter(szPrinter); }

private:
	BOOL _GetMountedPrinters(MountedPrinters& printers)
	{
		// Memory required to store information about printers.
		DWORD sizeBuffer = 0;
		PRINTER_INFO_5* printerInfo = NULL;

		// Get Buffer size required to store printers.
		EnumPrinters(
			PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS,
			NULL,
			5,
			NULL,
			NULL,
			&sizeBuffer,
			&printers.m_Entries
		);

		// Allocate memory to store the printers.
		printerInfo = (PRINTER_INFO_5*)malloc(sizeBuffer);

		// This time, fetch the printer's info and store it.
		EnumPrinters(
			PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS,
			NULL,
			5,
			(LPBYTE)printerInfo,
			sizeBuffer,
			&sizeBuffer,
			&printers.m_Entries

		);

		// Check whether printers are available in the system.
		if (!printers.m_Entries)
		{
			// User must be informed of absense of the printers on the system.
			free(printerInfo);
			return FALSE;
		}

		// printers.m_PrinterList: Allocate memory to hold all printer's name. MEMORY WILL BE RELEASED LATER.
		printers.m_PrinterList = new TCHAR * [printers.m_Entries];

		// Fill the memory with the names one by one.
		for (int i = 0; i < printers.m_Entries; i++)
		{
			// Calcuate the length of the name string and allocate memory accordingly.
			LPWSTR printerName = printerInfo[i].pPrinterName;
			size_t printerNameLen = _tcslen(printerName);
			printers.m_PrinterList[i] = new TCHAR[printerNameLen + 1];

			// Copy the name to the printers.
			_tcscpy_s(printers.m_PrinterList[i], printerNameLen + 1, printerName);
		}

		// Make sure to free the memory.
		free(printerInfo);
		return TRUE;
	}

	BOOL _GetSystemDefaultPrinter(TCHAR* szPrinter) {

		// Size required to store printer name in wide characters.
		DWORD dwSize = 0;

		// Get the size required to store the name.
		GetDefaultPrinter(NULL, &dwSize);

		// If there if default printer, then get the name.
		if (dwSize)
		{
			
			GetDefaultPrinter(szPrinter, &dwSize);
			
			return TRUE;
		}
		szPrinter[0] = L'\0';

		return FALSE;
	}

	BOOL _VerifyPrinter(CONST TCHAR* printer)
	{
		// Open the printer to verify if it's valid printer.
		// If valid, then close the printer and return true which is the state of the bStatus.
		// OpenPrinter returns non-zero value if it succeeds. Incase of failure, the return value is 0.
		HANDLE hWndPrinter = INVALID_HANDLE_VALUE;
		BOOL bStatus = FALSE;
		bStatus = OpenPrinter((LPTSTR)printer, &hWndPrinter, NULL);
		if (bStatus) ClosePrinter(hWndPrinter);

		return bStatus;
	}
	
	std::pair<CHAR*, DWORD> _ReadFile(TCHAR* szFile)
	{
		Logger.Write("Reading file.\n");
		BOOL bSuccess = FALSE;
		HANDLE hReadFile = INVALID_HANDLE_VALUE;

		hReadFile = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hReadFile == INVALID_HANDLE_VALUE)
		{
			Logger.Write("ReadFile: Failed to CreateFile.\n");
			ErrorMessage(TEXT("ReadFile(): "));
			return { NULL, 0 };
		}

		// The size of the content in the file in bytes.
		DWORD dwFileSize = 0;
		// Number of bytes already read.
		DWORD dwBytesRead = 0;

		// Get the size in advance to allocate enough memory before reading.
		dwFileSize = GetFileSize(hReadFile, NULL) + 1;

		// This memory will be released outside the scope of this function.
		CHAR* chBufferData = new CHAR[dwFileSize];

		bSuccess = ReadFile(
			hReadFile,
			chBufferData,
			dwFileSize,
			&dwBytesRead,
			NULL
		);

		if (!bSuccess)
		{
			// Inform the user.
			CloseHandle(hReadFile);
			Logger.Write("Failed to read the file.\n");
			return { NULL, 0 };
		}

		if (dwBytesRead > 0 && dwBytesRead <= dwFileSize)
		{
			// Set the null terminator.
			chBufferData[dwBytesRead] = '\0';
			CloseHandle(hReadFile);
			Logger.Write("Succesfully read the file.\n");
			return { chBufferData, dwFileSize };
		}
		else
		{
			// Check if the use of delete here causes any problem.
			delete[] chBufferData;
			CloseHandle(hReadFile);
			Logger.Write("Failed to read file completely.\n");
			return { NULL, 0 };
		}
	}

	BOOL _PrintFile(CONST TCHAR* szFileName)
	{
		_Write("Printing file.\n");
		Logger.Write(TEXT("Printing file!"));

		BOOL bStatus = FALSE;
		HANDLE hPrinter = INVALID_HANDLE_VALUE;
		DWORD bytes_written = 0;
		DOC_INFO_1 docInfo = { 0 };
		DWORD dwJob = 0L;

		// Try to open the printer and get the handle.
		bStatus = OpenPrinterW((LPWSTR)szAppCurrentPrinter, &hPrinter, NULL);

		if (bStatus)
		{
			TCHAR* szFilePath = FileManager::GetInputPath(szFileName);
			TCHAR* szOutPath = FileManager::GetOutputPath(szFileName);

			Logger.Write("Successfully opened the printer!");

			_Write("Successfully opened the printer!\n");
			
			docInfo.pDocName = szFilePath;
			docInfo.pOutputFile = szOutPath;

			dwJob = StartDocPrinter(hPrinter, 1, (LPBYTE)&docInfo);

			if (dwJob > 0)
			{
				Logger.Write(TEXT("Started writing!"));
				_Write("Started writing.\n");
				bStatus = StartPagePrinter(hPrinter);
				if (bStatus)
				{
					// First is the content of the file and Second is the size of the content.
					std::pair<CHAR*, DWORD> Data = _ReadFile(szFilePath);

					// If NULL, then no need to write data.
					if (!Data.first)
					{
						EndPagePrinter(hPrinter);
						EndDocPrinter(hPrinter);
						ClosePrinter(hPrinter);
						delete[] szFilePath;
						delete[] szOutPath;
						return FALSE;
					}

					bStatus = WritePrinter(hPrinter, (LPVOID)Data.first, Data.second, &bytes_written);

					EndPagePrinter(hPrinter);

					// Free the memory.
					delete[] Data.first;
				}
				EndDocPrinter(hPrinter);
			}
			ClosePrinter(hPrinter);
			delete[] szFilePath;
			delete[] szOutPath;
		}
		else
		{
			Logger.Write(TEXT("Failed to open the printer!"));
			_Write("Failed to open the printer!\n");
		}
		Logger.Write(TEXT("File printed successfully!"));
		_Write("File printed successfully.\n");

		return bStatus;
	}

private:
	Printer() : szAppCurrentPrinter { NULL } {}

	// Pointer to the memory initialized by the main application class.
	CONST TCHAR* szAppCurrentPrinter;
};