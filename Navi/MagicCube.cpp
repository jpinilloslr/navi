#include "MagicCube.h"


MagicCube::MagicCube(void)
{
	posX = 0.0f;
	posY = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0;
	scale = 1.0f;
	value = 0;
	ShowParticles = false;
	Hide();
	Select = false;

	PS = new ParticleSystem();
	PS->LoadTexture("SYSTEM\\PARTICLES\\particle.jpg");
	PS->SetSystemSpeed(2.0f);
	PS->SetParticlesSize(0.3f);
	PS->SystemGravity.y = -0.001f;
	PS->Emisor.z = -5.0f;
	PS->UseSingleColor = true;
	RSM = new CLoaderRSM();
	
	char szCurrentPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, szCurrentPath);
	SetCurrentDirectoryA("SYSTEM\\BLOCKS");

	RSM->Load("block.rsm");

	SetCurrentDirectoryA(szCurrentPath);
}


MagicCube::~MagicCube(void)
{
	delete RSM;
	delete PS;
}

void MagicCube::LoadTexture()
{
	CTextureLoader TL;
	char szFile[MAX_PATH];

	sprintf(szFile, "SYSTEM\\BLOCKS\\%d.jpg", value);
	TL.LoadTexture(szFile, texture);
}

void MagicCube::Draw()
{
	if(state != stClose)
	{
		glPushMatrix();
		glTranslatef(posX, posY, 0.0f);

		if(Select)
		{
			glColor3f(0.8f, 0.8f, 0.8f);
		}

		glRotatef(rotY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

		if(scale != 1.0);
			glScalef(scale, scale, scale);

		/*glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);*/
		RSM->Draw();
		/*glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);*/

		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f);		glVertex3f( 0.7f, -0.7f, -0.0f);
		glTexCoord2f(1.0f, 1.0f);		glVertex3f( 0.7f,  0.7f, -0.0f);
		glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.7f,  0.7f, -0.0f);
		glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.7f, -0.7f, -0.0f);
		glEnd();

		glPopMatrix();

		if(Select)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
		}

		if(state == stHiding)
			Hiding();
		if(state == stShowing)
			Showing();
		if(state == stClosing)
			Closing();
	}

}

void MagicCube::DrawPS()
{
	if(ShowParticles)
	{
		if(GetTickCount() - ParticlesTick < 10000)
		{
			glPushMatrix();
			PS->Emisor.x = posX+(sinf((float)GetTickCount()));
			PS->Emisor.y = posY+(cosf((float)GetTickCount()));
			PS->Emisor.z += 0.25f;
			PS->Draw();
			glPopMatrix();
		}
	}
}

void MagicCube::Show()
{
	if((state != stClose) && (state != stClosing))
		state = stShowing;
}

void MagicCube::Hide()
{
	if((state != stClose) && (state != stClosing))
		state = stHiding;
}

void MagicCube::Close()
{
	state = stClosing;
}

void MagicCube::Showing()
{
	if(rotY > 0.0f)
		rotY -= 10.0f;
	else
		state = stShow;
}

void MagicCube::Hiding()
{
	if(rotY < 180.0f)
		rotY += 10.0f;
	else
		state = stHide;
}

void MagicCube::Closing()
{
	if(scale > 0.0f)
	{
		scale -= 0.05f;
		rotZ += 20.0f;

		if(!ShowParticles)
		{
			ShowParticles = true;
			ParticlesTick = GetTickCount();
		}
	}
	else
		state = stClose;
}

void MagicCube::Reset()
{
	rotY = 0.0f;
	rotZ = 0.0;
	scale = 1.0f;
	ShowParticles = false;
	state = stHiding;
	Hide();

	PS->Emisor.z = -5.0f;
}

void MagicCube::Shoot()
{
	if(!ShowParticles)
	{
		ShowParticles = true;
		ParticlesTick = GetTickCount();
		PS->Emisor.z = -5.0f;
	}
}