#ifndef CTextureLoaderH
#define CTextureLoaderH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <olectl.h>
#include <gl\GL.h>
#include <gl\GLU.h>

typedef struct
{
    GLubyte *imageData;
    GLuint bpp;
    GLuint width;
    GLuint height;
    GLuint texID;
} glImage;

class CTextureLoader
{
    private:
	   void *ReadTGA(char *filename, int *tam);
	   bool LoadTGA(char *filename, GLuint &Texture);
	   bool BuildTexture(char *szPathName, GLuint &texid);	   
	public:
		int maxAnisotrophy;
	   CTextureLoader();
	   ~CTextureLoader();
	   bool LoadTexture(char *filename, GLuint &Texture);


};

#endif