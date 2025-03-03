#include "Application.h"

/*
	-------------------- Read notes (Note 4) for Setting Configuration -------------------------
*/

// Global declaration of utility functions required to fulfill tasks.
// Function to get the length of num. i.e. 1 is 1, 10 is 2, 100 is 3, 1000 is 4.
INT GetNumLength(INT nNum);
// Function to convert integer to string integer i.e. 200 to "200".
BOOL intToTchar(TCHAR* szNum, INT num);

BOOL Application::LoadApplicationSettings()
{
	Logger.Write(L"Loading application settings!");
	// Read the config file.

	//===============================> READ SETTINGS FROM CONFIG FILE.
	CONST TCHAR* SettingBuffer = _ReadSettingsFromFile();

	if (SettingBuffer == NULL) return FALSE;

	// Store the position of each value.
	INT ValueLenPositions[MAXHEADERVALUES];

	//============================================> PARSE HEADER.
	 
	// Get the name's and value's position from the setting buffer's header line.
	// Index is the end position of the first line i.e. at '\n' of header line.
	INT index = _GetHeaderLine(SettingBuffer, ValueLenPositions);
	INT positionIndex = 0; // Current position in ValueLenPositions.

	//==============================================> PARSE BODY.

	// Get the setting values.
	// Lambda function to perform repetative task of parsing each name and value from setting buffer.
	
	auto ParseValuesFromBuffer = [&](TCHAR* szName, INT nMaxNameLen)
	{
		// Skip name's length plus 4 (name's len + spaces, equal, and '\n').
		index += (ValueLenPositions[positionIndex] + 3 + 1);
		positionIndex++;
		// _tcsncpy_s allows the source buffer to advance to specific pointer location by adding the offset.
		_tcsncpy_s(szName, nMaxNameLen, (SettingBuffer + index), ValueLenPositions[positionIndex]);
		positionIndex++;
		index += ValueLenPositions[positionIndex - 1];
	};

	ParseValuesFromBuffer(m_Settings.input_directory, _MAX_PATH);
	ParseValuesFromBuffer(m_Settings.output_directory, _MAX_PATH);
	ParseValuesFromBuffer(m_Settings.error_directory, _MAX_PATH);
	ParseValuesFromBuffer(m_Settings.current_printer, _MAX_PATH);
	ParseValuesFromBuffer(m_Settings.waiting_time, 7);

	if (SettingBuffer != NULL)
	{
		delete[] SettingBuffer;
	}

	BOOL bIsValid = VerifyApplicationSettings();
	// If either of setting value is invalid, then write the setting file again.
	if (!bIsValid)
	{
		WriteApplicationSettings();
	}
	
	return TRUE;
}

BOOL Application::VerifyApplicationSettings()
{
	Logger.Write(L"Verifying application settings!");

	BOOL bStatus = TRUE;

	// Check if the input path is valid.
	if (!PathFileExistsW(m_Settings.input_directory))
	{
		// If the path does not exist, set the default path.
		_tcscpy_s(m_Settings.input_directory, _MAX_PATH, TEXT(".\\IN"));
		bStatus = FALSE;
	}
	// Check if the output path is valid.
	if (!PathFileExistsW(m_Settings.output_directory))
	{
		// If the path does not exist, set the default path.
		_tcscpy_s(m_Settings.output_directory, _MAX_PATH, TEXT(".\\OUT"));
		bStatus = FALSE;
	}
	// Check if the error path is valid.
	if (!PathFileExistsW(m_Settings.error_directory))
	{
		// If the path does not exist, set the default path.
		_tcscpy_s(m_Settings.error_directory, _MAX_PATH, TEXT(".\\ERROR"));
		bStatus = FALSE;
	}
	// Check if the printer name is valid.
	if (!Printer::VerifyPrinter(m_Settings.current_printer))
	{
		// If the printer does not exist, select the system default printer.
		Printer::GetSystemDefaultPrinter(m_Settings.current_printer);
		bStatus = FALSE;
	}
	// Check if the waiting time is within the range of 1000 and 100000 milliseconds.

	size_t nWaitingTimeLen = _tcslen(m_Settings.waiting_time);

	if (nWaitingTimeLen < 4)
	{
		// If it's less than 1000 milliseconds, set it to 1000.
		_tcscpy_s(m_Settings.waiting_time, 5, L"1000");
		bStatus = FALSE;
	}
	if (nWaitingTimeLen > 6)
	{
		// If it's greater than 100000 milliseconds, set it to 100000.
		_tcscpy_s(m_Settings.waiting_time, 7, L"100000");
		bStatus = FALSE;
	}

	if (!bStatus)
	{
		Logger.Write(L"Some settings are not valid, setting it to default");
	}
	else
	{
		Logger.Write(L"Setting verification successfull.");

	}
	return bStatus;
}

