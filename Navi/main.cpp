#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <WindowsX.h>
#include "GLWindow.h"

CGLWindow *glWindow;

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)          
{
	glWindow->RegisterFPSLoop();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_SIZE:
			glWindow->Resize();
			return 0;

		case WM_LBUTTONDOWN:
			glWindow->ProcessMouseInput(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;

		case WM_MOUSEMOVE:
			glWindow->ProcessMouseOver(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;

		case WM_DESTROY:
			glWindow->Destroy();
			return 0;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	glWindow = new CGLWindow();
	
	glWindow->CreateGLWindow(hInstance, WndProc);
	SetTimer(glWindow->GetHandle(), 1, 1000, TimerProc);
	glWindow->TreatMessages();

	delete glWindow;
	return 0;
}
