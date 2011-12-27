#include "GameTimer.h"


CGameTimer::CGameTimer(void)
{
	font = new CFont();
	font->LoadTexture("system\\screen\\font2.jpg");
	font->Size = 1.5f;

	Record = new CRecordsManager();

	nTick = 0;
	nLastTick = 0;
	bTicking = false;
}


CGameTimer::~CGameTimer(void)
{
	delete font;
	delete Record;
}

void CGameTimer::Draw()
{
	int seconds;
	int minutes;
	char szTime[100];
	
	seconds = (nLastTick - nTick)/1000;
	minutes = seconds / 60;
	seconds = seconds % 60;

	if(seconds < 10)
		sprintf(szTime, "%d:0%d", minutes, seconds);
	else
		sprintf(szTime, "%d:%d", minutes, seconds);

	font->DrawText(szTime, -0.08f, 0.05f);

	seconds = Record->GetBest();
	minutes = seconds / 60;
	seconds = seconds % 60;

	if(seconds < 10)
		sprintf(szTime, "%d:0%d", minutes, seconds);
	else
		sprintf(szTime, "%d:%d", minutes, seconds);

	font->Size = 1.0f;
	font->DrawText(szTime, -0.08f, 0.045f);
	font->Size = 1.5f;

	Tick();
}

void CGameTimer::SetRecord()
{
	if(Record->GetBest() > ((nLastTick - nTick)/1000))
	{
		Record->WriteRecord((nLastTick - nTick)/1000);
	}
}