BOOL Application::WriteApplicationSettings()
{
	// Verify current setting values before writing.
	BOOL bIsValid = VerifyApplicationSettings();
	/*===============================> CALCULATE THE HEADER SIZE <=========================================*/
	
	// Size of first line in the config file.
	INT nSizeOfHeader = 0;

	// Struct to store data of each names i.e. length, char length and etc.
	struct ValueData
	{
		size_t nLength = 0; // Length in character of values as integer.
		INT nSzLength = 0; // Length of length of values.
		TCHAR szLength[6] = { 0 }; // Length of values as characters.
	};
	// Lambda function to perform repeatative task of calculating lengths.
	auto GetValueData = [&](CONST TCHAR* szName)
	{
		ValueData valData;
		valData.nLength = _tcslen(szName);
		valData.nSzLength = GetNumLength(valData.nLength);
		intToTchar(valData.szLength, valData.nLength);

		return valData;
	};

	ValueData InputData = GetValueData(m_Settings.input_directory);
	ValueData OutputData = GetValueData(m_Settings.output_directory);
	ValueData ErrorData = GetValueData(m_Settings.error_directory);
	ValueData PrinterData = GetValueData(m_Settings.current_printer);
	ValueData WaitTimeData = GetValueData(m_Settings.waiting_time);

	// Calculate the header size.
	nSizeOfHeader += InputData.nSzLength;
	nSizeOfHeader += OutputData.nSzLength;
	nSizeOfHeader += ErrorData.nSzLength;
	nSizeOfHeader += PrinterData.nSzLength;
	nSizeOfHeader += WaitTimeData.nSzLength;

	nSizeOfHeader += 5; // Add 5 for each comma after every character length of values.
	nSizeOfHeader += 10; // 10 for constant bytes for names
	nSizeOfHeader += 5; // 5 for another commas.
	nSizeOfHeader += 1; // 1 for '\n'

	INT nSzSizeOfHeader = GetNumLength(nSizeOfHeader); // Get the current length of header size.
	nSizeOfHeader += nSzSizeOfHeader + 1; // Add it size of header plus one for it's comma.

	/*===============================> CALCULATE THE BODY SIZE <=========================================*/
	INT nSizeOfBody = 0;
	// First add lengths of all names i.e. length of input_directory plus length of output_directory and so on.
	nSizeOfBody += 15 + 16 + 15 + 15 + 12;
	// Now add all commas, spaces, equal, and \n. (Minus 1, since the last line does not need new line character.)
	nSizeOfBody += (4 * 5) - 1;
	// Now add lengths of all values i.e. length of value of input_directory and so on.
	nSizeOfBody +=
		InputData.nLength +
		OutputData.nLength +
		ErrorData.nLength +
		PrinterData.nLength +
		WaitTimeData.nLength;

	// Calcuate the buffer size. Plus one for null terminating character.
	TCHAR* szSettingBuffer = new TCHAR[nSizeOfHeader + nSizeOfBody + 1];

	// To store the current position in buffer.
	INT nBufferIndex = 0;

	// Buffer to store the length in character instead of int.
	
	// Buffer to store the length in character instead of int. Plus one for terminating character. (4 + 1)
	TCHAR szSizeOfHeader[4 + 1];

	// szSizeOfHeader does not include: size of itself plus it's comma plus 1 for and carriage return.
	intToTchar(szSizeOfHeader, (nSizeOfHeader - nSzSizeOfHeader - 1 - 1));


	CONST TCHAR Comma[] = L",";

	/*===============================> WRITE THE HEADER INTO THE BUFFER. <=========================================*/
	
	// Lambda function to perform repetative task of writing header into buffer.
	auto WriteHeaderToBuffer = [&](CONST TCHAR* szText, INT nTextLen)
	{
		// Write length.
		_tcscpy_s(szSettingBuffer + nBufferIndex, nTextLen + 1, szText);
		nBufferIndex += nTextLen;
		// Write it's comma.
		_tcscpy_s(szSettingBuffer + nBufferIndex, 1 + 1, Comma);
		nBufferIndex += 1;
	};
	
	// Write total Length and all lengths of names and values, including each comma.
	WriteHeaderToBuffer(szSizeOfHeader, nSzSizeOfHeader);
	WriteHeaderToBuffer(L"15", 2);
	WriteHeaderToBuffer(InputData.szLength, InputData.nSzLength);
	WriteHeaderToBuffer(L"16", 2);
	WriteHeaderToBuffer(OutputData.szLength, OutputData.nSzLength);
	WriteHeaderToBuffer(L"15", 2);
	WriteHeaderToBuffer(ErrorData.szLength, ErrorData.nSzLength);
	WriteHeaderToBuffer(L"15", 2);
	WriteHeaderToBuffer(PrinterData.szLength, PrinterData.nSzLength);
	WriteHeaderToBuffer(L"12", 2);
	WriteHeaderToBuffer(WaitTimeData.szLength, WaitTimeData.nSzLength);

	// Insert a new line.
	_tcscpy_s(szSettingBuffer + nBufferIndex, 1 + 1, L"\n");
	nBufferIndex++;

	/*===============================> WRITE THE BODY INTO THE BUFFER. <=========================================*/

	CONST TCHAR LineFeed[] = L"\n";
	// Lambda function to perform repetative task of writing body into buffer.
	auto WriteBodyToBuffer = [&](CONST TCHAR* szName, CONST TCHAR* szValue, INT nNameLen, INT nValueLen, BOOL isNextNewLine = TRUE)
	{
		// Write the name, spaces, and equal sign.
		_tcscpy_s(szSettingBuffer + nBufferIndex, nNameLen + 1, szName);
		nBufferIndex += nNameLen;

		// Write the value.
		_tcscpy_s(szSettingBuffer + nBufferIndex, nValueLen + 1, szValue);
		nBufferIndex += nValueLen;

		// Insert a new line, except last line.
		if (isNextNewLine)
		{
			_tcscpy_s(szSettingBuffer + nBufferIndex, 1 + 1, LineFeed);
			nBufferIndex += 1;
		}
	};


	WriteBodyToBuffer(L"input_directory = ", m_Settings.input_directory, (15 + 3), InputData.nLength);
	WriteBodyToBuffer(L"output_directory = ", m_Settings.output_directory, (16 + 3), OutputData.nLength);
	WriteBodyToBuffer(L"error_directory = ", m_Settings.error_directory, (15 + 3), ErrorData.nLength);
	WriteBodyToBuffer(L"current_printer = ", m_Settings.current_printer, (15 + 3), PrinterData.nLength);
	WriteBodyToBuffer(L"waiting_time = ", m_Settings.waiting_time, (12 + 3), WaitTimeData.nLength, FALSE); // Don't insert a new line.

	// Completed writing, no need to terminate since _tcslen_s will automatically terminate the buffer.

	// Write them into the config file.
	_WriteSettingsToFile(szSettingBuffer, nBufferIndex);

	delete[] szSettingBuffer;
	return TRUE;
}

