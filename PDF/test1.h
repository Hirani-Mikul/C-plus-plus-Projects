#pragma once


#include <iostream>

#include <podofo/podofo.h>


using namespace PoDoFo;

int main()
{

	return;
	PdfMemDocument doc_in;


	doc_in.Load("./IN/abcd.pdf");

	//PdfMemDocument doc_out("./OUT/hmp.pdf");
	PdfMemDocument doc_out;

	std::cout << "Author: " << doc_in.GetInfo()->GetSubject().GetString() << std::endl;




	try
	{

		doc_out.InsertPages(doc_in, 0, 1);



		doc_out.GetInfo()->SetCreator(PdfString("HMP"));
		doc_out.GetInfo()->SetAuthor(PdfString("MIKUL HIRANI"));
		doc_out.GetInfo()->SetTitle(PdfString("TRIAL"));
		doc_out.GetInfo()->SetSubject(PdfString("Testing copying"));
		doc_out.GetInfo()->SetKeywords(PdfString("Test;PDF;MPH;"));


		doc_out.Write("./OUT/hmp.pdf");
		//doc_out.WriteUpdate("./OUT/hmp.pdf");


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

	std::cout << "\n\nCopied a PDF file" << std::endl;
	return 0;
}


/*
#include <iostream>

#include <podofo/podofo.h>

#include <fstream>

#include <winspool.h>
#include <Windows.h>

using namespace PoDoFo;

int main() {


	if (1) {

	PRINTER_INFO_5* printer = NULL;
	DWORD sizeBuffer = 0;
	DWORD entries = 0; // Total number of mounted printers

	HANDLE hPrinterHandle = INVALID_HANDLE_VALUE;
	DOC_INFO_1 docInfo;

	LPWORD bytes_written = 0;
	char docName[] = "test";
	char dataType[] = "text";
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

	bStatus = OpenPrinter(printer[4].pPrinterName, &hPrinter, NULL);
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
				PdfInputDevice pDevice("./IN/abcd.pdf");

				char* buff = new char[100];

				pDevice.Read(buff, 100);

				bStatus = WritePrinter(hPrinter, (void*)buff, 100, &dwBytesWritten);
				std::cout << "Bytes written: " << dwBytesWritten << std::endl;
				EndPagePrinter(hPrinter);
			}
			// Inform the spooler that the document is ending.
			EndDocPrinter(hPrinter);
		}
		// Close the printer handle.
		ClosePrinter(hPrinter);
	}
	}


	//PdfMemDocument doc;


	//doc.Load("./IN/abcd.pdf");

	//std::cout << "Author: " << doc.GetInfo()->GetSubject().GetString() << std::endl;

	//PdfPage* page;


	return 0;
	try
	{
		//page = doc.GetPage(0);

		//auto temp = page->GetContents()->GetString();



		//PdfContentsTokenizer tok(page);
		//PdfOutputDevice pDevice("output.txt");

		PdfInputDevice pDevice("./IN/abcd.pdf");

		char* buff = new char[100];

		auto test = pDevice.Read(buff, 50);

		for (int i = 0; i < 100; i++)
		{
			std::cout << buff[i];
		}
		delete[] buff;
		//auto temp = pDevice.GetChar();

		//for (int i = 0; i < 100; i++)
		//{
		//	std::cout << (char)temp;
		//	temp = pDevice.GetChar();

		//}


		//PdfDeviceOutputStream out(&pDevice);

		//std::string ab = "fassafafdas";

		//out.Write(ab.c_str(), std::strlen(ab.c_str()));

		//const char* token = nullptr;

		//PdfVariant var;
		//EPdfContentsType type;

		//while (tok.ReadNext(type, token, var))
		//{
		//	switch (type) {
		//	case ePdfContentsType_Keyword:
		//		std::cout << "keyword: " << token << std::endl;
		//		break;

		//	case ePdfContentsType_Variant:
		//		break;
		//		std::cout << "var: " << token << std::endl;

		//	default:
		//		break;
		//	}
		//}


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

*/