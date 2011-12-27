#include "PerformanceController.h"


CPerformanceController::CPerformanceController()
{
}


CPerformanceController::~CPerformanceController()
{
}

void CPerformanceController::EnableVerticalSync(bool enableVerticalSync)
{
    // WGL_EXT_swap_control.

    typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC)(GLint);

    static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
        reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(
        wglGetProcAddress("wglSwapIntervalEXT"));

    if (wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(enableVerticalSync ? 1 : 0);
    }
}

void CPerformanceController::SetProcessorAffinity()
{
    // Asigna el hilo actual a un procesador. Esto asegura que el
    // codigo corra en un solo procesador, y no sufrira los efectos indeseados
    // del tratamiento de energia.

    DWORD_PTR dwProcessAffinityMask = 0;
    DWORD_PTR dwSystemAffinityMask = 0;
    HANDLE hCurrentProcess = GetCurrentProcess();

    if (!GetProcessAffinityMask(hCurrentProcess, &dwProcessAffinityMask, &dwSystemAffinityMask))
        return;

    if (dwProcessAffinityMask)
    {
        // Busca el procesador más bajo en el que nuestro proceso puede correr

        DWORD_PTR dwAffinityMask = (dwProcessAffinityMask & ((~dwProcessAffinityMask) + 1));

        // Define este como el procesador que nuestro proceso siempre debe usar.
        // Debe ser un subconjunto de la mascara de afinidad de los procesadores.

        HANDLE hCurrentThread = GetCurrentThread();

        if (hCurrentThread != INVALID_HANDLE_VALUE)
        {
            SetThreadAffinityMask(hCurrentThread, dwAffinityMask);
            CloseHandle(hCurrentThread);
        }
    }

    CloseHandle(hCurrentProcess);
}

void CPerformanceController::SwitchToFullScreen(int width, int height, int bits)
{
	DEVMODE dmScreenSettings;
	memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);
	dmScreenSettings.dmPelsWidth  = width;
	dmScreenSettings.dmPelsHeight = height;
	dmScreenSettings.dmBitsPerPel = bits;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	ShowCursor(FALSE);
}
