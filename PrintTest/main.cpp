#include <iostream>
#include <Windows.h>
#include <winspool.h>
#include <vector>
#include <string>
#include <atlstr.h>

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



//bool getAllPrinters(std::vector<LPWSTR>&, std::vector<std::string>&);
bool getAllPrinters(LPWSTR&, std::vector<std::string>&);

std::unique_ptr<BYTE[]> ptrBuffer;



int main()
{
	std::vector<LPWSTR> printerList;
	LPWSTR printer2;
	std::vector<std::string> printerListName;

	HANDLE hPrinterHandle = INVALID_HANDLE_VALUE;
	LPWORD bytes_w = 0;
	DOC_INFO_1 doc_info;
	char docName[] = "Test document";
	char docType[] = "text";
	char docOut[] = "NULL";


	//bool arePrintersAvailable = getAllPrinters(printerList, printerListName);
	bool arePrintersAvailable = getAllPrinters(printer2, printerListName);

	PRINTER_INFO_5* printer = (PRINTER_INFO_5*)ptrBuffer.get();
	PRINTER_INFO_5* printerToUse = NULL;

	std::cout << "Printer List: " << std::endl;

	for (int i = 0; i < 5; i++)
	{
		if (i == 1) printerToUse = printer;

		std::wstring wstr = std::wstring(printer->pPrinterName);
		std::string pname = std::string(wstr.begin(), wstr.end());
		std::cout << i + 1 << "\t" << pname << std::endl;

		printer++;
	}

	if (!arePrintersAvailable)
	{
		LOG_ERROR("Windows Error: ", GetLastError());

		return 0;
	}


	/*int printerNum = 1;

	for (auto& p : printerListName)
	{
		std::cout << printerNum << "\t" << p << std::endl;
		printerNum++;
	}*/

	std::wstring wstr = std::wstring(printerToUse->pPrinterName);
	std::string pname = std::string(wstr.begin(), wstr.end());
	std::cout << std::endl << std::endl;
	std::cout << "Printer name: " + pname << std::endl;

	bool openPrinter = OpenPrinter(
		printerToUse->pPrinterName,
		&hPrinterHandle,
		NULL
	);


	if (!openPrinter)
	{
		LOG_ERROR("Error Opening Printer", GetLastError());
		return 0;
	}
	else { LOG_SUCCESS("Printer successfully opened."); }

	char printText[] = "HELLO THERE, MY NAME IS MIKUL HIRANI!";
	doc_info.pDocName = (LPWSTR)docName;
	doc_info.pDatatype = (LPWSTR)docType;
	//doc_info.pOutputFile = (LPWSTR)docOut;
	doc_info.pOutputFile = NULL;

	StartDocPrinter(hPrinterHandle, 1, (LPBYTE)&doc_info);
	StartPagePrinter(hPrinterHandle);
	auto temp = WritePrinter(hPrinterHandle, printText, std::strlen(printText), (LPDWORD)&bytes_w);

	if (temp) LOG_SUCCESS("Written successfully");

	EndPagePrinter(hPrinterHandle);
	EndDocPrinter(hPrinterHandle);
	ClosePrinter(hPrinterHandle);


	LOG_WARNING("JOB DONE.");
}

//bool getAllPrinters(std::vector<LPWSTR>& printerList, std::vector<std::string>& printerListName) {
	bool getAllPrinters(LPWSTR& printer2, std::vector<std::string>& printerListName) {
	PRINTER_INFO_5* printer = nullptr;
	DWORD sizeBuffer = 0;
	DWORD entries = 0; // Total number of printers installed in the system

	// Get buffer size

	BOOL enumPrinter_1 = EnumPrinters(
		PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS, // Flag
		NULL, // Name
		5, // Level
		NULL, // pPrinterEnum
		NULL, // cbBuf
		&sizeBuffer, // pcbNeeded
		&entries // pcReturned
	);

	if (!enumPrinter_1)
	{
		LOG_ERROR("Fetching local printer failed: ", GetLastError());

	}

	ptrBuffer = std::unique_ptr<BYTE[]>(new BYTE[sizeBuffer]);
	//std::unique_ptr<BYTE[]> ptrBuffer(new BYTE[sizeBuffer]);
	//std::unique_ptr<BYTE[]> ptrBuffer(new BYTE[sizeBuffer]);

	BOOL enumPrinter_2 = EnumPrinters(
		PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS,
		NULL,
		5,
		ptrBuffer.get(),
		sizeBuffer,
		&sizeBuffer,
		&entries
	);

	if (!enumPrinter_2)
	{
		LOG_ERROR("Fetching printers failed: ", GetLastError());

	}
	else LOG_SUCCESS("Successfully fetched the printers.");

	if (!entries) return false;

	else {
		//printer = (PRINTER_INFO_5*)ptrBuffer.get();
		std::cout << entries << " printers found." << std::endl;

		//printerList.resize(entries);
		//printerListName.resize(entries);


		//for (UINT i = 0; i < entries; i++)
		//{
		//	if (i == 2) printer2 = printer->pPrinterName;

		//	std::wstring wspn(printer->pPrinterName);

		//	printerListName[i] = std::string(wspn.begin(), wspn.end());

		//	std::cout << i + 1 << ": " << printer->pPrinterName<< std::endl;

		//	//printerList[i] = printer->pPrinterName;

		//	printer++; // Next printer
		//}
	
	}

	return true;

}



/*

			// First convert from LPWSTR to wstring
			std::wstring wstring_pritnerName = std::wstring(printer->pPrinterName);

			// convert wstring to string
			printerList.emplace_back(std::string(wstring_pritnerName.begin(), wstring_pritnerName.end()));

	int printerNum = 1;


				for (auto& p : printerList)
	{
		//std::wstring wstring_pritnerName = std::wstring(p);
		//std::string pname = std::string(wstring_pritnerName.begin(), wstring_pritnerName.end());
		// convert wstring to string

		std::wstring wspn(p);
		std::string pname = std::string(wspn.begin(), wspn.end());

		std::cout << printerNum << "\t" << pname << std::endl;
		printerNum++;
	}

			*/