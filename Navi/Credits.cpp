#include "Credits.h"


Credits::Credits(void)
{
	BackMouseOver = false;

	PS = new ParticleSystem();
	PS->LoadTexture("SYSTEM\\PARTICLES\\particle.jpg");
	PS->SetSystemSpeed(3.0f);
	PS->SetParticlesSize(0.3f);
	PS->SystemGravity.y = -0.001f;
	PS->Emisor.z = -20.0f;
	PS->UseSingleColor = true;
}


Credits::~Credits(void)
{
	delete PS;
}

void Credits::Load(char *szPath)
{
	char szCurrentPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, szCurrentPath);
	SetCurrentDirectoryA(szPath);

	CTextureLoader tl;
	tl.LoadTexture("background.jpg", backtexture);
	tl.LoadTexture("back.tga", backbtntexture);
	tl.LoadTexture("credits.tga", credittexture);

	SetCurrentDirectoryA(szCurrentPath);
}

void Credits::Draw()
{
	glBindTexture(GL_TEXTURE_2D, backtexture);
	glTranslatef(0.0f, 0.0f, -20.0f);

	glBegin(GL_QUADS);
	glNormal3f( 0.0, 0.0, -1.0);
	glTexCoord2f(1.0, 0.0);		glVertex3f( 20.0, -20.0, 0.0);
	glTexCoord2f(1.0, 1.0);		glVertex3f( 20.0,  20.0, 0.0);
	glTexCoord2f(0.0, 1.0);		glVertex3f(-20.0,  20.0, 0.0);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-20.0, -20.0, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, credittexture);

	glBegin(GL_QUADS);
	glNormal3f( 0.0, 0.0, -1.0);
	glTexCoord2f(1.0, 0.0);		glVertex3f( 7.0, -7.0, 0.1);
	glTexCoord2f(1.0, 1.0);		glVertex3f( 7.0,  7.0, 0.1);
	glTexCoord2f(0.0, 1.0);		glVertex3f(-7.0,  7.0, 0.1);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-7.0, -7.0, 0.1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, backbtntexture);

	glPushMatrix();
	glTranslatef(-14.0f, -11.0f, 0.0f);

	if(!BackMouseOver)
	{
		glBegin(GL_QUADS);
		glNormal3f( 0.0, 0.0, -1.0);
		glTexCoord2f(1.0, 0.0);		glVertex3f( 2.5, -2.5, 0.1);
		glTexCoord2f(1.0, 1.0);		glVertex3f( 2.5,  2.5, 0.1);
		glTexCoord2f(0.0, 1.0);		glVertex3f(-2.5,  2.5, 0.1);
		glTexCoord2f(0.0, 0.0);		glVertex3f(-2.5, -2.5, 0.1);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
		glNormal3f( 0.0, 0.0, -1.0);
		glTexCoord2f(1.0, 0.0);		glVertex3f( 2.5+sinf(GetTickCount()/20.0f)/10, -2.5+cosf(GetTickCount()/70.0f)/10, 0.1);
		glTexCoord2f(1.0, 1.0);		glVertex3f( 2.5+cosf(GetTickCount()/50.0f)/10,  2.5+sinf(GetTickCount()/100.0f)/10, 0.1);
		glTexCoord2f(0.0, 1.0);		glVertex3f(-2.5+sinf(GetTickCount()/30.0f)/10,  2.5+cosf(GetTickCount()/20.0f)/10, 0.1);
		glTexCoord2f(0.0, 0.0);		glVertex3f(-2.5+cosf(GetTickCount()/10.0f)/10, -2.5+sinf(GetTickCount()/80.0f)/10, 0.1);
		glEnd();
	}

	glPopMatrix();

	if(PS->Emisor.z < 300)
	{
		PS->Emisor.x = cosf((float)GetTickCount()/100.0f)*3.0f;
		PS->Emisor.y = sinf((float)GetTickCount()/100.0f)*3.0f;
		PS->Emisor.z += 0.8f;
		PS->Draw();
	}
}

void Credits::Reset()
{
	PS->Emisor.z = -20.0f;
}