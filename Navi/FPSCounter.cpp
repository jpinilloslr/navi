#include "FPSCounter.h"


CFPSCounter::CFPSCounter()
{
	fps = 0;
	counter = 0;

	Font = new CFont();
	char szFileName[MAX_PATH];

	GetCurrentDirectoryA(MAX_PATH, szFileName);
	strcat_s(szFileName, MAX_PATH, "\\SYSTEM\\SCREEN\\font.jpg");

	Font->Size = 0.8f;
	Font->LoadTexture(szFileName);
}


CFPSCounter::~CFPSCounter()
{
	delete Font;
}

void CFPSCounter::Draw()
{
	char szText[225];
	sprintf_s(szText, "FPS:%d", fps);
	Font->DrawText(szText, -0.08f, 0.055f);
	counter++;
}

void CFPSCounter::Loop()
{
	fps = counter-1;
	counter = 0;
}