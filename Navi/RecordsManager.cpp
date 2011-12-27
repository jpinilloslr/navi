#include "RecordsManager.h"


CRecordsManager::CRecordsManager(void)
{
	best = 0;
}


CRecordsManager::~CRecordsManager(void)
{
}

void CRecordsManager::WriteRecord(UINT time)
{
	FILE *fp;

	fp = fopen("data.bin", "wb");

	if(fp)
	{
		fwrite(&time, sizeof(time), 1, fp);
		fclose(fp);
	}

	best = time;
}

void CRecordsManager::LoadBest()
{
	FILE *fp;
	UINT time = 60;

	fp = fopen("data.bin", "rb");

	if(fp)
	{
		fread(&time, sizeof(time), 1, fp);
		fclose(fp);
	}

	best = time;
}