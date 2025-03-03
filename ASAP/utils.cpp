#include "utils.h"

Console console;
TextBox Logger;

DWORD Exit_Code = -1;

void _Write(const char* text)
{
#ifdef  DEBUGMODEON
	console.Write(text);
#endif //  DEBUGMODEON

}
void _Write(const char* text, int intVal)
{
#ifdef  DEBUGMODEON
	console.Write(text, intVal);
#endif //  DEBUGMODEON

}
void _Write(const char* text, const char* text2 )
{
#ifdef  DEBUGMODEON
	console.Write(text, text2);
#endif //  DEBUGMODEON

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
