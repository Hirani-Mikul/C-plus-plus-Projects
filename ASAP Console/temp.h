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

struct Temp
{
	CHAR fname[MAX_PATH] = { 0 };
	CHAR mname[MAX_PATH] = { 0 };
	CHAR lname[MAX_PATH] = { 0 };
};

INT GetLength(int num) { return (num < 10 ? 1 : (num < 100 ? 2 : (num < 1000 ? 3 : (num < 10000 ? 4 : 5)))); }

int chToInt(CONST CHAR* cNum)
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

BOOL intToCh(CHAR* chNum, INT num)
{
	// Any value cannot be greater than 100000.
	if (num < 0 || num >= 100000)
	{
		chNum[0] = '\0';
		return FALSE;
	}

	INT numLength = GetLength(num);

	//args: start destination, end destination, source.
	std::to_chars(chNum, chNum + numLength, num);
	chNum[numLength] = '\0';

	return TRUE;
}

INT GetPositions(CONST CHAR* buffer, INT(&valPositions)[6])
{
	int index = 0;

	for (int i = 0; i < 3; i++)
	{
		if (buffer[i] == ',')
		{
			index = i;
			break;
		}
	}
	if (index == 0) return -1;

	// Size is based on the above logic, plus one for terminating character.
	CHAR chSizeOfFirstLine[2 + 1] = { 0 };
	memcpy(chSizeOfFirstLine, buffer, index);
	chSizeOfFirstLine[index] = '\0';

	INT nSizeOfFirstLine = chToInt(chSizeOfFirstLine);

	// Size is based on the above logic, plus one for terminating character.
	CHAR chFirstLine[25 + 1] = { 0 };
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
			valPositions[posIndex] = chToInt(chNum);
			posIndex++;
		}
	}
	// Since index is reset after the size of first line is computed, getting the position of next line is tricky.
	// Position: 
	// Position of last comma.
	// Plus 2 for return carriage(\r\n).
	// Plus 2 or 3 depending on the character size of first value in the buffer.
	return (index + 2 + (nSizeOfFirstLine < 10 ? 2 : 3));
}

BOOL Parse(CONST CHAR* buffer, Temp& temp) {
	if (buffer == NULL) return FALSE;

	std::cout << "\n\n\n";


	INT valPositions[6] = { -1 };

	// Stores the current marker position in the buffer.
	// The start of the index is the second line i.e. after first '\n\ character.
	INT index = GetPositions(buffer, valPositions);

	// Get input path.
	// Skip 15 + 3 (name + spaces and equal sign)
	index += (valPositions[0] + 3);
	memcpy(temp.fname, buffer + index, valPositions[1]);
	temp.fname[valPositions[1]] = '\0';

	// Get output path.
	// Skip previous's value character size. 
	// Skip 16 + 3 + 2 (name + spaces and equal sign + '\r\n')
	index += valPositions[1];
	index += (valPositions[2] + 3 + 2);
	memcpy(temp.mname, buffer + index, valPositions[3]);
	temp.mname[valPositions[3]] = '\0';

	// Get error path.
	// Skip previous's value character size.
	// Skip 15 + 3 + 2 (name + spaces and equal sign + '\r\n')
	index += valPositions[3];
	index += (valPositions[4] + 3 + 2);
	memcpy(temp.lname, buffer + index, valPositions[5]);
	temp.lname[valPositions[5]] = '\0';

	std::cout << "\n\n====================> CURRENT APPLICATION SETTINGS <=====================\n\n";

	std::cout << "First name: " << temp.fname << std::endl;
	std::cout << "Middle name: " << temp.mname << std::endl;
	std::cout << "Last name: " << temp.lname << std::endl;

	return TRUE;
}

CHAR* Read() {

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
	return NULL;
}

