#pragma once
#include <string>
#include <fstream>
#include "json.hpp"

using json::JSON;

class FileStream {

public:
	FileStream(const FileStream&) = delete;

	static FileStream& Get()
	{
		static FileStream Instance;

		return Instance;
	}

	static void WriteToFile(const char* filePath, JSON data) { Get()._WriteToFile(filePath, data); }
	static std::string ReadFile(const char* filePath) { return Get()._ReadFile(filePath); }

private:
	std::string _ReadFile(const char* filePath) {
		
		m_InputStream.open(filePath);

		std::string text;
		std::string rawData;

		while (std::getline(m_InputStream, text))
		{
			rawData += text;
		}

		m_OutputStream.close();

		return std::move(rawData);
	}
	void _WriteToFile(const char* filePath, JSON data)
	{
		m_OutputStream.open(filePath);

		m_OutputStream << data;

		m_OutputStream.close();
	}

private:
	FileStream() {}
	std::fstream m_OutputStream;
	std::ifstream m_InputStream;
};









//void _ReadFile2(const char* path) {
//	m_InputStream.open(path);
//
//	std::vector<std::string> string;
//
//	std::string text;
//	const std::string delimiter = "{,}";
//	while (std::getline(m_InputStream, text))
//	{
//		if (text == "{" || text == "},")
//			continue;
//		const auto temptext = text;
//		const auto FindNext = [&](const auto i) {
//
//			return std::find_first_of(i, temptext.end(), delimiter.begin(), delimiter.end());
//		};
//
//		for (std::string::const_iterator i, i_prev = temptext.begin(); ; i_prev = i + 1)
//		{
//			i = FindNext(i_prev);
//			string.emplace_back(i_prev, i);
//
//			if (i == temptext.end())
//				break;
//		}
//	}
//	m_InputStream.close();
//
//	for (auto& s : string)
//		std::cout << s << std::endl;
//}