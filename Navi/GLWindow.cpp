#include "GLWindow.h"


CGLWindow::CGLWindow(void)
{
	gl = new CGL();
	bWindowed = true;
}


CGLWindow::~CGLWindow(void)
{
	delete System;
	delete FPSCounter;
	delete gl;
}

void CGLWindow::Start()
{
	gl->InitOpenGL(hWndMain, false, X_RESOLUTION, Y_RESOLUTION);
	gl->Light(GL_LIGHT0, 15.0f, 150.0f, -510.0f, false);
	gl->Light(GL_LIGHT1, 0.0f, -10.0f, 10.0f, false);
	glEnable(GL_LIGHTING);
	glDepthMask(1);
	glDisable(GL_BLEND);

	if (!OpenGLSupportsGLVersion(1, 0))
		MessageBoxA(NULL, "This system don't support OpenGL 1.0", "Error", MB_ICONWARNING);
	if (!OpenGLSupportsGLVersion(1, 1))
		MessageBoxA(NULL, "This system don't support OpenGL 1.1", "Error", MB_ICONWARNING);
	if (!OpenGLSupportsGLVersion(2, 0))
		MessageBoxA(NULL, "This system don't support OpenGL 2.0", "Error", MB_ICONWARNING);

	FPSCounter = new CFPSCounter();
	System = new CSystemManager();
	System->Start(!bWindowed, X_RESOLUTION, Y_RESOLUTION);
}

void CGLWindow::Destroy()
{
	gl->StopOpenGL();
	bFinished = true;
}

void CGLWindow::Draw()
{
	gl->StartSceneDraw();
	System->DrawGraphics();
	//FPSCounter->Draw();
	gl->StopSceneDraw();

	bFinished = System->Finished;
}

void CGLWindow::Resize()
{
	gl->Resize(hWndMain);
}

HWND CGLWindow::CreateGLWindow(HINSTANCE hInstance, WNDPROC lpfnWndProc)
{
	TCHAR szWindowClass[] = L"Kenai Pad";
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= lpfnWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(0));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_BTNFACE);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(0));

	RegisterClassEx(&wcex);
	ReadCommandLine();

	if(!bWindowed)
	{
		hWndMain = CreateWindowEx(WS_EX_APPWINDOW, szWindowClass, L"Kenai Pad", WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 10, 10, NULL, NULL, hInstance, 0);
	}
	else
	{
		hWndMain = CreateWindow(szWindowClass, L"Kenai Pad [benevixit7@gmail.com]", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		200, 300, 10, 10, NULL, NULL, hInstance, NULL);
	}

	bFinished = false;
	Start();
	ShowWindow(hWndMain, SW_SHOWNORMAL);

	return hWndMain;
}

void CGLWindow::TreatMessages()
{
	MSG msg;

	while(!bFinished)
	{
		if ( PeekMessageA(&msg, 0,0,0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{  
			Draw();
		}
	}
}

void CGLWindow::ReadCommandLine()
{
	if(NULL != strstr(GetCommandLineA(), " --windowed"))
	{
		bWindowed = true;
	}
}


void CGLWindow::ProcessMouseInput(int x, int y)
{
	System->ProcessMouseInput(x, y);
}

void CGLWindow::ProcessMouseOver(int x, int y)
{
	System->ProcessMouseOver(x, y);
}