#ifndef CGameTimerH
#define CGameTimerH

#include "glUtil\CFont.h";
#include "RecordsManager.h";

class CGameTimer
{
	private:
		CFont *font;
		CRecordsManager *Record;
		UINT nTick;
		UINT nLastTick;
		bool bTicking;

	public:
		CGameTimer(void);
		~CGameTimer(void);
		void Draw();
		void Tick()		{  if(bTicking) nLastTick = GetTickCount();  }
		void Start()	{  bTicking = true;	nTick = GetTickCount(); Record->LoadBest(); }
		void Stop()		{  bTicking = false;  }	
		void Reset()	{  nTick = 0;  }	
		void SetRecord();
		UINT GetTime()	{  nLastTick - nTick;  }
};

#endif