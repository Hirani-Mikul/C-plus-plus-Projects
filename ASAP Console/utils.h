#pragma once

#include <Windows.h>
#include <atlstr.h>
#include <tchar.h>
#include <WinUser.h>
#include <iostream>
#include <unordered_map>
#include <strsafe.h>
#include <sysinfoapi.h>
#include <algorithm>
#include <string>
#include <cstdio>

#include <charconv>

void ErrorMessage(const wchar_t* lpszFunction);

#define MAX_VALUES 10

struct AppSetting
{
	CHAR input_directory[MAX_PATH] = { 0 };
	CHAR output_directory[MAX_PATH] = { 0 };
	CHAR error_directory[MAX_PATH] = { 0 };
	CHAR current_printer[32] = { 0 };
	INT waiting_time = 0;
};

BOOL WriteSettingsToFile(CHAR* buffer, INT nBufLen)
{
	HANDLE hFile = CreateFile(
		L"C:\\Users\\HIRANI\\Desktop\\Windows API\\ASAP Console\\config4.config",
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	DWORD bytesWritten = 0;
	BOOL bSuccess = WriteFile(hFile, buffer, nBufLen, &bytesWritten, NULL);

	if (bSuccess && bytesWritten == nBufLen)
	{
		CloseHandle(hFile);
		return TRUE;
	}
	CloseHandle(hFile);

	return FALSE;
}

// Function to check the length of num. i.e. 1 is 1, 10 is 2, 100 is 3, 1000 is 4.
INT GetNumLength(int num) {	return (num < 10 ? 1 : (num < 100 ? 2 : (num < 1000 ? 3 : (num < 10000 ? 4 : 5)))); }

int charToInt(CONST CHAR* cNum)
{


	if (cNum == NULL) return -1;

	int num = 0;
	int i = 0;

	while (cNum[i] != '\0')
	{
		num = (cNum[i] - '0') + (num * 10);
		i++;
	}

	return num;
}

BOOL intToChar(CHAR* chNum, INT num)
{
	// Any value cannot be greater than 100000.
	if (num < 0 || num >= 100000)
	{
		chNum[0] = '\0';
		return FALSE;
	}

	INT numLength = GetNumLength(num);

	//args: start destination, end destination, source.
	std::to_chars(chNum, chNum + numLength, num);
	chNum[numLength] = '\0';

	return TRUE;
}

// Returns a number that represents starting position of the second line incase of successfull reading.
INT GetFirstLine(CONST CHAR* buffer, INT (&valPositions)[MAX_VALUES])
{
	int index = 0;
	/*=================================== CORRECTION NEEDED =====================================*/
	/* MAX CHARACTER LIMIT SHOULD BE (4 * 5) + 10 */
	
	// The first value in the buffer before comman is the size of the entire first line.
	// Considering all 10 values has max character limit of 4 bytes, then the maximum length of first line is:
	// (4 * 10) + (10 for each comma) => 50.
	// 50 is only 2 bytes, therefore, the first comma should be at position less than 3.
	// Find the first comma to know the size of the first line.
	// Based on the above logic, done some random comparasion to exit out of loop. i < INFINITY could work.
	for (int i = 0; i < 3; i++)
	{
		if (buffer[i] == ',')
		{
			index = i;
			break;
		}
	}
	// In valid file, position of comma cannot be greater than 3.
	if (index == 0) return -1;

	// Size is based on the above logic, plus one for terminating character.
	CHAR chSizeOfFirstLine[2 + 1] = { 0 };
	memcpy(chSizeOfFirstLine, buffer, index);
	chSizeOfFirstLine[index] = '\0';

	INT nSizeOfFirstLine = charToInt(chSizeOfFirstLine);

	// Size is based on the above logic, plus one for terminating character.
	CHAR chFirstLine[50 + 1] = { 0 };
	memcpy(chFirstLine, (buffer + index + 1), nSizeOfFirstLine);
	chFirstLine[nSizeOfFirstLine] = '\0';

	std::cout << "sizeOfFirstLine: " << chSizeOfFirstLine << std::endl;
	std::cout << "FirstLine: " << chFirstLine << std::endl;

	
	int posIndex = 0;
	index = 0;

	for (int i = 0; i < nSizeOfFirstLine; i++)
	{
		if (chFirstLine[i] == ',')
		{
			// Maximum character limit for all values is 4.
			CHAR chNum[4 + 1] = { 0 };
			memcpy(chNum, chFirstLine + index, (i - index));
			chNum[(i - index)] = '\0';
			index = (i + 1);
			valPositions[posIndex] = charToInt(chNum);
			posIndex++;
		}
	}
	// Since index is reset after the size of first line is computed, getting the position of next line is tricky.
	// Position: 
	// Position of last comma.
	// Plus 1 for return carriage(\n).
	// Plus 2 or 3 depending on the character size of first value in the buffer.
	return (index + 1 + (nSizeOfFirstLine < 10 ? 2 : 3));
}

BOOL ParseSetting(CONST CHAR* buffer, AppSetting& settings)
{
	if (buffer == NULL) return FALSE;

	std::cout << "\n\n\n";

	// Store the position of each value. i.e. .\\IN\\

	INT valPositions[MAX_VALUES] = { -1 };
	
	// Stores the current marker position in the buffer.
	// The start of the index is the second line i.e. after first '\n\ character.
	INT index = GetFirstLine(buffer, valPositions);
	
	// Now get the setting values.
	
	// Get input path.
	// Skip 15 + 3 (name + spaces and equal sign)
	index += (valPositions[0] + 3);
	memcpy(settings.input_directory, buffer + index, valPositions[1]);
	settings.input_directory[valPositions[1]] = '\0';

	// Get output path.
	// Skip previous's value character size. 
	// Skip 16 + 3 + 1 (name + spaces and equal sign + '\r\n')
	index += valPositions[1];
	index += (valPositions[2] + 3 + 1);
	memcpy(settings.output_directory, buffer + index, valPositions[3]);
	settings.output_directory[valPositions[3]] = '\0';

	// Get error path.
	// Skip previous's value character size.
	// Skip 15 + 3 + 1 (name + spaces and equal sign + '\r\n')
	index += valPositions[3];
	index += (valPositions[4] + 3 + 1);
	memcpy(settings.error_directory, buffer + index, valPositions[5]);
	settings.error_directory[valPositions[5]] = '\0';

	// Get printer name.
	// Skip previous's value character size.
	// Skip 15 + 3 + 1 (name + spaces and equal sign + '\r\n')
	index += valPositions[5];
	index += (valPositions[6] + 3 + 1);
	memcpy(settings.current_printer, buffer + index, valPositions[7]);
	settings.current_printer[valPositions[7]] = '\0';

	// Get waiting time.
	// Skip previous's value character size.
	// Skip 12 + 3 + 1 (name + spaces and equal sign + '\r\n')
	index += valPositions[7];
	index += (valPositions[8] + 3 + 1);
	CHAR chWaitTime[5];
	memcpy(chWaitTime, buffer + index, valPositions[9]);
	chWaitTime[valPositions[9]] = '\0';
	settings.waiting_time = charToInt(chWaitTime);

	std::cout << "\n\n====================> CURRENT APPLICATION SETTINGS <=====================\n\n";

	std::cout << "Input path: " << settings.input_directory << std::endl;
	std::cout << "Output path: " << settings.output_directory << std::endl;
	std::cout << "Error path: " << settings.error_directory << std::endl;
	std::cout << "Current printer: " << settings.current_printer << std::endl;
	std::cout << "Waiting time: " << settings.waiting_time << std::endl;

	return TRUE;
}

CHAR* ReadAppSettings()
{
	std::wcout << L"Started reading config file.\n";
	HANDLE hFile = INVALID_HANDLE_VALUE; // Handle to file that needs to be read.
	DWORD fileLen = 0; // Size of the file in bytes.
	DWORD dwBytesRead = 0; // Number of bytes read.

	hFile = CreateFile(
		L"C:\\Users\\HIRANI\\Desktop\\Windows API\\ASAP Console\\config.config",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;

	fileLen = GetFileSize(hFile, NULL);

	std::wcout << "File size in bytes: " << fileLen << std::endl;

	//Changed: *Buffer = new CHAR[fileLen + 1];
	CHAR* Buffer = new CHAR[fileLen + 1];

	BOOL bSuccess = ReadFile(hFile, Buffer, fileLen, &dwBytesRead, NULL);

	if (!bSuccess)
	{
		ErrorMessage(L"ReadFile: ");
		CloseHandle(hFile);
		return NULL;
	}

	CloseHandle(hFile);

	if (dwBytesRead > 0 && dwBytesRead <= fileLen)
		(Buffer)[fileLen] = L'\0';

	else return NULL;
	
	std::cout << "\n\n====================> ORIGINAL SETTINGS <=====================\n\n";

	std::cout << Buffer << std::endl;

	std::cout << "Reading completed successfully.\n";

	return Buffer;
}
BOOL WriteAppSettings(CONST AppSetting& settings)
{
	// Write the first line.
	// Length of each values in integer.
	size_t nInputPathSize = strlen(settings.input_directory);
	size_t nOutputPathSize = strlen(settings.output_directory);
	size_t nErrorPathSize = strlen(settings.error_directory);
	size_t nCurrentPrinterSize = strlen(settings.current_printer);
	INT    nWaitingTimeSize = GetNumLength(settings.waiting_time);
	
	// Length of size of each values.
	INT nChInputPathLen = GetNumLength(nInputPathSize);
	INT nChOutputPathLen = GetNumLength(nOutputPathSize);
	INT nChErrorPathLen = GetNumLength(nErrorPathSize);
	INT nChCurrentPrinterLen = GetNumLength(nCurrentPrinterSize);
	INT nChWaitingTimeLen = GetNumLength(nWaitingTimeSize);

	INT nSizeOfHeader = 0;
	nSizeOfHeader += nChInputPathLen;
	nSizeOfHeader += nChOutputPathLen;
	nSizeOfHeader += nChErrorPathLen;
	nSizeOfHeader += nChCurrentPrinterLen;
	nSizeOfHeader += nChWaitingTimeLen;

	// Add 5 for each comma after every character length of values.
	nSizeOfHeader += 5;
	
	//Changed: nSizeOfHeader += 2; // 2 for \n\0
	nSizeOfHeader += 1; // 1 for \n
	
	nSizeOfHeader += 10; // 10 for constant bytes for names
	nSizeOfHeader += 5; // 5 for another commas.

	INT nChSizeOfFirstLine = GetNumLength(nSizeOfHeader);
	nSizeOfHeader += nChSizeOfFirstLine + 1; // 1 for comma

	// Calculate the size in bytes of body.
	// Length of all values + name + 2 spaces + equal character + \n
	INT nSizeOfBody = 0;
	// First add lengths of all names i.e. length of input_directory plus length of output_directory and so on.
	nSizeOfBody += 15 + 16 + 15 + 15 + 12;
	// Now add all commas, spaces, equal, and \n. (Minus 1, since the last line does not need new line character.)
	nSizeOfBody += (4 * 5) - 1;
	// Now add lengths of all values i.e. length of value of input_directory and so on.
	nSizeOfBody +=
		nInputPathSize +
		nOutputPathSize +
		nErrorPathSize +
		nCurrentPrinterSize +
		nWaitingTimeSize;

	INT nFileSize = nSizeOfBody + nSizeOfHeader;
	// Header + Body + Null terminating char
	CHAR* chContentBuffer = new CHAR[nSizeOfHeader + nSizeOfBody + 1];

	INT nBufferIndex = 0;

	// Get the interger converted to char.
	
	// Buffer to store the length in character instead of int. Plus one for terminating character. (4 + 1)
	CHAR
		chSizeOfFirstLineLen[5],
		chInputPathLen[5],
		chOutputPathLen[5],
		chErrorPathLen[5],
		chCurrentPrinterLen[5],
		chWaitingTimeLen[5];

	// chSizeOfFirstLineLen does not include: size of itself plus it's comma plus 1 for and carriage return.
	intToChar(chSizeOfFirstLineLen, (nSizeOfHeader - nChSizeOfFirstLine - 1 - 1));

	intToChar(chInputPathLen, nInputPathSize);
	intToChar(chOutputPathLen, nOutputPathSize);
	intToChar(chErrorPathLen, nErrorPathSize);
	intToChar(chCurrentPrinterLen, nCurrentPrinterSize);
	intToChar(chWaitingTimeLen, nWaitingTimeSize);

	CONST CHAR Comma = ',';

	auto WriteToBuffer = [&](CONST CHAR* chText, INT nTextLen)
	{
		memcpy(chContentBuffer + nBufferIndex, chText, nTextLen);
		nBufferIndex += nTextLen;
		memcpy(chContentBuffer + nBufferIndex, &Comma, 1);
		nBufferIndex += 1;
	};

	// Write total length of first line + comma.
	WriteToBuffer(chSizeOfFirstLineLen, nChSizeOfFirstLine);

	// Write total length of name + comma + value + comma.
	// Input path.
	WriteToBuffer("15", 2);
	WriteToBuffer(chInputPathLen, nChInputPathLen);

	// Output path.
	WriteToBuffer("16", 2);
	WriteToBuffer(chOutputPathLen, nChOutputPathLen);

	// Error path.
	WriteToBuffer("15", 2);
	WriteToBuffer(chErrorPathLen, nChErrorPathLen);

	// Current Printer.
	WriteToBuffer("15", 2);
	WriteToBuffer(chCurrentPrinterLen, nChCurrentPrinterLen);

	// Waiting time.
	WriteToBuffer("12", 2);
	WriteToBuffer(chWaitingTimeLen, nChWaitingTimeLen);

	chContentBuffer[nBufferIndex] = '\n';
	nBufferIndex++;

	CONST CHAR CarriageReturn = '\n';

	auto WriteToBodyBuffer = [&](CONST CHAR* chName, CONST CHAR* chValue, INT nNameLen, INT nValueLen, BOOL isNextNewLine = TRUE)
	{
		memcpy(chContentBuffer + nBufferIndex, chName, nNameLen);
		nBufferIndex += nNameLen;
		memcpy(chContentBuffer + nBufferIndex, chValue, nValueLen);
		nBufferIndex += nValueLen;
		if (isNextNewLine)
		{
			memcpy(chContentBuffer + nBufferIndex, &CarriageReturn, 1);
			nBufferIndex += 1;
		}
	};

	CHAR chWaitingTime[6];
	intToChar(chWaitingTime, settings.waiting_time);

	WriteToBodyBuffer("input_directory = ", settings.input_directory, 15 + 3, nInputPathSize);
	WriteToBodyBuffer("output_directory = ", settings.output_directory, 16 + 3, nOutputPathSize);
	WriteToBodyBuffer("error_directory = ", settings.error_directory, 15 + 3, nErrorPathSize);
	WriteToBodyBuffer("current_printer = ", settings.current_printer, 15 + 3, nCurrentPrinterSize);
	WriteToBodyBuffer("waiting_time = ", chWaitingTime, 12 + 3, nWaitingTimeSize, FALSE);

	chContentBuffer[nBufferIndex] = '\0';

	std::cout << "\n\n====================> BUFFER SETTINGS <=====================\n\n";
	std::cout << chContentBuffer << std::endl;


	WriteSettingsToFile(chContentBuffer, nBufferIndex);

	delete[] chContentBuffer;

	std::cout << "Finished reading.\n";

	return TRUE;
}

void ErrorMessage(const wchar_t* lpszFunction)
{
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;

	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);

	lpDisplayBuf = (LPVOID)LocalAlloc(
		LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)
	);

	StringCchPrintf(
		(LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction,
		dw,
		lpMsgBuf
	);

	MessageBox(
		NULL,
		(LPCTSTR)lpDisplayBuf,
		TEXT("Error"),
		MB_OK
	);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}