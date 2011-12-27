#include "GameMenu.h"


GameMenu::GameMenu(void)
{
	Tunnel = new CJHTunnel();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	PassingText = new CPassingText();

	selectorx = 0.0;
	selectory = -0.33f;
}


GameMenu::~GameMenu(void)
{
	delete Tunnel;
	delete PassingText;
}

void GameMenu::Load(char *szPath)
{
	char szCurrentPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, szCurrentPath);
	SetCurrentDirectoryA(szPath);

	CTextureLoader tl;
	tl.LoadTexture("tunnel.jpg", tunneltexture);
	tl.LoadTexture("menu.tga", menutexture);
	tl.LoadTexture("logo.tga", logotexture);

	PassingText->Load();
	PassingText->Start();

	SetCurrentDirectoryA(szCurrentPath);
}

void GameMenu::Draw()
{
	glBindTexture(GL_TEXTURE_2D, tunneltexture);
	Tunnel->Draw();

	glPushMatrix();
	glTranslatef(0.0f, -0.4f, -1.0f);

	glBindTexture(GL_TEXTURE_2D, menutexture);
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, -3.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f);		glVertex3f( 0.3f, -0.3f, 0.1f);
	glTexCoord2f(1.0f, 1.0f);		glVertex3f( 0.3f,  0.3f, 0.1f);
	glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.3f,  0.3f, 0.1f);
	glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.3f, -0.3f, 0.1f);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0f, 0.25f, -1.0f);

	glBindTexture(GL_TEXTURE_2D, logotexture);
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, -3.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f);		glVertex3f( 0.5f, -0.5f, 0.1f);
	glTexCoord2f(1.0f, 1.0f);		glVertex3f( 0.5f,  0.5f, 0.1f);
	glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.5f,  0.5f, 0.1f);
	glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.5f, -0.5f, 0.1f);
	glEnd();
	glPopMatrix();

	//selector
	glPushMatrix();
	glTranslatef(selectorx, selectory, -1.0f);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, -3.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f);		glVertex3f( 0.17f+sinf(GetTickCount()/200.0f)/70, -0.045f+cosf(GetTickCount()/700.0f)/70, 0.09f);
	glTexCoord2f(1.0f, 1.0f);		glVertex3f( 0.17f+cosf(GetTickCount()/500.0f)/70,  0.045f+sinf(GetTickCount()/1000.0f)/70, 0.09f);
	glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.17f+sinf(GetTickCount()/300.0f)/70,  0.045f+cosf(GetTickCount()/250.0f)/70, 0.09f);
	glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.17f+cosf(GetTickCount()/100.0f)/70, -0.045f+sinf(GetTickCount()/800.0f)/70, 0.09f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	PassingText->Draw();
	glPopMatrix();
}

void GameMenu::SelectMenu(int menu)
{
	if(menu == 1)
	{
		selectory = -0.33f;
	}
	if(menu == 2)
	{
		selectory = -0.42f;
	}
	if(menu == 3)
	{
		selectory = -0.51f;
	}
}