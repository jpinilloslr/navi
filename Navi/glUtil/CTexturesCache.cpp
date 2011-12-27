#include "CTexturesCache.h"

CTexturesCache::CTexturesCache()
{
	for(int i = 0; i < MAX_CACHE; i++)
	{
		memset(szName[i], 0, 50);
		nTexture[i] = 0;
	}

	nLastTexture = 0;
}

CTexturesCache::~CTexturesCache()
{
}

UINT CTexturesCache::IsCache(char *szfilename)
{
	int n = 0;
	bool bFound = false;

	while((n <= nLastTexture) && (!bFound))
	{
		if(nLastTexture > MAX_CACHE)
			nLastTexture = 0;

		if(strcmp(szfilename, szName[n]) == 0)
		{
			bFound = true;
		}
		else
			n++;
	}

	if(bFound)
		return nTexture[n];
	else
		return 0;
}

void CTexturesCache::Insert(char *szfilename, UINT nTex)
{
	nLastTexture++;

	if(nLastTexture > MAX_CACHE)
		nLastTexture = 0;

	strncpy_s(szName[nLastTexture], szfilename, 50);
	nTexture[nLastTexture] = nTex;
}