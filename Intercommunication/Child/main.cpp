/*
	This program is always outputting some content on to the console.
	When a child process is opened manually. It prompts for input
	the input is passed to the program and it is outputted in this program.


*/

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <fstream>
#include <string>
#include <TlHelp32.h>

#define BUFFERSIZE 1024

HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;

HANDLE g_hInputFile = NULL;

void WriteToPipe(void);
void ReadFromPipe(void);
DWORD FindProcessId(const std::wstring&);
void GetChildProcess(void);
void ErrorExit(const wchar_t*);

int _tmain(int argc, TCHAR* argv[]) {

	std::cout << "Parent program started.\n";

	SECURITY_ATTRIBUTES saAttr;

	// Set the bInheritHandle flag so pipes handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe for the child process's STDOUT.
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
		ErrorExit(TEXT("StdOutRd CreatePipe"));

	// Ensure the read handle to the pipe for STDOUT is not inherited
	if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
		ErrorExit(TEXT("StdOut SetHandleInformation"));

	// Create a pipe for the child process's STDIN.
	if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
		ErrorExit(TEXT("StdIn CreatePipe"));

	// Ensure the write handle to the pipe for STDIN is not inherited.
	if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
		ErrorExit(TEXT("StdIn SetHandleInformation"));

	GetChildProcess();

	std::string path_str = "./Input.txt";
	TCHAR* path = new TCHAR[path_str.size() + 1];
	path[path_str.size()] = 0;

	std::copy(path_str.begin(), path_str.end(), path);


	std::string message;
	std::cout << "Write a message: ";
	std::getline(std::cin, message);

	std::ofstream file("./Input.txt");
	file << message;

	file.close();

	g_hInputFile = CreateFile(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_READONLY,
		NULL
	);

	if (g_hInputFile == INVALID_HANDLE_VALUE)
		ErrorExit(TEXT("CreateFile"));

	// Write to the pipe that is the standard input for a child process.
	// Data is written to the pipe's buffers, so it is not necessary to wait
	// until the child process is running before writing data.


	WriteToPipe();
	std::cout << "\n->Contents of " << path_str << " written to child STDIN pipe.\n";

	// Read from pipe that is the standard output for child process.
	std::cout << "\n->Contents of child process STDOUT:\n\n";
	ReadFromPipe();


	delete[] path;

	std::cout << "End of parent execution.\n";

	// The remaining open handles are cleaned up when this process terminates.
	// To avoid resource leaks in a larger application, close handles explicitly.

	//CloseHandle(g_hChildStd_IN_Rd);
	//CloseHandle(g_hChildStd_IN_Wr);
	//CloseHandle(g_hChildStd_OUT_Rd);
	//CloseHandle(g_hChildStd_OUT_Wr);
	//CloseHandle(g_hInputFile);
	std::cin.get();
	return 0;
}

DWORD FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}


void GetChildProcess(void)
{
	DWORD processID = FindProcessId(L"Parent.exe");

	if (processID == 0) return;

	HANDLE hProcess;
	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

	if (hProcess == NULL) return;

}

void WriteToPipe(void)
{
	// Read from a file and write its contents to the pipe for the child's STDIN.
	// Stop when there is no more data.

	DWORD dwRead, dwWritten;
	CHAR chBuf[BUFFERSIZE];
	BOOL bSuccess = FALSE;

	for (;;) {

		bSuccess = ReadFile(g_hInputFile, chBuf, BUFFERSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) break;

		bSuccess = WriteFile(g_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, NULL);

		if (!bSuccess) break;
	}

	// Close the pipe handle so the child process stops reading.

	if (!CloseHandle(g_hChildStd_IN_Wr))
		ErrorExit(TEXT("StdInWr CloseHandle"));
}

void ReadFromPipe(void)
{
	// Read output from the child process's pipe for STDOUT
	// and write to the parent process's pipe for STDOUT.
	// Stop when there is no more data.
	DWORD dwRead, dwWritten;
	CHAR chBuf[BUFFERSIZE];
	BOOL bSuccess = FALSE;
	HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (;;)
	{
		bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFFERSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) break;

		bSuccess = WriteFile(hParentStdOut, chBuf,
			dwRead, &dwWritten, NULL);
		if (!bSuccess) break;
	}
}

void ErrorExit(const wchar_t* lpszFunction)
{
	// Format a readable error message, display a message box,
	// and exit from the application.

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
	ExitProcess(1);
}