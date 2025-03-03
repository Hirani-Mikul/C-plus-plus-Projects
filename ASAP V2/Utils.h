#pragma once

#include <Windows.h>
#include <winspool.h>

#include <string>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <unordered_map>

namespace utils {

	

	std::string NowToString()
	{
		std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
		time_t t = std::chrono::system_clock::to_time_t(p);
		char str[26];
		ctime_s(str, sizeof str, &t);

		std::string str_time(str);

		return str_time.substr(11, 8);

		//return str;
	}

	std::string getDate()
	{
		time_t ttime = time(0);
		struct tm local_time;
		localtime_s(&local_time, &ttime);

		std::string day = std::to_string(local_time.tm_mday);
		std::string month = std::to_string(1 + local_time.tm_mon);
		std::string year = std::to_string(1900 + local_time.tm_year);

		return day + "-" + month + "-" + year;
	}

	void writeLogFile(const std::string&& message, std::string path, const std::string &log_path) {
		
		std::ofstream output;

		output.open(log_path, std::ios_base::app);

		output << utils::NowToString() << "-> " << message << ": " << path << "\n";

		output.close();
	}

	std::pair<std::string, std::string> parseRawFileContent(const std::string& rawContent)
	{
		// Find better way to parse the config file.

		// Separate the line fetched.
		size_t pos = rawContent.find('=');

		if (pos == -1)
		{
			// This means the line has invalid setting.
			return std::pair<std::string, std::string> { "NULL", "NULL" };
		}
		std::string tag = rawContent.substr(0, pos - 1);
		std::string value = rawContent.substr(pos + 2);

		if (value[0] == ' ')
			return std::pair<std::string, std::string> { "NULL", "NULL" };

		return std::pair<std::string, std::string> { tag, value };
	}

	char* readFile(const std::filesystem::path& path, std::streampos& documentLength) {

		std::ifstream file;

		file.open(path.c_str(), std::ios_base::binary);
		file.unsetf(std::ios_base::skipws);

		documentLength = file.tellg();

		file.seekg(0, std::ios::end);
		documentLength = file.tellg() - documentLength;

		file.seekg(0, std::ios::beg);

		char* buffer = new char[(int)documentLength];

		char ch;
		int index = 0;

		while (file >> ch)
		{
			if (index < documentLength)
				buffer[index] = ch;

			index++;
		}

		file.close();
		return buffer;
	}

	bool printFile(const TCHAR* printer, const std::string &fileName, const char *data, DWORD dwCount) {

		BOOL bStatus = FALSE;
		HANDLE hPrinterHandle = INVALID_HANDLE_VALUE;
		DWORD bytes_written = 0;
		DOC_INFO_1 docInfo = { 0 };
		DWORD dwJob = 0L;

		bStatus = OpenPrinter((LPTSTR)printer, &hPrinterHandle, NULL);

		if (bStatus)
		{
			std::string filePath = "./OUT\\" + fileName;

			docInfo.pDocName = (LPTSTR)fileName.c_str();
			docInfo.pOutputFile = (LPTSTR)filePath.c_str();
			docInfo.pDatatype = (LPTSTR)(L"RAW");

			dwJob = StartDocPrinter(hPrinterHandle, 1, (LPBYTE)&docInfo);

			if (dwJob > 0)
			{
				bStatus = StartPagePrinter(hPrinterHandle);

				if (bStatus)
				{
					bStatus = WritePrinter(hPrinterHandle, (LPVOID)data, dwCount, &bytes_written);
					EndPagePrinter(hPrinterHandle);
				}
				EndDocPrinter(hPrinterHandle);

			}
			ClosePrinter(hPrinterHandle);
		}

		return bStatus;
	}

	TCHAR* getSystemDefaultPrinter() {

		DWORD dwSize = 0;
		
		GetDefaultPrinter(NULL, &dwSize);

		if (dwSize)
		{
			TCHAR* buffer = new TCHAR[dwSize];

			GetDefaultPrinter(buffer, &dwSize);

			return buffer;
		}

		return nullptr;
	}
	bool verifyPrinter(const TCHAR* printer)
	{
		HANDLE hPrinterHandle = INVALID_HANDLE_VALUE;

		bool bStatus = OpenPrinter((LPTSTR)printer, &hPrinterHandle, NULL);

		if (bStatus)
		{
			ClosePrinter(hPrinterHandle);
			return true;
		}

		return false;
	}

}