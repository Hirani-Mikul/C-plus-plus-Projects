#pragma once
#include <Windows.h>
#include <string>
#include <type_traits>
/*
	THIS CLASS IS PURELY FOR DEBUGGING PURPOSE

	IT IS THEREFORE, NOT A PART OF THE MAIN APPLICATION

*/
class Console
{
public:
	Console();
	~Console();

public:

	BOOL Create();

	// Write the content to the console. Text is white.
	BOOL Write(LPCSTR lpText);
	BOOL Write(LPCWSTR lpwText);

	// Write the "INFO" content to the console. Text is green.
	BOOL WriteInfo(LPCSTR lpInfo);

	// Write the "Error" content to the console. Text is red.
	BOOL WriteError(LPCSTR lpError);


	BOOL Write(LPCSTR lpText, int intVal);

	BOOL Write(LPCSTR lpText, LPCSTR lpText2);

	// Read content or user input from console
	//INT Read();

	// Clear the content of the console
	void Clear();


private:

	// Set the color of the text in the console. E.g. red for error.
	void setTextColor(int color);

private:

	// HANDLE to the "STD_INPUT_HANDLE".
	//HANDLE m_hSTDIn;

	// HANDLE to the "STD_OUTPUT_HANDLE".
	HANDLE m_hSTDOut;

	// Buffer to store the input from user. Maximum size 256.
	//CHAR m_ContentRead[256];
};

/*

template<typename T>
inline BOOL Console::Write(LPCSTR lpText, T arg2)
{
	// Check if the arg2 is type of integer or character array.

	std::string text = std::string(lpText);


	if (std::is_integral<T>::value && std::is_same<T, int>::value) // is it an integer value
	{
		// Concatenate lpText with arg2.
		// Convert the int to string
		text += std::to_string(arg2);
	}
	else if (std::is_pointer<T>::value) // is it pointer to character array.
	{
		if (std::is_same<T, const char*>::value)
			text += arg2;
	}

	BOOL bSuccess = Write(text.c_str());

	return bSuccess;
}

*/
/*
template<typename T>
inline BOOL Console::Write(LPCSTR lpText, T arg2)
{
	// Check if the arg2 is type of integer or character array.

	char* textBuffer = nullptr;

	if (std::is_integral<T>::value && std::is_same<T, int>::value) // is it an integer value
	{
		// Concatenate lpText with arg2.
		// Convert the int to string
		std::string intVal = std::to_string(arg2);
		size_t textLen = lstrlenA(lpText);

		// Allocate buffer size to store the text and integer value.
		textBuffer = new char[textLen + intVal.length() + 1];
		memcpy(textBuffer, lpText, textLen);
		memcpy(textBuffer + textLen, intVal.c_str(), intVal.length());
		textBuffer[textLen + intVal.length()] = 0;
	}
	else if (std::is_pointer<T>::value) // is it pointer to character array.
	{
		// Check if it is a character.
		//if (std::is_same<T, const char*>::value)
		//{
			// Concatenate lpText with arg2.

			size_t textLen = lstrlenA(lpText);
			size_t arg2Len = strlen(arg2);

			textBuffer = new char[textLen + arg2Len + 1];

			memcpy(textBuffer, lpText, textLen);
			memcpy(textBuffer + textLen, arg2, arg2Len);
			textBuffer[textLen + arg2Len] = 0;
		//}
	}

	BOOL bSuccess = Write(textBuffer);

	if (textBuffer != nullptr)
		delete[] textBuffer;

	return bSuccess;
}
*/

