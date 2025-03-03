#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "json.hpp"

using json::JSON;

// SINGLETON 
// USED TO READ AND WRITE FROM AND TO TEXT FILES 

class FileStream
{
public:
	FileStream(const FileStream&) = delete;

	static FileStream& Get()
	{
		static FileStream Instance;

		return Instance;
	}

public:

	static JSON ReadFile(const char* filePath) { return Get()._ReadFile(filePath); }

	static void WriteToFile(const char* filePath, const JSON data ) { Get()._WriteToFile(filePath, data); }

	static void AppendToFile(const char* filePath, const JSON& data) { Get()._AppendToFile(filePath, data); }

private:

	JSON _ReadFile(const char* filePath)
	{
		m_InputStream.open(filePath);

		std::string text;
		std::string rawData;

		while (std::getline(m_InputStream, text))
		{
			rawData += text;
		}

		m_InputStream.close();

		if (rawData.empty()) return JSON::JSON();

		return JSON::Load(rawData);
	}

	void _WriteToFile(const char* filePath, const JSON data)
	{
		m_OutputStream.open("temp.txt");

		m_OutputStream << data;

		m_OutputStream.close();

		// Removes the old file, and renames the temp file to the filePath

		std::remove(filePath);
		std::rename("temp.txt", filePath);
	}

	void _AppendToFile( const char* filePath, const JSON& data )
	{
		// Temporarily store data in buffer
		// Therefore, modification is done
		// And modified string is written to text file

		// THIS FUNCTION IS ONLY APPLICABLE TO ADD NEW USER
		// BECAUSE TEXT FILES ARE NOT EDITABLE (EASILY).
		// THEREFORE, YOU HAVE TO WRITE THE ENTIRE DATA INTO A FILE

		m_InputStream.open(filePath);

		std::stringstream buffer;

		buffer << m_InputStream.rdbuf();

		m_InputStream.close();

		std::string bufferStr = buffer.str();

		if (bufferStr.size() > 0)
			bufferStr.pop_back();

		m_OutputStream.open(filePath);

		if (bufferStr.size() > 0)
		{
			m_OutputStream << bufferStr;
			m_OutputStream << ',';
			m_OutputStream << data;
			m_OutputStream << ']';
		}

		else
		{
			m_OutputStream << '[';
			m_OutputStream << data;
			m_OutputStream << ']';
		}

		m_OutputStream.close();
	}

private:
	FileStream() {}

	std::ofstream m_OutputStream;
	std::ifstream m_InputStream;
	std::fstream m_TempStream;
};