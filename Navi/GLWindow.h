#ifndef CGLWindowH
#define CGLWindowH

#include <Windows.h>
#include "CGL.h"
#include "FPSCounter.h"
#include "SystemManager.h"

#define X_RESOLUTION 640
#define Y_RESOLUTION 480

class CGLWindow
{
	private:
		CGL *gl;
		CFPSCounter *FPSCounter;
		CSystemManager *System;

		bool bWindowed;
		bool bFinished;
		HWND hWndMain;

		void Start();
		void Draw();
		void ReadCommandLine();
	public:
		CGLWindow();
		~CGLWindow();

		void Resize();
		void Destroy();

		HWND CreateGLWindow(HINSTANCE hInstance, WNDPROC lpfnWndProc);
		void TreatMessages();
		HWND GetHandle()				{  return hWndMain;  }
		void RegisterFPSLoop()          {  FPSCounter->Loop();   }

		void ProcessMouseInput(int x, int y);
		void ProcessMouseOver(int x, int y);
};

#endif;