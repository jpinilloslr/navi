#include "CGL.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

void CGL::Light(int Light, float X,float Y, float Z, bool Positional)
{
    float position[] = {0.0f, 0.0f, 0.0f, 0.0f};
    position[0] = X;
    position[1] = Y;
    position[2] = Z;
    position[3] = Positional;

    float ambiente[] = {0.1f, 0.1f, 0.1f, 1.0f};
    float difusa[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float especular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat MatShine[] = {50.0f};

    glLightfv (Light, GL_POSITION, position);
    glLightfv (Light, GL_AMBIENT, ambiente);
    glLightfv (Light, GL_DIFFUSE, difusa);
    glLightfv (Light, GL_SPECULAR, especular);


    glEnable(Light);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShine);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}


CGL::CGL()
{
}



CGL::~CGL()
{
}



void CGL::InitOpenGL(HWND hWnd, bool bAntialiasing, int wndWidth, int wndHeight)
{
	PIXELFORMATDESCRIPTOR pfd;
	OSVERSIONINFO osvi = {0};
	int g_msaaSamples;
	int pf;

	dc = GetDC(hWnd);

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osvi);

	// When running under Windows Vista or later support desktop composition.
	if (osvi.dwMajorVersion > 6 || (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion >= 0))
	pfd.dwFlags |=  PFD_SUPPORT_COMPOSITION;

	if(bAntialiasing)
		ChooseBestMultiSampleAntiAliasingPixelFormat(pf, g_msaaSamples);
	else 
		pf = 0;

	if (!pf)
		pf = ChoosePixelFormat(dc, &pfd);

	SetPixelFormat(dc, pf, &pfd);

	(HGLRC)rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);

	SetWindowPos(hWnd, NULL, 0, 0, wndWidth, wndHeight, 0);

	glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_CULL_FACE);
	  
}



void CGL::Resize(HWND hWnd)
{
	DEVMODE dmScreenSettings;
	RECT WinRect, Screen;
    int Width, Height;
	int ScreenWidth, ScreenHeight;
    GetWindowRect(hWnd, &WinRect);

    Width = WinRect.right - WinRect.left;
    Height = WinRect.bottom - WinRect.top;

	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings);

	ScreenWidth = dmScreenSettings.dmPelsWidth;
	ScreenHeight = dmScreenSettings.dmPelsHeight;

	if(ScreenWidth == 0)
		ScreenWidth = 800;
	if(ScreenHeight == 0)
		ScreenHeight = 600;

    if (Height == 0) 
	{
        Height+=1;        
    }

	SetWindowPos(hWnd, NULL, (ScreenWidth/2)-(Width/2), (ScreenHeight/2)-(Height/2), Width, Height, 0);

    //redefine algunos valores segun el nuevo
    //tamaño de ventana
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, (GLfloat)Width/(GLfloat)Height, 0.1f, 5000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}



void CGL::StopOpenGL()
{
    wglMakeCurrent(0,0);
    wglDeleteContext(rc);
}


void CGL::StartSceneDraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}



void CGL::StopSceneDraw()
{
    glFlush();
    SwapBuffers(dc);
}