BOOL Application::SaveApplicationSettings(const AppSettings& newSettings)
{
	//================> Pause application if still running.

	// Not all setting's values might be changed, so only write changed settings.

	// _tcscpy_s does not clear the memory before copying new data.
	// The memory will still hold values from previous writing, if it's length exceed the current value's length.
	// However, it's not important.

	// Lambda function to perform repetative task of changing the current to new setting's value.
	auto ChangeSettings = [&](TCHAR* szCurrentValue, CONST TCHAR* szNewValue)
	{
		// Get the lengths of new setting's value.
		size_t nNewValueSize = _tcslen(szNewValue);

		// Change only if it has been changed.
		if (nNewValueSize != 0)
		{
			_tcscpy_s(szCurrentValue, nNewValueSize + 1, szNewValue);
			 
		}
	};

	// Change the settings.
	ChangeSettings(m_Settings.input_directory, newSettings.input_directory);
	ChangeSettings(m_Settings.output_directory, newSettings.output_directory);
	ChangeSettings(m_Settings.error_directory, newSettings.error_directory);
	ChangeSettings(m_Settings.current_printer, newSettings.current_printer);
	ChangeSettings(m_Settings.waiting_time, newSettings.waiting_time);

	// Write the settings to config file.
	WriteApplicationSettings();

	return TRUE;
}

