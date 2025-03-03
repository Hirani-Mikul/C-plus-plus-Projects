#pragma once
#include <fstream>
#include <string>
#include <iostream>

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

	static void ReadFile(const char* filePath) { Get().I_ReadFile(filePath); }

	static void WriteFile(const char* filePath) { Get().I_WriteFile(filePath); }

public:

	void I_ReadFile( const char* filePath ) 
	{
		m_InputStream.open(filePath);

		std::string text;

		while (std::getline(m_InputStream, text))
		{

		}

		m_InputStream.close();
	}
	void I_WriteFile( const char* filePath ) 
	{
		m_OutputStream.open(filePath);

		m_OutputStream.close();
	}
private:
	FileStream() {}

	std::ifstream m_InputStream;
	std::ofstream m_OutputStream;
};