BOOL Write(CONST Temp& temp) {
	// Write the first line.
	// Length of each values in integer.
	size_t nInputPathSize = strlen(temp.fname);
	size_t nOutputPathSize = strlen(temp.mname);
	size_t nErrorPathSize = strlen(temp.lname);

	// Length of size of each values.
	INT nChInputPathLen = GetNumLength(nInputPathSize);
	INT nChOutputPathLen = GetNumLength(nOutputPathSize);
	INT nChErrorPathLen = GetNumLength(nErrorPathSize);

	INT nSizeOfHeader = 0;
	nSizeOfHeader += nChInputPathLen;
	nSizeOfHeader += nChOutputPathLen;
	nSizeOfHeader += nChErrorPathLen;

	// Add 5 for each comma after every character length of values.
	nSizeOfHeader += 3;

	//Changed: nSizeOfHeader += 2; // 2 for \n\0
	nSizeOfHeader += 2; // 2 for \r\n

	nSizeOfHeader += 3; // 10 for constant bytes for names
	nSizeOfHeader += 3; // 5 for another commas.

	INT nChSizeOfFirstLine = GetNumLength(nSizeOfHeader);
	nSizeOfHeader += nChSizeOfFirstLine + 1; // 1 for comma

	// Calculate the size in bytes of body.
	// Length of all values + name + 2 spaces + equal character + \n
	INT nSizeOfBody = 0;
	// First add lengths of all names i.e. length of input_directory plus length of output_directory and so on.
	nSizeOfBody += 4 + 4 + 4;
	// Now add all commas, spaces, equal, and \n. (Minus 2, since the last line does not need new line characters.)
	nSizeOfBody += (5 * 3) - 2;
	// Now add lengths of all values i.e. length of value of input_directory and so on.
	nSizeOfBody +=
		nInputPathSize +
		nOutputPathSize +
		nErrorPathSize;

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
		chErrorPathLen[5];

	// chSizeOfFirstLineLen does not include: size of itself plus it's comma plus 2 for and carriage return.
	intToChar(chSizeOfFirstLineLen, (nSizeOfHeader - nChSizeOfFirstLine - 1 - 2));

	intToChar(chInputPathLen, nInputPathSize);
	intToChar(chOutputPathLen, nOutputPathSize);
	intToChar(chErrorPathLen, nErrorPathSize);

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
	WriteToBuffer("4", 1);
	WriteToBuffer(chInputPathLen, nChInputPathLen);

	// Output path.
	WriteToBuffer("4", 1);
	WriteToBuffer(chOutputPathLen, nChOutputPathLen);

	// Error path.
	WriteToBuffer("4", 1);
	WriteToBuffer(chErrorPathLen, nChErrorPathLen);

	CONST CHAR CarriageReturn[] = "\r\n";
	memcpy(chContentBuffer, CarriageReturn, 2);
	nBufferIndex += 2;


	auto WriteToBodyBuffer = [&](CONST CHAR* chName, CONST CHAR* chValue, INT nNameLen, INT nValueLen, BOOL isNextNewLine = TRUE)
	{
		memcpy(chContentBuffer + nBufferIndex, chName, nNameLen);
		nBufferIndex += nNameLen;
		memcpy(chContentBuffer + nBufferIndex, chValue, nValueLen);
		nBufferIndex += nValueLen;
		if (isNextNewLine)
		{
			memcpy(chContentBuffer + nBufferIndex, &CarriageReturn, 2);
			nBufferIndex += 2;
		}
	};


	WriteToBodyBuffer("fname = ", temp.fname, 4 + 3, nInputPathSize);
	WriteToBodyBuffer("mname = ", temp.mname, 4 + 3, nOutputPathSize);
	WriteToBodyBuffer("lname = ", temp.lname, 4 + 3, nErrorPathSize);

	chContentBuffer[nBufferIndex] = '\0';

	std::cout << "\n\n====================> BUFFER SETTINGS <=====================\n\n";
	std::cout << chContentBuffer << std::endl;


	//WriteSettingsToFile(chContentBuffer, nBufferIndex);

	delete[] chContentBuffer;

	std::cout << "Finished reading.\n";

	return TRUE;
}