#ifndef CJHTunnelH
#define CJHTunnelH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "glUtil\CGL.h"

typedef struct
{
	GLfloat X;
	GLfloat Y;
	GLfloat Z;
} CGLCoord;

class CJHTunnel
{
	private:
		CGLCoord Tunnels[34][34];
		GLfloat  Angle;
		GLfloat  Speed;
		GLfloat  TextureSpeed;
	public:
		CJHTunnel();
		~CJHTunnel();
		void Draw();
};

#endif