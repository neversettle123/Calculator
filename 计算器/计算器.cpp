// 计算器.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "计算器.h"
#include<math.h>
#include<vector>
#include"Calculator.h"

using namespace std;

struct 
{
	int style;
	TCHAR * szText;
}
Button[]=
{
	BS_PUSHBUTTON, TEXT("MC"),BS_PUSHBUTTON, TEXT("MR"),
	BS_PUSHBUTTON, TEXT("MS"),BS_PUSHBUTTON, TEXT("M+"),
	BS_PUSHBUTTON, TEXT("M-"),BS_PUSHBUTTON, TEXT("<--"),
	BS_PUSHBUTTON, TEXT("CE"),BS_PUSHBUTTON, TEXT("C"),
	BS_PUSHBUTTON, TEXT("±"),BS_PUSHBUTTON, TEXT("√"),
	BS_PUSHBUTTON, TEXT("7"),BS_PUSHBUTTON, TEXT("8"),
	BS_PUSHBUTTON, TEXT("9"),BS_PUSHBUTTON, TEXT("/"),
	BS_PUSHBUTTON, TEXT("%"),BS_PUSHBUTTON, TEXT("4"),
	BS_PUSHBUTTON, TEXT("5"),BS_PUSHBUTTON, TEXT("6"),
	BS_PUSHBUTTON, TEXT("*"),BS_PUSHBUTTON, TEXT("1/x"),
	BS_PUSHBUTTON, TEXT("1"),BS_PUSHBUTTON, TEXT("2"),
	BS_PUSHBUTTON, TEXT("3"),BS_PUSHBUTTON, TEXT("-"),
	BS_PUSHBUTTON, TEXT("="),BS_PUSHBUTTON, TEXT("0"),
	BS_PUSHBUTTON, TEXT("."),BS_PUSHBUTTON, TEXT("+")
};

#define ID_STATIC 100
Calculator Num;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlg(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	               PSTR szCmdLine, int iCmdShow)
{
	MSG msg;
	HWND hWnd;
	HACCEL hAccel;
	WNDCLASS wndclass;	
	static TCHAR szAppName[] = TEXT("计算器");

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDC_MY);
	

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hWnd = CreateWindow(szAppName, TEXT("计算器"),
		WS_OVERLAPPED|WS_SYSMENU| WS_MINIMIZEBOX | WS_BORDER,
		800, 300, 250, 320,
		NULL, NULL, hInstance, NULL); 

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HFONT hfont;
	HDC hdc;	
	RECT rect;
	PAINTSTRUCT ps;

	static HINSTANCE hInst;
	static HWND hStatic;
	static int cxChar, cyChar,
		cxClient, cyClient;
	static HWND hButton[28];
	int i = 0, x, y;	
	
	switch (message)
	{
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		hStatic = CreateWindow(TEXT("static"), TEXT("0"),
			WS_CHILD | WS_VISIBLE | WS_BORDER|SS_SUNKEN|SS_RIGHT,
			0, 0, 0, 0, hWnd, (HMENU)ID_STATIC, hInst, NULL);	
		Num.GethWnd(hStatic);    //获取句柄
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		
		MoveWindow(hStatic, 20, 20, cxClient - 20 * 2, 50, TRUE);
		ShowWindow(hStatic, SW_NORMAL);
		UpdateWindow(hStatic);
				
		for (y = 0; y < 6; y++)
		{
			for (x = 0; x < 5; x++)
			{
				if (i < 28)
				{
					hButton[i] = CreateWindow(TEXT("button"), Button[i].szText,
						WS_VISIBLE | WS_CHILD | Button[i].style,
						20 + x * 10 + x*(cxClient - 80) / 5,
						80 + y * 10 + y*(cyClient - 150) / 6,
						(cxClient - 80) / 5, (cyClient - 150) / 6,
						hWnd, (HMENU)(i+1), hInst, NULL);
					i++;
				}
			}
		}
		break;
				
	case WM_SETFOCUS:
		SetFocus(hWnd);
		break;

	case WM_CHAR:
		Num.CharMsg((char)wParam);		
		break;
		
	case WM_COMMAND: 		
		Num.BtnMsg(LOWORD(wParam));           //按钮消息
		
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutDlg);
			break;
		}
		SetFocus(hWnd);
		return 0;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


BOOL CALLBACK AboutDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
















