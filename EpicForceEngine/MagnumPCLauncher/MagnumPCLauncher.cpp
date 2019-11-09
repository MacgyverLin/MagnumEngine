///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MagnumPCLauncher.h"
#include "anyoption.h"
#include "gldef.h"
#ifdef USE_GLES20
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#else
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "Opengl32.lib")
#endif

#define MAX_LOADSTRING 100
#define ID_INPUT_TRAP_TIMER 1
// Global Variables:
HINSTANCE hInst;								// current instance
HWND hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int, int, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "GameDescriptor.h"
#include "InputData.h"
#include "EGLDriver20.h"
using namespace Magnum;

GameDescriptor		gameDesc;

EGLDriver20			*eglDriver = 0;

bool lButtonDown = false, mButtonDown = false, rButtonDown = false;
float accX = 0.0f, accY = 0.0f, accZ = 0.0f;
bool isPaused = false;
bool done = false;

HWND lastFocusedHWND = NULL;
HWND focusedHWND	 = NULL;

InputData inputData;

//////////////////////////////////////////////////////////////////////////////////////
int keyCodes[] =
{
	VK_F9, VK_F10, VK_F11, VK_F12,		// KEY_HOME,		KEY_BACK,		KEY_MENU,		KEY_SEARCH,
	VK_F1,  VK_F2,  VK_F3,  VK_F4,		// KEY_SPECIAL0,	KEY_SPECIAL1,	KEY_SPECIAL2,	KEY_SPECIAL3,
	VK_F5,  VK_F6,  VK_F7,  VK_F8,		// KEY_SPECIAL4,	KEY_SPECIAL5,	KEY_SPECIAL6,	KEY_SPECIAL7,
	'W', 'S', 'A', 'D',					// KEYPAD0_UP,		KEYPAD0_DOWN,	KEYPAD0_LEFT,	KEYPAD0_RIGHT,
	'F', 'G',							// KEYPAD0_SELECT,	KEYPAD0_START,
	'J', 'M', 'K', ',',					// KEYPAD0_BUTTON0,	KEYPAD0_BUTTON1,KEYPAD0_BUTTON2,KEYPAD0_BUTTON3,
	'H', 'N', 'Y',						// KEYPAD0_L1,		KEYPAD0_L2,		KEYPAD0_L3,
	'.', 'L', 'O',						// KEYPAD0_R1,		KEYPAD0_R2,		KEYPAD0_R2,
};

int lastKeyStatus[] =
{
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 
	0, 0, 0, 0,
	0, 0, 0, 
	0, 0, 0, 
};

void updateKeyBoard()
{
	for(int i=0; i<sizeof(keyCodes)/sizeof(keyCodes[0]); i++)
	{
		int keyStatus = ::GetAsyncKeyState(keyCodes[i]);
		if( (keyStatus & 0x8000) ^ (lastKeyStatus[i] & 0x8000) )
		{
			if(keyStatus & 0x8000)
			{
				inputData.addKeyDown(i);
				//::OutputDebugString("inputData.addKeyDown\n");
			}
			else
			{
				inputData.addKeyUp(i);
				//::OutputDebugString("inputData.addKeyUp\n");
			}
		}
		lastKeyStatus[i] = keyStatus;
	}
}

//////////////////////////////////////////////////////////////////////////////////////
unsigned int lastJoypadButtonStatus[16] =
{
	0x00000000,	0x00000000,	0x00000000,	0x00000000,
	0x00000000,	0x00000000,	0x00000000,	0x00000000,
	0x00000000,	0x00000000,	0x00000000,	0x00000000,
	0x00000000,	0x00000000,	0x00000000,	0x00000000,
};

void updateJoyPad()
{
	int numJoypads = joyGetNumDevs();
	for(int i=0; i<numJoypads && i<16; i++)
	{
		JOYINFOEX joyInfoEx;
		memset(&joyInfoEx, 0, sizeof(joyInfoEx));
		joyInfoEx.dwSize = sizeof(JOYINFOEX);
		joyInfoEx.dwFlags = JOY_RETURNALL;

		MMRESULT result = joyGetPosEx(i, &joyInfoEx);
		if(result==JOYERR_NOERROR)
		{
			int x = joyInfoEx.dwXpos;
			int y = joyInfoEx.dwYpos;
			int z = joyInfoEx.dwZpos;
			unsigned int joypadButtonStatus = joyInfoEx.dwButtons;
			unsigned int joypadButtonDelta = joypadButtonStatus ^ lastJoypadButtonStatus[i];

			for(int j=0; j<32; j++)
			{
				unsigned int bit = (1<<j);
				if(joypadButtonDelta & bit)
				{
					if(joypadButtonStatus & bit)
					{
						inputData.addKeyDown(j);
						//debug("Key %d down", j);
					}
					else
					{
						inputData.addKeyUp(j);
						//debug("Key %d up", j);
					}
				}
			}

			lastJoypadButtonStatus[i] = joypadButtonStatus;

			//char buffer[1024];
			//sprintf(buffer, "%d %d %d %d, %08x\n", i, x, y, z, joypadButtonStatus);
			//::OutputDebugString(buffer);
		}
		else
		{
			//char buffer[1024];
			//sprintf(buffer, "joypad error\n");
			//::OutputDebugString(buffer);

			lastJoypadButtonStatus[i] = 0;
		}
	}
}

