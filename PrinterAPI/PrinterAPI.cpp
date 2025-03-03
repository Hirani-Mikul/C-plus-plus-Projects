// PrinterAPI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <winspool.h>
#include <vector>
#include <wingdi.h>



#define LOG_ERROR(message, error) \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); \
	std::cout << message << " -> " << error << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) 


#define LOG_SUCCESS(message) \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); \
	std::cout << message << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) 


#define LOG_WARNING(message) \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); \
	std::cout << message << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)



#define LOG_INFO(message) \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); \
	std::cout << message << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) 

BOOL RawDataToPrinter(LPTSTR, LPCTSTR, DWORD);


int main()
{
	std::vector<std::string> mountedPrinters;

	int printerToUse = int{ };

    PRINTER_INFO_5* printer = NULL;
	DWORD sizeBuffer = 0;
	DWORD entries = 0; // Total number of mounted printers

	HANDLE hPrinterHandle = INVALID_HANDLE_VALUE;
	DOC_INFO_1 docInfo;

	LPWORD bytes_written = 0;
	char docName[] = "test";
	char dataType[] = "text";

	// GET BUFFER SIZE
	// RETURNS ERROR

	EnumPrinters(
		PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS,
		NULL,
		5,
		NULL,
		NULL,
		&sizeBuffer,
		&entries
	);

	// -------------------- PRINT THE BUFFER SIZE -----------------

	printer = (PRINTER_INFO_5*)malloc(sizeBuffer);

	// Now successfully fetches the mounted printers

	EnumPrinters(
		PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS,
		NULL,
		5,
		(LPBYTE)printer,
		sizeBuffer,
		&sizeBuffer,
		&entries
	);
	if (!entries) {
		LOG_ERROR("Found 0 Printers OR Failed to fetch printers", GetLastError());
		return 0;
	}
	else {
		mountedPrinters.resize((int)entries);

		for (int i = 0; i < (int)entries; i++)
		{
			std::wstring wstr(printer[i].pPrinterName);
			mountedPrinters[i] = std::string(wstr.begin(), wstr.end());

		}
	}
	
	free(printer);

	LOG_INFO("Printer List: ");

	for (int i = 0; i < mountedPrinters.size(); i++)
	{
		std::cout << i + 1 << "\t" << mountedPrinters[i] << std::endl;

	}
	printerToUse = 3;

	std::string filePathIn = "C:\\Users\\HIRANI\\Desktop\\C++\\PrinterAPI\\IN\\ReadMe.txt";

	std::ifstream inputStream;

	inputStream.open(filePathIn);

	std::string text;
	std::string rawData;

	while (std::getline(inputStream, text))
	{
		rawData += text;
	}

	inputStream.close();


	std::wstring wstr_printerName
		= std::wstring(mountedPrinters[printerToUse].begin(), mountedPrinters[printerToUse].end());

	std::cout << "\n\nSelected printer: " << mountedPrinters[printerToUse] << std::endl;

	std::string str_printText = "HELLO THERE, MY NAME IS PRINTER. ";
	const char* c_printText = rawData.c_str();

	//BOOL bStatus = RawDataToPrinter((LPTSTR)wstr_printerName.c_str(), (LPBYTE)str_printText.c_str(), (DWORD)std::strlen(str_printText.c_str()));
	BOOL bStatus = RawDataToPrinter((LPTSTR)wstr_printerName.c_str(), (LPCTSTR)c_printText, (DWORD)std::strlen(rawData.c_str()));

	if (bStatus) { LOG_SUCCESS("Successfully written to printer."); }
	else { LOG_ERROR("Failed to write content to printer", GetLastError()); }

}


/*
	AddJob()
	ClosePrinter()
	EndDocPrinter()
	EndPagePrinter()
	EnumJobs()
	GetJob()
	OpenPrinter()
	SetJob()
	StartDocPrinter()
	StartPagePrinter()


	EnumPrinters()
	GetDefaultPrinter()
	WritePrinter()

*/

BOOL RawDataToPrinter(LPTSTR szPrinterName, LPCTSTR lpData, DWORD dwCount)
{
    BOOL     bStatus = FALSE;
    HANDLE     hPrinter = NULL;
	DOC_INFO_1 DocInfo = {0};
    DWORD      dwJob = 0L;
    DWORD      dwBytesWritten = 0L;

    // Open a handle to the printer. 
    bStatus = OpenPrinter(szPrinterName, &hPrinter, NULL);
    if (bStatus) {
        // Fill in the structure with info about this "document." 
		//DocInfo.pDocName = (LPTSTR)(L"Trial");
		DocInfo.pDocName = (LPTSTR)(L"ReadMe");
		//DocInfo.pOutputFile = (LPTSTR)(L"C:\\Users\\HIRANI\\Desktop\\C++\\PrinterAPI\\OUT\\ReadMe.pdf");
		//DocInfo.pOutputFile = (LPTSTR)(L"TRIAL\0");
		DocInfo.pOutputFile = (LPTSTR)(NULL);
		DocInfo.pDatatype = (LPTSTR)(L"RAW");
		//DocInfo.pDatatype = NULL;

        // Inform the spooler the document is beginning. 
        dwJob = StartDocPrinter(hPrinter, 1, (LPBYTE)&DocInfo);


        if (dwJob > 0) {
            // Start a page. 
            bStatus = StartPagePrinter(hPrinter);
            if (bStatus) {
                // Send the data to the printer. 
                bStatus = WritePrinter(hPrinter, (void*)lpData, dwCount, &dwBytesWritten);
				std::cout << "Total bytes: " << dwCount << std::endl;
				std::cout << "Bytes written: " << dwBytesWritten << std::endl;
                EndPagePrinter(hPrinter);
            }
            // Inform the spooler that the document is ending. 
            EndDocPrinter(hPrinter);
        }
        // Close the printer handle. 
        ClosePrinter(hPrinter);
    }
    // Check to see if correct number of bytes were written. 
    if (!bStatus || (dwBytesWritten != dwCount)) {
        bStatus = FALSE;
    }
    else {
        bStatus = TRUE;
    }
    return bStatus;
}