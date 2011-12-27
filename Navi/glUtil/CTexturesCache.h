#ifndef CTexturesCache_H
#define CTexturesCache_H

#include <windows.h>

#define MAX_CACHE 50

class CTexturesCache
{
    private:
		char szName[MAX_CACHE][50];
		UINT nTexture[MAX_CACHE];

		int nLastTexture;
	public:
	   CTexturesCache();
	   ~CTexturesCache();
	   UINT IsCache(char *szfilename);
	   void Insert(char *szfilename, UINT nTex);
	   
};

#endif