long long getCurrentTimeMSFunc_()
{
	return timeGetTime();
	return GetTickCount();
}

void infoPrintFunc(const char *buf_)
{
	OutputDebugStringA("Info : ");
	OutputDebugStringA(buf_);
	OutputDebugStringA("\n");
}

void debugPrintFunc(int i, const char *buf_)
{
	OutputDebugStringA("Debug : ");
	OutputDebugStringA(buf_);
	OutputDebugStringA("\n");
}

void panicPrintFunc(const char *buf_)
{
	OutputDebugStringA("Panic : ");
	OutputDebugStringA(buf_);
	OutputDebugStringA("\n");
	
	exit(-1);
}

const char *initialScene = "PlayMode";
int width				 = 960;
int height				 = 640;

//////////////////////////////////////////////////////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// TODO: Place code here.
	MSG msg;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MAGNUMPCLAUNCHER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	//////////////////////////////////////////////////////
	// initialize Game Entry Point
	if(!gameDesc.create("game.dll"))
		return FALSE;

	//////////////////////////////////////////////////////
	// initialize Launcher Entry Point

	/////////////////////////////////////////////////////
	// initialize Apps
	if( !InitInstance(hInstance, width, height, nCmdShow) )
		return FALSE;

	/////////////////////////////////////////////////////
	// initialize Video
	eglDriver = new EGLDriver20();
	eglDriver->Init(hWnd);
	if(!eglDriver)
		return FALSE;

	/////////////////////////////////////////////////////
	// initialize Engine
	gameDesc.setRawAssetRootDirectory("../rawAssets/");
	gameDesc.setAssetRootDirectory("../device/application/bundle/");
	gameDesc.setDocumentDirectory("../device/application/document/");
	gameDesc.setExternalDirectory("../device/external/");
	gameDesc.setGetCurrentTimeMSFunc(getCurrentTimeMSFunc_);
	gameDesc.setPrintFunc(infoPrintFunc, debugPrintFunc, panicPrintFunc);
	gameDesc.setInitialScene("PlayMode");

	if( !gameDesc.onInitialize(width, height) )
		return FALSE;

	/////////////////////////////////////////////////////
	// Engine loop
	do
	{
		// is there a message to process?
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) )
		{
			// dispatch the message
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else 
		{
			if(!isPaused)
			{
				updateKeyBoard();
				//updateJoyPad();

				for(int i=0; i<inputData.mouseDownCnt; i++)
					gameDesc.onMouseDown(inputData.mouseDownModifier[i], inputData.mouseDownID[i], inputData.mouseDownX[i], inputData.mouseDownY[i]);
				inputData.mouseDownCnt	= 0;
	
				for(int i=0; i<inputData.mouseMoveCnt; i++)
					gameDesc.onMouseMoved(inputData.mouseDownModifier[i], inputData.mouseDownID[i], inputData.mouseMoveX[i], inputData.mouseMoveY[i]);
				inputData.mouseMoveCnt	= 0;
	
				for(int i=0; i<inputData.mouseUpCnt; i++)
					gameDesc.onMouseUp(inputData.mouseDownModifier[i], inputData.mouseDownID[i], inputData.mouseUpX[i], inputData.mouseUpY[i]);
				inputData.mouseUpCnt	= 0;

				for(int i=0; i<inputData.wheelCnt; i++)
					gameDesc.onMouseWheel(inputData.wheelModifier[i], inputData.wheelX[i], inputData.wheelY[i], inputData.wheelAxis[i], inputData.wheelRotation[i]);
				inputData.wheelCnt	= 0;

				for(int i=0; i<inputData.keyDownCount; i++)
					gameDesc.onGamePadKeyDown(inputData.keyDownCode[i]);
				inputData.keyDownCount	= 0;

				for(int i=0; i<inputData.keyUpCount; i++)
					gameDesc.onGamePadKeyUp(inputData.keyUpCode[i]);
				inputData.keyUpCount	= 0;

				if(inputData.hasAcc)
					gameDesc.onAccelerationUpdate(inputData.accX, inputData.accY, inputData.accZ);
				inputData.hasAcc = false;

				gameDesc.onProcess();

				if(eglDriver)
					eglDriver->SwapBuffers();
			}
		}
	}while(!done);

	/////////////////////////////////////////////////////
	// terminate Engine
	gameDesc.onTerminate();

	/////////////////////////////////////////////////////
	// terminate Video
	if(eglDriver)
	{
		eglDriver->Terminate();

		delete eglDriver;
		eglDriver = 0;
	}

	//////////////////////////////////////////////////////
	// terminate Launcher Entry Point

	/////////////////////////////////////////////////////
	// terminate entry point
	gameDesc.destroy();

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MAGNUMPCLAUNCHER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
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
BOOL InitInstance(HINSTANCE hInstance, int width, int height, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 
		width, height, 
		NULL, NULL, 
		hInstance, 
		NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	SetTimer(hWnd, ID_INPUT_TRAP_TIMER, 16, 0);

	eglDriver = new EGLDriver20();
	eglDriver->Init(hWnd);
	if(!eglDriver)
		return FALSE;

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
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_COMMAND:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_KEYDOWN:
		{
			if(wParam==VK_PAUSE)
			{
				if(isPaused)
				{
					gameDesc.onResume();
					isPaused = false;
				}
				else
				{
					gameDesc.onPause();
					isPaused = true;
				}					
			}

			if(wParam==VK_ESCAPE)
			{
				done = true;
			}
		}
		break;

		case WM_KEYUP:
		{
		}
		break;

		case WM_MOUSEMOVE:
		{
			int x= LOWORD(lParam);
			int y= HIWORD(lParam);

			if(lButtonDown)
			{
				inputData.addMouseMove(0, 0, (float)x, (float) y);
			}
			if(mButtonDown)
			{
				inputData.addMouseMove(0, 1, (float)x, (float) y);
			}
			if(rButtonDown)
			{
				gameDesc.onMouseMoved(0, 2, (float)x, (float) y);
			}
		}
		break;

		case WM_LBUTTONDOWN:
		{
			lButtonDown = true;
			int x= LOWORD(lParam);
			int y= HIWORD(lParam);

			inputData.addMouseDown(0, 0, (float)x, (float) y);
		}
		break;

		case WM_LBUTTONUP:
		{
			lButtonDown = false;
			int x= LOWORD(lParam);
			int y= HIWORD(lParam);
			
			inputData.addMouseUp(0, 0, (float)x, (float) y);
		}
		break;

		case WM_MBUTTONDOWN:
		{
			mButtonDown = true;
			int x= LOWORD(lParam);
			int y= HIWORD(lParam);
			inputData.addMouseDown(0, 1, (float)x, (float) y);
		}
		break;

		case WM_MBUTTONUP:
		{
			mButtonDown = false;
			int x= LOWORD(lParam);
			int y= HIWORD(lParam);
			inputData.addMouseUp(0, 1, (float)x, (float) y);
		}
		break;

		case WM_RBUTTONDOWN:
		{
			rButtonDown = true;
			int x= LOWORD(lParam);
			int y= HIWORD(lParam);

			inputData.addMouseDown(0, 2, (float)x, (float) y);
		}
		break;

		case WM_RBUTTONUP:
		{
			rButtonDown = false;
			int x= LOWORD(lParam);
			int y= HIWORD(lParam);
			
			inputData.addMouseUp(0, 2, (float)x, (float) y);
		}
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_TIMER:
		{
			if(wParam==ID_INPUT_TRAP_TIMER) 
			{ 
				focusedHWND = GetFocus();
				if(lastFocusedHWND!=focusedHWND ) // detect refocus condition
				{
					if(focusedHWND == hWnd)
					{
						// gameDesc.onCustomEvent("UpdateRawResource", "");
						// isPaused = false;
					}
					else
					{
						// isPaused = true;
					}
				}
				lastFocusedHWND = focusedHWND;
			}

			SetTimer(hWnd, ID_INPUT_TRAP_TIMER, 16, 0);
		}
		return 0;

		case WM_DESTROY:
		{
			done = true;
			KillTimer(hWnd, ID_INPUT_TRAP_TIMER);
			PostQuitMessage(0);
		}
		break;
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	// UNREFERENCED_PARAMETER(lParam);
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
