#ifndef CLoaderRSMH
#define CLoaderRSMH

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "CTextureLoader.h"
#include "CTexturesCache.h"
#include <gl\GL.h>
#include <gl\GLU.h>

#define  RSM_SUCCESS        0
#define  RSM_ERROR_FILE     1
#define  RSM_ERROR_IDENT    2
#define  RSM_ERROR_VERSION  3

typedef struct
{
   float X;
   float Y;
} CTextCoord;

typedef struct
{
   float X;
   float Y;
   float Z;
} CVertex;

typedef struct
{
    char          szIdent[4];
	char          szName[15];
	unsigned int  nVersion;
	unsigned int  nSurfaces;
	unsigned int  nTextures;
	unsigned int  nFrames;
} CHeaderRSM;

typedef struct
{
    CVertex      Vertex[3];
	CVertex      Normal[3];
	CTextCoord   TextCoord[3];
    unsigned int Texture;
} CSurfaceRSM;



class CLoaderRSM
{
    private:
	   CHeaderRSM    Header;
	   CSurfaceRSM   *Surfaces;
	   GLuint        *Textures;
	   GLuint        DisplayList;
	   unsigned int  nLights;
	   unsigned int  nTick;
	   unsigned int  nCurrTriangle, nCurrFrame;
	   
	   void LoadTexture(char *filename, GLuint &Texture);
	   CTexturesCache *TexCache;
	public:
		bool bAnimTerminated;
		bool Textured;
	   CLoaderRSM();
	   ~CLoaderRSM();

	   CHeaderRSM      GetHeader()                {  return Header;       }
	   CSurfaceRSM    *GetSurfaces()              {  return Surfaces;     }
	   GLuint         *GetTextures()              {  return Textures;     }
	   GLuint          GetDisplayList()           {  return DisplayList;  }
	   CTexturesCache *GetTextureCache()          {  return TexCache;     }
	   
	   int Load(char *file);
	   bool DrawFrame(unsigned int Frame);
	   bool InterpolateFrame(unsigned int Frame, unsigned int NextFrame, unsigned int Delay);
	   bool Animate(unsigned int StartFrame, unsigned int EndFrame, unsigned int Delay, bool bInterpolated);
	   bool AnimateOnce(unsigned int StartFrame, unsigned int EndFrame, unsigned int Delay, bool bInterpolated);
	   bool AnimateBack(unsigned int StartFrame, unsigned int EndFrame, unsigned int Delay, bool bInterpolated);
	   bool Draw();
	   bool CallDisplayList();
	   void Reset();
	   bool BuildDisplayList();
	   int  GetTrianglesCount()              { return Header.nSurfaces;     }
	   int  GetFramesCount()                 { return Header.nFrames;       }	   
	   int  GetTexturesCount()               { return Header.nTextures;     }
	   void GetName(char *Name)              { strcpy_s(Name, sizeof(Name), Header.szName); }
	   bool IsAnimated()                     { return (Header.nFrames > 1); }
	   
	   bool GetFirstTriangle(CVertex &X, CVertex &Y, CVertex &Z);
	   bool GetNextTriangle(CVertex &X, CVertex &Y, CVertex &Z);
	   
	   void SetTexturesCache(CTexturesCache *cache)   {  TexCache = cache;  }
	   void Clone(CLoaderRSM *RSM);
};

#endif








