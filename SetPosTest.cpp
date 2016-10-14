// SetPosTest.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <sstream>

#include "resource.h"

// Global Variables:
HINSTANCE hInst;
const TCHAR szTitle[] = _T("SetPosTest");
const TCHAR szWindowClass[] = _T("SetPosTestClass");

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SETPOSTEST));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SETPOSTEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SETPOSTEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 400, 200, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		HFONT hf = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		HWND btns[] = {
		CreateWindow(_T("BUTTON"), _T("LeftTop (F5)"), WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON, 0,0,0,0,hWnd, (HMENU)ID_POSITION_LEFTTOP, NULL, 0),
		CreateWindow(_T("BUTTON"), _T("LeftBottom (F6)"), WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON, 0,0,0,0,hWnd, (HMENU)ID_POSITION_LEFTBOTTOM, NULL, 0),
		CreateWindow(_T("BUTTON"), _T("RightTop (F7)"), WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON, 0,0,0,0,hWnd, (HMENU)ID_POSITION_RIGHTTOP, NULL, 0),
		CreateWindow(_T("BUTTON"), _T("RightBottom (F8)"), WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON, 0,0,0,0,hWnd, (HMENU)ID_POSITION_RIGHTBOTTOM, NULL, 0)
		};
		for (size_t i = 0; i < ARRAYSIZE(btns); i++)
			SendMessage(btns[i], WM_SETFONT, (WPARAM)hf, FALSE);
		WndProc(hWnd, WM_SIZE, 0,0);
		WndProc(hWnd, WM_MOVE, 0,0);
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_SIZE:
	{
		RECT rc = {};
		const double margin_x = 0.05;
		const double margin_y = 0.05;
		const double btn_w = 0.35;
		const double btn_h = 0.25;
		GetClientRect(hWnd, &rc);
		#pragma warning(disable: 4244)
		MoveWindow(GetDlgItem(hWnd, ID_POSITION_LEFTTOP), margin_x*rc.right, margin_y*rc.bottom, btn_w*rc.right, btn_h*rc.bottom, TRUE);
		MoveWindow(GetDlgItem(hWnd, ID_POSITION_LEFTBOTTOM), margin_x*rc.right, (1-margin_y-btn_h)*rc.bottom, btn_w*rc.right, btn_h*rc.bottom, TRUE);
		MoveWindow(GetDlgItem(hWnd, ID_POSITION_RIGHTTOP), (1-margin_x-btn_w)*rc.right, margin_y*rc.bottom, btn_w*rc.right, btn_h*rc.bottom, TRUE);
		MoveWindow(GetDlgItem(hWnd, ID_POSITION_RIGHTBOTTOM), (1-margin_x-btn_w)*rc.right, (1-margin_y-btn_h)*rc.bottom, btn_w*rc.right, btn_h*rc.bottom, TRUE);
		break;
	}
	case WM_MOVE:
	{
		RECT rc = {};
		std::wstringstream text;
		GetWindowRect(hWnd, &rc);
		text << szTitle << L" - {" << rc.left << L"," << rc.top << L"}-{" << rc.right << L"," << rc.bottom << L"}";
		SetWindowTextW(hWnd, text.str().c_str());
		break;
	}
	case WM_COMMAND:
	{
		int wmId    = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_POSITION_LEFTTOP:
		case ID_POSITION_LEFTBOTTOM:
		case ID_POSITION_RIGHTTOP:
		case ID_POSITION_RIGHTBOTTOM:
		{
			HMONITOR hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi = {sizeof(mi)}; GetMonitorInfo(hmon, &mi);
			RECT rc = {}; GetWindowRect(hWnd, &rc);
			switch (wmId)
			{
			case ID_POSITION_LEFTTOP:
				SetWindowPos(hWnd, NULL, mi.rcWork.left, mi.rcWork.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE); break;
			case ID_POSITION_LEFTBOTTOM:
				SetWindowPos(hWnd, NULL, mi.rcWork.left, mi.rcWork.bottom-(rc.bottom-rc.top), 0, 0, SWP_NOZORDER|SWP_NOSIZE); break;
			case ID_POSITION_RIGHTTOP:
				SetWindowPos(hWnd, NULL, mi.rcWork.right-(rc.right-rc.left), mi.rcWork.top, 0, 0, SWP_NOZORDER|SWP_NOSIZE); break;
			case ID_POSITION_RIGHTBOTTOM:
				SetWindowPos(hWnd, NULL, mi.rcWork.right-(rc.right-rc.left), mi.rcWork.bottom-(rc.bottom-rc.top), 0, 0, SWP_NOZORDER|SWP_NOSIZE); break;
			}
			break;
		}
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
