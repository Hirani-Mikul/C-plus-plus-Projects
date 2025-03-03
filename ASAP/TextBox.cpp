#include "TextBox.h"

TextBox::TextBox()
{
	m_Edit = NULL;
}

BOOL TextBox::Write(LPCSTR lpString)
{
	if (m_Edit == NULL) return FALSE;

	AppendText(lpString);

	return TRUE;

}
BOOL TextBox::Write(LPCWSTR lpwText)
{
	if (m_Edit == NULL) return FALSE;

	AppendText(lpwText);

	return TRUE;
}

BOOL TextBox::Write(LPCWSTR lpwText, LPCWSTR lpwText2)
{
	if (m_Edit == NULL) return FALSE;
	AppendText(lpwText, lpwText2);
	return TRUE;
}

BOOL TextBox::Log(LPCWSTR lpwText)
{
	return Write(lpwText);
}

BOOL TextBox::Clear()
{
	SetWindowText(m_Edit, 0);
	SendMessage(m_Edit, WM_CLEAR, NULL, NULL);
	return 0;
}

BOOL TextBox::CreateEdit(HWND hWnd)
{
	RECT rect; // To store size of client area of window.

	GetClientRect(hWnd, &rect);

	// Create a TextBox to replicate the design of console application.
	// The TextBox is read-only 
	m_Edit = CreateWindow(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE | ES_READONLY | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, rect.right - rect.left - 150, rect.bottom - rect.top, hWnd, NULL, NULL, NULL);

	if (m_Edit == NULL) return FALSE;

	SendMessage(m_Edit, WM_SETFONT, (WPARAM)GetFont(), MAKELPARAM(TRUE, 0));

	return TRUE;
}

CHAR* TextBox::GetTextContent()
{

	size_t TextLength = GetWindowTextLength(m_Edit);

	CHAR* pszText = new CHAR[TextLength + 1];

	int BytesWritten = GetWindowTextA(m_Edit, pszText, TextLength + 1);

	if (BytesWritten != TextLength) return nullptr;

	return pszText;
}

const HWND TextBox::getEdit() const
{
	return m_Edit;
}

void TextBox::AppendText(LPCSTR pszText)
{
	int nLength = GetWindowTextLength(m_Edit) + 2;
	SendMessageA(m_Edit, EM_SETSEL, (WPARAM)nLength, (LPARAM)nLength);
	SendMessageA(m_Edit, EM_REPLACESEL, 0, (LPARAM)pszText);
	SendMessageA(m_Edit, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessageA(m_Edit, WM_VSCROLL, SB_BOTTOM, (LPARAM)NULL);
}

void TextBox::AppendText(LPCWSTR lpwText)
{
	int nLength = GetWindowTextLength(m_Edit) + 2;
	SendMessage(m_Edit, EM_SETSEL, (WPARAM)nLength, (LPARAM)nLength);
	SendMessage(m_Edit, EM_REPLACESEL, 0, (LPARAM)lpwText);
	SendMessage(m_Edit, EM_REPLACESEL, 0, (LPARAM)L"\r\n");
	//SendMessage(m_Edit, WM_VSCROLL, SB_BOTTOM, (LPARAM)NULL);
}
void TextBox::AppendText(LPCWSTR lpwText, LPCWSTR lpwText2)
{
	int nLength = GetWindowTextLength(m_Edit) + 2;
	SendMessage(m_Edit, EM_SETSEL, (WPARAM)nLength, (LPARAM)nLength);
	SendMessage(m_Edit, EM_REPLACESEL, 0, (LPARAM)lpwText);

	nLength = GetWindowTextLength(m_Edit) + 2;
	SendMessage(m_Edit, EM_SETSEL, (WPARAM)nLength, (LPARAM)nLength);
	SendMessage(m_Edit, EM_REPLACESEL, 0, (LPARAM)lpwText2);

	SendMessage(m_Edit, EM_REPLACESEL, 0, (LPARAM)L"\r\n");
}


HFONT TextBox::GetFont()
{
	return CreateFont(
		20, 0, 0, 0, 
		FW_DONTCARE, FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, 
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, 
		VARIABLE_PITCH, TEXT("Consolas")
	);

}