BOOL Application::_WriteSettingsToFile(CONST TCHAR* szBuffer, INT nBufferLen)
{
	Logger.Write(L"Saving application settings!");

	auto size1 = sizeof(szBuffer);
	auto size2 = size1 / sizeof(TCHAR);
	auto size3 = _tcslen(szBuffer);
	auto size4 = sizeof(TCHAR);

	// Get a handle to the config file.
	HANDLE hFile = CreateFileW(
		SETTINGS_CONFIGFILEDIR, // Destination, where to wirte.
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	// Number of bytes written.
	DWORD dwBytesWritten = 0;
	DWORD dwBytesToWrite = nBufferLen * 2;
	// Write the buffer to the config file.
	BOOL bSuccess = WriteFile(hFile, (LPCVOID)szBuffer, dwBytesToWrite, &dwBytesWritten, NULL);
	CloseHandle(hFile);

	if (bSuccess && dwBytesWritten == dwBytesToWrite) return TRUE;

	return FALSE;
}

TCHAR* Application::_ReadSettingsFromFile()
{
	HANDLE hFile = CreateFileW(
		SETTINGS_CONFIGFILEDIR, // Destination, where to wirte.
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	DWORD dwBytesToRead = 0; // Size of the config file in bytes.
	DWORD dwBytesRead = 0; // Number of bytes already read.
	DWORD dwRealFileCharLen = 0; // Store the size of actual number of ansi characters in the file.

	// The size fetched is twice the orignial number of bytes, since every character requires two bytes.
	dwBytesToRead = GetFileSize(hFile, NULL);

	// Divide by 2, to get number of characters.
	dwRealFileCharLen = dwBytesToRead / 2;
	// Allocate buffer to store read bytes, plus 1 for null terminating character.
	TCHAR* SettingBuffer = new TCHAR[dwRealFileCharLen + 1];

	BOOL bSuccess = ReadFile(hFile, SettingBuffer, dwBytesToRead, &dwBytesRead, NULL);

	CloseHandle(hFile);

	if (!bSuccess)
	{
		delete[] SettingBuffer;
		return NULL;
	}
	
	if (dwBytesRead > 0 && dwBytesRead <= dwBytesToRead)
	{
		SettingBuffer[(INT)dwRealFileCharLen] = L'\0';
	}
	else
	{
		delete[] SettingBuffer;
		return NULL;
	}

	return SettingBuffer;
}

INT Application::_GetHeaderLine(const TCHAR* szBuffer, INT(&positions)[MAXHEADERVALUES])
{
	INT index = 0;

	/*=================================== CORRECTION NEEDED =====================================*/
	/* MAX CHARACTER LIMIT SHOULD BE (4 * 5) + 10 */

	// The first value in the buffer before comman is the size of the entire first line.
	// Considering all 5 values has max character limit of 4 bytes, then the maximum length of first line is:
	// (4 * 10) + (10 for each comma) => 50.
	// 50 is only 2 bytes, therefore, the first comma should be at position less than 3.
	// Find the first comma to know the size of the first line.
	// Based on the above logic, done some random comparasion to exit out of loop. i < INFINITY could work.

	for (INT i = 0; i < 3; i++)
	{
		if (szBuffer[i] == L',')
		{
			index = i;
			break;
		}
	}

	// In valid file, position of comma cannot be greater than 3.
	if (index == 0) return -1;

	// Size is based on the above logic, plus one for terminating character.
	TCHAR szSizeOfHeaderLine[2 + 1] = { 0 };
	_tcsncpy_s(szSizeOfHeaderLine, 3, szBuffer, index);
	
	INT nSizeOfHeaderLine = _tstoi(szSizeOfHeaderLine);

	// Size is based on the above logic, plus one for terminating character.
	TCHAR szHeaderLine[50 + 1] = { 0 };
	//_tcscpy_s(szHeaderLine, nSizeOfHeaderLine, (szBuffer + index + 1));
	_tcsncpy_s(szHeaderLine, 51, (szBuffer + index + 1), nSizeOfHeaderLine);

	index = 0;
	INT posIndex = 0;

	for (INT i = 0; i < nSizeOfHeaderLine; i++)
	{
		if (szHeaderLine[i] == ',')
		{
			// Maximum character limit for all values is 4.
			TCHAR szNum[4 + 1] = { 0 };
			_tcsncpy_s(szNum, 5, (szHeaderLine + index), (i - index));
			szNum[i - index] = L'\0';
			index = (i + 1);
			positions[posIndex] = _tstoi(szNum);
			posIndex++;
		}
	}

	// Since index is reset after the size of first line is computed, getting the position of next line is tricky.
	// Position: 
	// Position of last comma.
	// Plus 2 or 3 depending on the character size of first value in the buffer.
	return (index + (nSizeOfHeaderLine < 10 ? 2 : 3));
}

BOOL Application::_ParseSettings(CONST TCHAR* szBuffer, CONST INT(&positions)[MAXHEADERVALUES])
{
	/*
		 Define the maximum size for the config file.

		 Length of input path + output path + error path + waiting time.
		 Size in bytes of MAX_PATH + MAX_PATH + MAX_PATH + DWORD

		 ----------> 260 + 260 + 260 + 4 = 784


		Plus the default text.

		input_directory =
		output_directory =
		printer =
		waiting_time =


		(15 + 3) + (16 + 3) + (7 + 3) + (12 + 3) = 62

		Plus 1 for null terminating character

		TOTAL MAXIMUM SIZE = 846 + 1

	*/

	return TRUE;
}


INT GetNumLength(INT num) { return (num < 10 ? 1 : (num < 100 ? 2 : (num < 1000 ? 3 : (num < 10000 ? 4 : 5)))); };

BOOL intToTchar(TCHAR* szNum, INT num)
{
	// Any value cannot be greater than 100000.
	if (num < 0 || num >= 100000)
	{
		szNum[0] = L'\0';
		return FALSE;
	}

	// Maximum number can be 9999 which is only 4 in character length.
	INT numLen = GetNumLength(num);

	// Start writing from second last byte, since the last is \0.
	for (INT i = numLen - 1; i >= 0; i--)
	{
		szNum[i] = num % 10 + '0';
		num /= 10;
	}

	szNum[numLen] = L'\0';

	return TRUE;
}
