#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include <fstream>

#define BUFFERSIZE 1024

HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;

HANDLE g_hInputFile = NULL;

void CreateChildProcess(void);
void WriteToPipe(void);
void ReadFromPipe(void);
void ErrorExit(const std::string&&);


int _tmain(int argc, TCHAR *argv[]) {

	std::cout << "Parent program started.\n";

	SECURITY_ATTRIBUTES saAttr;

	// Set the bInheritHandle flag so pipes handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe for the child process's STDOUT.
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
		ErrorExit("StdOutRd CreatePipe");

	// Ensure the read handle to the pipe for STDOUT is not inherited
	if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
		ErrorExit("StdOut SetHandleInformation");

	// Create a pipe for the child process's STDIN.
	if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
		ErrorExit("StdIn CreatePipe");

	// Ensure the write handle to the pipe for STDIN is not inherited.
	if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
		ErrorExit("StdIn SetHandleInformation");

	// Create the child process.
	CreateChildProcess();

	// The file name should be LPCTSTR
	// path: C:\Users\HIRANI\Desktop\C++\Pipes\Input.txt

	//std::string path_str = "C:\\Users\\HIRANI\\Desktop\\C++\\Pipes\\Input.txt";
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
		ErrorExit("CreateFile");

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


void CreateChildProcess() {
	// Create a child process that uses the previously created pipes for STDIN.

	//TCHAR szCmdLine[] = L"C:\\Users\\HIRANI\\Desktop\\C++\\Pipes"; // Check if this is leak. It should be manually deleted.

	TCHAR szCmdLine[] = L"Pipes_Child"; // Check if this is leak. It should be manually deleted.


	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE;

	// Set up members of the PROCESS_INFORMATION structure.
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	// Set up members of the STARTUPINFO structure.
	// This structure specifies the STDIN and STDOUT handles for redirection.

	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = g_hChildStd_OUT_Wr;
	siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
	siStartInfo.hStdInput = g_hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	// Create the child process.

	bSuccess = CreateProcess(
		NULL,
		szCmdLine, // command line
		NULL, // process security attributes
		NULL, // primary thread security attributes
		TRUE, // handles are inherited
		0, // creatin flags
		NULL, // use parent's environment
		NULL, // use parent's current directory
		&siStartInfo, // STARTUPINFO pointer
		&piProcInfo // receives PROCESS_INFORMATION
	);

	if (!bSuccess)
		ErrorExit("CreateProcess");
	else
	{
		// Close handles to the child process and its primary thread.
		// Some applications might keep these handles to monitor the status
		// of the child process, for example
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);

		 // Close handles to the stdin and stdout pipes no longer needed by the child process.
		 // If they are not explicitly closed, there is no way to recognize that the child process has ended.

		CloseHandle(g_hChildStd_OUT_Wr);
		CloseHandle(g_hChildStd_IN_Rd);
	}


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
		ErrorExit("StdInWr CloseHandle");
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

void ErrorExit(const std::string&& err)
{
	// Format a readable error message, display a message box,
	// and exit from the application.

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	std::wstring wstr_err = std::wstring(err.begin(), err.end());

	LPCWSTR lpszFunction = wstr_err.c_str();


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
