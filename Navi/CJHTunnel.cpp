#include "CJHTunnel.h"


CJHTunnel::CJHTunnel()
{
	Angle = 0.0f;
	Speed = 0.3f;
	TextureSpeed = 1.0f/50.0f;
}


CJHTunnel::~CJHTunnel()
{
}


void CJHTunnel::Draw()
{
	GLfloat c, j1, j2;

	Angle = Angle + Speed;

	// setup tunnel coordinates
	for(int i=0; i<13; i++)
	{
		for(int j=0; j<33; j++)
		{
			Tunnels[i][j].X =(3.0f - (float)j/12.0f)*cos(2.0f*3.14159/12.0f*(float)i) + 2.0f*sin((Angle+2.0f*(float)j)/29.0f) + cos((Angle+2.0f*(float)j)/13.0f) - 2.0f*sin(Angle/29.0f) - cos(Angle/13.0f);
			Tunnels[i][j].Y =(3.0f - (float)j/12.0f)*sin(2.0f*3.14159/12.0f*(float)i) + 2.0f*cos((Angle+2.0f*(float)j)/33.0f) + sin((Angle+2.0f*(float)j)/17.0f) - 2.0f*cos(Angle/33.0f) - sin(Angle/17.0f);
			Tunnels[i][j].Z = -(float)j;
		}
	}

	// draw tunnel
	for(int j=0; j<31; j++)
	{
		j1 = (float)j/32.0f + Angle*TextureSpeed;        // precalculate texture v coords for speed
		j2 = ((float)j+1.0f)/32.0f + Angle*TextureSpeed;
		
		// near the end of the tunnel, fade the effect away
		if (j > 24)
			c = 1.0f-(j-24.0f)/10.0f;
		else
			c = 1.0;
		
		glColor3f(c, c, c);
		
		glBegin(GL_QUADS);
		
		for(int i=0; i<12; i++)
		{
			glTexCoord2f(((float)i-3.0f)/12.0f, j1); glVertex3f(Tunnels[i  ][j  ].X, Tunnels[i  ][j  ].Y, Tunnels[i  ][j  ].Z);
			glTexCoord2f(((float)i-2.0f)/12.0f, j1); glVertex3f(Tunnels[i+1][j  ].X, Tunnels[i+1][j  ].Y, Tunnels[i+1][j  ].Z);
			glTexCoord2f(((float)i-2.0f)/12.0f, j2); glVertex3f(Tunnels[i+1][j+1].X, Tunnels[i+1][j+1].Y, Tunnels[i+1][j+1].Z);
			glTexCoord2f(((float)i-3.0f)/12.0f, j2); glVertex3f(Tunnels[i  ][j+1].X, Tunnels[i  ][j+1].Y, Tunnels[i  ][j+1].Z);
		}
		glEnd();
	}
}