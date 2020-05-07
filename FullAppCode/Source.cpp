#ifdef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include "FileEnDe.h"


#define FILE_EXIT 1
#define ENCRYPT_BUTTON 2
#define DECRYPT_BUTTON 3

LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void addMenus(HWND);
void addControls(HWND);

HMENU hMenu;
HWND hTxtFileName, hTxtFileOut;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpszClassName = L"ourWindowEncryptor";
	wc.lpfnWndProc = windowProc;

	RegisterClass(&wc);
	

	CreateWindow(L"ourWindowEncryptor", L"MyWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

	MSG msg{ 0 };

	while ( GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_COMMAND:
		switch (wParam)
		{
		case FILE_EXIT:
			PostQuitMessage(0);
			return 0;

		case ENCRYPT_BUTTON:
		{
			char txtFileName[30], outputBox[500];
			GetWindowTextA(hTxtFileName, txtFileName, 30);
			fileEncryption(txtFileName);
			std::string fileContent = outputFileContents(txtFileName);

			strncpy_s(outputBox, fileContent.c_str(), sizeof(outputBox));
			outputBox[sizeof(outputBox) - 1] = 0;

			SetWindowTextA(hTxtFileOut, outputBox);
			return 0;
		}
		case DECRYPT_BUTTON:
		
				char txtFileName[30], outputBox[500];
				GetWindowTextA(hTxtFileName, txtFileName, 30);
				fileDecryption(txtFileName);
				std::string fileContent = outputFileContents(txtFileName);
				strncpy_s(outputBox, fileContent.c_str(), sizeof(outputBox));
				outputBox[sizeof(outputBox) - 1] = 0;
				SetWindowTextA(hTxtFileOut, outputBox);
			return 0;
		
		}

		return 0;

	case WM_CREATE:
		addMenus(hwnd);
		addControls(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	
	}
}

void addMenus(HWND hwnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();

	AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenuA(hFileMenu, MF_STRING, FILE_EXIT, "Exit");
	
	SetMenu(hwnd, hMenu);
}

void addControls(HWND hWnd)
{
	CreateWindow(L"static", L"File Name(.txt format):", WS_VISIBLE | WS_CHILD, 50, 100, 200, 30, hWnd, NULL, NULL, NULL);
	hTxtFileName = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOHSCROLL | WS_BORDER, 203, 100, 150, 20, hWnd, NULL, NULL, NULL);

	CreateWindow(L"button", L"Encrypt", WS_VISIBLE | WS_CHILD, 200, 125, 55, 20, hWnd, (HMENU)ENCRYPT_BUTTON, NULL, NULL);
	CreateWindow(L"button", L"Decrypt", WS_VISIBLE | WS_CHILD, 260, 125, 55, 20, hWnd, (HMENU)DECRYPT_BUTTON, NULL, NULL);

	hTxtFileOut = CreateWindow(L"edit", L"Text contents will display here:", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE |WS_BORDER, 50, 175, 350, 100, hWnd, NULL, NULL, NULL);
}
