#ifndef CGL_H
#define CGL_H

#include <windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <WGL_ARB_multisample.h>
#include <opengl.h>

class CGL
{
    private:
       HDC dc;
       HGLRC rc;	
	public:
	   CGL();
	   ~CGL();
	   void InitOpenGL(HWND hWnd, bool bAntialiasing, int wndWidth, int wndHeight);
	   void Resize(HWND hWnd);
	   void StopOpenGL();
	   void StartSceneDraw();
	   void StopSceneDraw();
	   void Light(int Light, float X,float Y, float Z, bool Positional);
	   
};

#endif