
#include "utils.h"
#include "temp.h"
#include "MyQueue.h"
#include <tchar.h>
#include <bitset>

#include <charconv>

#include <stdlib.h>
struct Setting
{
	TCHAR sInput[MAX_PATH];
	TCHAR sOutput[MAX_PATH];
	TCHAR sError[MAX_PATH];
	TCHAR sPrinter[32];
	DWORD sWaiting;
};


void Initialize();

INT ReadFileSettings(CHAR* buffer)
{
	HANDLE hFile = CreateFile(
		L"C:\\Users\\HIRANI\\Desktop\\Windows API\\ASAP Console\\config3.config",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD bytesRead = 0;
	DWORD fileLen = GetFileSize(hFile, NULL);

	BOOL bSuccess = ReadFile(hFile, buffer, fileLen, &bytesRead, NULL);

	CloseHandle(hFile);

	if (bSuccess && (bytesRead == fileLen))
	{
		return fileLen;
	}
	else return 0;

}

BOOL WriteFileSettings(CHAR* buffer, DWORD fileLen)
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
	BOOL bSuccess = WriteFile(hFile, buffer, fileLen, &bytesWritten, NULL);

	if (bSuccess && bytesWritten == fileLen)
	{
		CloseHandle(hFile);
		return TRUE;
	}
	CloseHandle(hFile);

	return FALSE;
}

void FirstInitate(AppSetting& settings)
{
	CONST CHAR Input[] = ("C:\\Users\\HIRANI\\Desktop\\Project\\ASAP\\IN");     // INPUT PATH
	CONST CHAR Output[] = ("C:\\Users\\HIRANI\\Desktop\\Project\\ASAP\\OUT");    // OUTPUT PATH
	CONST CHAR Error[] = ("C:\\Users\\HIRANI\\Desktop\\Project\\ASAP\\ERROR");  // ERROR PATH
	CONST CHAR Printer[] = ("Microsoft XPS Document Writer");  // PRINTER NAME
	
	size_t lenInput = strlen(Input);
	size_t lenOutput = strlen(Output);
	size_t lenError = strlen(Error);
	size_t lenPrinter = strlen(Printer);

	memcpy(settings.input_directory, Input, lenInput);
	memcpy(settings.output_directory, Output, lenOutput);
	memcpy(settings.error_directory, Error, lenError);
	memcpy(settings.current_printer, Printer, lenPrinter);

	settings.waiting_time = 5000;
}

void convert(int num, TCHAR* szNum)
{
	for (int i = 4; i >= 0; i--)
	{
		auto ch = num % 10 + '0';
		szNum[i] = num % 10 + '0';
		num /= 10;
	}
}


bool getBitState(char value, int pos)
{
	// To check if the bit is on at pos,
	// use AND (&) with mask with bit on that pos.
	char mask = 0b00000001;
	bool isOn = false;

	for (int i = 1; i < 9; i++)
	{
		if (i == pos)
		{
			int j = 0;
			mask = mask << (i - 1);
		}
	}

	isOn = value & mask;

	return isOn;
}

int _tmain(int argc, TCHAR* argv[])
{
	std::cout << "Bitwise operation.\n";

	char stat = 0b00000000;
	char mask = 0b00010000;

	char stat2 = 0b10101010;

	std::cout << "initial stat2: " << std::bitset<8>(stat2) << std::endl;

	std::cout << "second2 stat2: ";
	for (int i = 8; i > 0; i--)
	{
		bool isOn = getBitState(stat2, i);
		std::cout << isOn;
	}

	std::cout << std::endl;

	return 0;

	std::cout << "stat: " << stat << std::endl;
	std::cout << "initial stat: " << std::bitset<8>(stat) << std::endl;
	stat = stat | mask;

	std::cout << "second stat: " << std::bitset<8>(stat) << std::endl;

	mask = 0b00000100;

	stat = stat | mask;
	std::cout << "third stat: " << std::bitset<8>(stat) << std::endl;

	mask = 0b00000010;

	stat = stat | mask;
	std::cout << "forth stat: " << std::bitset<8>(stat) << std::endl;


	mask = 0b00000001;
	stat = stat | mask;

	std::cout << "fifth stat: " << std::bitset<8>(stat) << std::endl;

	return 0;
	TCHAR sznum[] = L"10320";

	auto num = _tstoi(sznum);

	//auto szNum = _itot(num, ;
	TCHAR szNum2[9] = { 'L'};
	convert(num, szNum2);
	
	std::wcout << "sznum: " << sznum << std::endl;
	std::wcout << "num: " << num << std::endl;
	std::wcout << "szNum2: " << szNum2 << std::endl;

	return 0;

	TCHAR buff[_MAX_ITOSTR_BASE16_COUNT];

	int num2 = 23;

	auto szNum = _itot_s(num2, buff, _MAX_ITOSTR_BASE16_COUNT);

	std::wcout << "szNum: " << szNum << std::endl;
	return 0;
	Temp temp;

	CHAR* buffer = Read();

	Parse(buffer, temp);

	BOOL bSuccess1 = Write(temp);

	if (buffer == NULL)
		delete buffer;
	else delete[] buffer;

	return 0;
	/*
	AppSetting initialSettings;
	FirstInitate(initialSettings);
	BOOL bSuccess1 = WriteAppSettings(initialSettings);

	return 0;

	*/
	AppSetting settings;

	CHAR* Buffer = ReadAppSettings();

	ParseSetting(Buffer, settings);

	BOOL bSuccess = WriteAppSettings(settings);

	if (Buffer == NULL)
		delete Buffer;
	else delete[] Buffer;


	return 0;
}

void Initialize()
{
	Setting settings;

	LPCWSTR Input = TEXT("C:\\Users\\HIRANI\\Desktop\\Project\\ASAP\\IN");     // INPUT PATH
	LPCWSTR Output = TEXT("C:\\Users\\HIRANI\\Desktop\\Project\\ASAP\\OUT");    // OUTPUT PATH
	LPCWSTR Error = TEXT("C:\\Users\\HIRANI\\Desktop\\Project\\ASAP\\ERROR");  // ERROR PATH
	LPCWSTR Printer = TEXT("Microsoft XPS Document Writer");  // PRINTER NAME

	size_t lenInput = _tcslen(Input);
	size_t lenOutput = _tcslen(Output);
	size_t lenError = _tcslen(Error);
	size_t lenPrinter = _tcslen(Printer);

	_tcscpy_s(settings.sInput, lenInput + 1, Input);
	_tcscpy_s(settings.sOutput, lenOutput + 1, Output);
	_tcscpy_s(settings.sError, lenError + 1, Error);
	_tcscpy_s(settings.sPrinter, lenPrinter + 1, Printer);

	settings.sWaiting = 1000;

}

