#pragma once
#include <Windows.h>
#include <tchar.h>

/* 
		EDIT CONTROL

The Read-Only edit control.
Painted it to replicate the appearance of console application.
It covers the entire client area of the window.
The Edit Control must truncate new content on the screen, unless cleared.

Only one instance of this class will exist from beginning to the end of the life of application.
*/


/*
	SECOND IDEA:
	HWND to Edit Control Box is held and owned by the main application class.
	This class only stores reference to it, and can send messages to write to the edit control.
*/
class TextBox
{
public:

	TextBox();

public:



	// Write content to edit box.
	// @param: control text to write to the edit control.
	BOOL Write( LPCSTR lpText);
	BOOL Write(LPCWSTR lpwText);
	BOOL Write(LPCWSTR lpwText, LPCWSTR lpwText2);
	BOOL Log(LPCWSTR);

	// Clear the content of edit box.
	BOOL Clear();

	// Creates a read-only edit control.
	// @param 1: HWND to the parent window.
	BOOL CreateEdit(HWND hWnd);

	// GET all the content of the edit control.
	CHAR* GetTextContent();

	CONST HWND getEdit() CONST;


private:
	void AppendText(LPCSTR pszText);
	void AppendText(LPCWSTR lpwText);
	void AppendText(LPCWSTR lpwText, LPCWSTR lpwText2);

	HFONT GetFont();

public:
	// TEMPORARY FOR DEBUGGING

	BOOL Write();
private:
	// HANDLE to Edit Box
	HWND m_Edit;

	// Buffer is needed to store the content of the edit box. 
	// Check if the EDIT-CONTROL has it's own buffer by default.
	
};

//void AppendWindowText(HWND hWnd, const char* lpString)
//{
//	int iLength = GetWindowTextLength(hWnd);
//	SendMessage(hWnd, EM_SETSEL, iLength, iLength);
//	SendMessage(hWnd, EM_REPLACESEL, 0, (LPARAM)lpString);
//	SendMessage(hWnd, WM_VSCROLL, SB_BOTTOM, (LPARAM)NULL);
//}