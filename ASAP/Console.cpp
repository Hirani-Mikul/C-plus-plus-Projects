#include "Console.h"

Console::Console() : /*m_hSTDIn{INVALID_HANDLE_VALUE}, */ m_hSTDOut{INVALID_HANDLE_VALUE}
{
}

Console::~Console()
{
	CloseHandle(m_hSTDOut);
}

BOOL Console::Create()
{
	// Allocate console.
	BOOL bSuccess = AllocConsole();

	// If failed to allocate console return false.
	if (!bSuccess) return bSuccess;

	// Retreive standard output handle
	m_hSTDOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// If failed to retreive handle, set bSucess false.
	if (m_hSTDOut == INVALID_HANDLE_VALUE)
		bSuccess = FALSE;

	return bSuccess;
}

BOOL Console::Write(LPCSTR lpText)
{
	if (m_hSTDOut == INVALID_HANDLE_VALUE) return FALSE;

	DWORD dwBytesToWrite = lstrlenA(lpText);
	//DWORD dwBytesToWrite = lpText.size();
	DWORD dwBytesWritten = 0;

	BOOL bSuccess = WriteFile(
		m_hSTDOut, // A handle to StdOut.
		lpText, // Pointer to buffer containing data to write.
		dwBytesToWrite, // Number of bytes to write.
		&dwBytesWritten, // Number of bytes already written.
		NULL // Pointer to Overlapped structure
	);

	if (!bSuccess)
	{
		// Failed to write to the console.
		return FALSE;
	}
	else if (dwBytesWritten < dwBytesToWrite)
	{
		// No content was written, or less bytes were written.
		return FALSE;
	}

	return bSuccess;
}

BOOL Console::Write(LPCWSTR lpwText)
{
	DWORD dwBytesToWrite = wcslen(lpwText) * sizeof(wchar_t);
	DWORD dwBytesWritten = 0;

	BOOL bSuccess = WriteFile(
		m_hSTDOut,
		lpwText,
		dwBytesToWrite,
		&dwBytesWritten,
		NULL
	);

	if (!bSuccess)
	{
		// Failed to write to the console.
		return FALSE;
	}
	else if (dwBytesWritten < dwBytesToWrite)
	{
		// No content was written, or less bytes were written.
		return FALSE;
	}

	return bSuccess;
}

BOOL Console::WriteInfo(LPCSTR lpInfo)
{
	// 14 is yellow color.
	setTextColor(14);
	
	BOOL bSucess = Write(lpInfo);

	// 15 is default "white" color.
	setTextColor(15);

	return bSucess;
}

BOOL Console::WriteError(LPCSTR lpError)
{
	// 4 is red color.
	setTextColor(4);
	
	BOOL bSuccess = Write(lpError);

	// 15 is default "white" color.
	setTextColor(15);

	return bSuccess;
}

//INT Console::Read()
//{
//	return 0;
//}

void Console::Clear()
{

}

void Console::setTextColor(int color)
{

	/*
		1  : Blue
		2  : Green
		3  : Cyan
		4  : Red
		5  : Purple
		6  : Yellow(dark)
		7  : Default white
		8  : Grey
		9  : Bright blue
		10 : Bright green
		11 : Bright cyan
		12 : Bright red
		13 : pink
		14 : yellow
		15 : Bright white
	*/

	SetConsoleTextAttribute(m_hSTDOut, color);
}

BOOL Console::Write(LPCSTR lpText, int intVal) // If T is int
{
	std::string text(lpText);
	text += std::to_string(intVal);
	text += "\n";

	return Write(text.c_str());
}

BOOL Console::Write(LPCSTR lpText, LPCSTR lpText2)
{
	std::string text(lpText);
	text += lpText2;
	text += "\n";

	return Write(text.c_str());
}
