#pragma once

#include <iostream>

#include <podofo/podofo.h>

#include <fstream>

#include <winspool.h>
#include <Windows.h>

using namespace PoDoFo;

int main() {


	try
	{
		PdfInputDevice pDevice("./IN/Files.pdf");

		std::streampos len = pDevice.Tell();

		pDevice.Seek(0, std::ios::end);

		len = pDevice.Tell() - len;

		std::cout << "Length: " << len << std::endl;

		char* buff = new char[(int)len];

		pDevice.Seek(0, std::ios::beg);

		auto test = pDevice.Read(buff, len);


		PRINTER_INFO_5* printer = NULL;
		DWORD sizeBuffer = 0;
		DWORD entries = 0; // Total number of mounted printers

		HANDLE hPrinterHandle = INVALID_HANDLE_VALUE;

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
		EnumPrinters(
			PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS,
			NULL,
			5,
			(LPBYTE)printer,
			sizeBuffer,
			&sizeBuffer,
			&entries
		);
		BOOL     bStatus = FALSE;
		HANDLE     hPrinter = NULL;
		DOC_INFO_1 DocInfo = { 0 };
		DWORD      dwJob = 0L;
		DWORD      dwBytesWritten = 0L;

		bStatus = OpenPrinter(printer[3].pPrinterName, &hPrinter, NULL);
		if (bStatus)
		{
			DocInfo.pDocName = (LPTSTR)(L"Files.pdf");
			DocInfo.pOutputFile = (LPTSTR)(L"C:\\Users\\HIRANI\\Desktop\\C++\\PDF\\OUT\\Files.pdf");
			//DocInfo.pOutputFile = (LPTSTR)(NULL);
			DocInfo.pDatatype = (LPTSTR)(L"RAW");

			// Inform the spooler the document is beginning.
			dwJob = StartDocPrinter(hPrinter, 1, (LPBYTE)&DocInfo);

			if (dwJob > 0) {
				// Start a page.
				bStatus = StartPagePrinter(hPrinter);
				if (bStatus) {
					// Send the data to the printer.

					bStatus = WritePrinter(hPrinter, (void*)buff, len, &dwBytesWritten);
					std::cout << "Bytes written: " << dwBytesWritten << std::endl;
					EndPagePrinter(hPrinter);
				}
				// Inform the spooler that the document is ending.
				EndDocPrinter(hPrinter);
			}
			// Close the printer handle.
			ClosePrinter(hPrinter);

			delete[] buff;
		}

	}
	catch (PdfError& eCode)
	{
		eCode.PrintErrorMsg();
		return eCode.GetError();

	}

	try {
		PdfEncodingFactory::FreeGlobalEncodingInstances();
	}
	catch (PdfError& eCode) {
		eCode.PrintErrorMsg();
		return eCode.GetError();
	}

	std::cout << "\n\nFINISHED!" << std::endl;

	return 0;
}