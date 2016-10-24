#pragma once

#include "resource.h"
#include "resource.h"
#include <windowsX.h>
#include <windows.h>
#include <winuser.h>
#include <commctrl.h>
#include <vector>
#include <fstream>
#include "Settings.h"
#include "Shape.h"

using namespace std;

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#define MAX_LOADSTRING 100
#define BUFFSIZE 260

void onCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
void onPaint(HWND hWnd);
void onDestroy(HWND hWnd);
BOOL onCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void onLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void onLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void onMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
void SaveData();
void LoadData();
void Clear(HWND hWnd);

int Shape, bX, bY, aX, aY;
bool mouseDown;
vector<CShape*> list;

//Global variables
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
PAINTSTRUCT ps;
HDC hdc;
HPEN hPen;

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
