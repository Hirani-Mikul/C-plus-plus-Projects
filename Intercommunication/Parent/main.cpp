#include <iostream>
#include <Windows.h>

#define BUFFERSIZE 1024

void GetCommandFromChild();

int main()
{

	return 0;
}

void GetCommandFromChild()
{
	CHAR chBuf[BUFFERSIZE];
	DWORD dwRead, dwWritten;
	HANDLE hStdIn, hStdOut;
	BOOL bSuccess;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);

	if (hStdOut == INVALID_HANDLE_VALUE || hStdIn == INVALID_HANDLE_VALUE)
		return;

	std::cout << "Child process running.\n";

	for (;;)
	{
		bSuccess = ReadFile(hStdIn, chBuf, BUFFERSIZE, &dwRead, NULL);
		
		if (!bSuccess || dwRead == 0)
			break;

		bSuccess = WriteFile(hStdOut, chBuf, dwRead, &dwWritten, NULL);

		if (!bSuccess)
			break;
	}
}