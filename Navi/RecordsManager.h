#ifndef CRecordsManagerH
#define CRecordsManagerH

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

class CRecordsManager
{
	private:
		UINT best;
	public:
		CRecordsManager(void);
		~CRecordsManager(void);
		void WriteRecord(UINT time);
		void LoadBest();
		UINT GetBest()	{  return best;  }
};

#endif