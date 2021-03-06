// MyPaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MyPaint.h"

#define MAX_LOADSTRING 100



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYPAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYPAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYPAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, onCreate);
		HANDLE_MSG(hWnd, WM_PAINT, onPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, onDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, onCommand);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, onLButtonDown);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, onMouseMove);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, onLButtonUp);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void onPaint(HWND hWnd)
{
	hdc = BeginPaint(hWnd, &ps);
	hPen = CreatePen(PS_SOLID, 3, RGB(110, 0, 110));
	SelectObject(hdc, hPen);
	// TODO: Add any drawing code here...
	
	for (int i = 0; i < list.size(); i++)
	{
		list[i]->Paint(hdc);
	}
	
	if (true == mouseDown)
	{
		switch(Shape)
		{
		case 0:
		{	
			MoveToEx(hdc, bX, bY, NULL);
			LineTo(hdc, aX, aY);
			break;
		}

		case 1:
		{
			Rectangle(hdc, bX, bY, aX, aY);
			break;
		}

		case 2:
		{
			Ellipse(hdc, bX, bY, aX, aY);
			break;
		}

		}
	}
	EndPaint(hWnd, &ps);
}

void onDestroy(HWND hWnd)
{
	SaveData();
	SaveRect(hWnd);
	PostQuitMessage(0);
}

BOOL onCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	mouseDown = false;
	LoadRect(hWnd);
	LoadData();
	
	return true;
}

void onCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;

	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;

	case IDM_CLEAR:
		Clear(hWnd);
		break;
	
	case IDM_LINE:
		Shape = 0;
		break;

	case IDM_RECTANGLE:
		Shape = 1;
		break;

	case IDM_ELLIPSE:
		Shape = 2;
		break;
	}
}

void onLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	mouseDown = true;
	bX = x;
	bY = y;
}

void onLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	mouseDown = false;
	aX = x;
	aY = y;
	CShape *shape;
	switch (Shape)
	{
	case 0:
		shape = new CLine(bX, bY, aX, aY);
		break;

	case 1:
		shape = new CRectangle(bX, bY, aX, aY);
		break;

	case 2:
		shape = new CEllipse(bX, bY, aX, aY);
		break;
	}

	list.push_back(shape);
	InvalidateRect(hwnd, NULL, TRUE);
}

void onMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (false == mouseDown)
		return;
	aX = x;
	aY = y;
	InvalidateRect(hwnd, NULL, TRUE);
}

void SaveData()
{
	fstream fi;
	fi.open("data.bin", ios::binary | ios::out);
	if (!fi)
	{
		MessageBox(0, 0, 0, 0);
		return;
	}
	fi << list.size() << "\n";
	for (int i = 0; i < list.size(); i++)
	{
		list[i]->Save(fi);
	}
	fi.close();
}

void LoadData()
{
	fstream fo;
	fo.open("data.bin", ios::binary | ios::in);
	if (!fo)
		return;
	int n;
	fo >> n;
	for (int i = 0; i < n; i++)
	{
		int shape, x1, x2, y1, y2;
		CShape *temp;
		fo >> shape >> x1 >> y1 >> x2  >> y2;
		switch (shape)
		{
		case 0:
			temp = new CLine(x1, y1, x2, y2);
			break;

		case 1:
			temp = new CRectangle(x1, y1, x2, y2);
			break;

		case 2:
			temp = new CEllipse(x1, y1, x2, y2);
			break;
		}
		list.push_back(temp);
	}
	fo.close();
}

void Clear(HWND hWnd)
{
	list.clear();
	InvalidateRect(hWnd, NULL, TRUE);
}