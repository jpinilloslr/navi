#include "PassingText.h"


CPassingText::CPassingText(void)
{
	CurrentText = 10;
	alpha = 0.0f;
	transition = trans_done;
	bStarted = false;
}


CPassingText::~CPassingText(void)
{
}

void CPassingText::Load()
{
	char szFile[250];

	CTextureLoader TL;

	for(int i=0; i<MAX_TEXTS; i++)
	{
		sprintf(szFile, "ps%d.jpg", i+1);
		TL.LoadTexture(szFile, Textures[i]);
	}
}

void CPassingText::Start()
{
	nTick = GetTickCount();
}

void CPassingText::Draw()
{
	if(CurrentText < MAX_TEXTS)
	{
		glBindTexture(GL_TEXTURE_2D, Textures[CurrentText]);

		glEnable(GL_BLEND);
		glColor4f(1.0f, 1.0f, 1.0f, alpha);

		glPushMatrix();
		glTranslatef(0.0f, -0.05f, -1.0f);

		glBegin(GL_QUADS);
		glNormal3f( 0.0f, -3.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f);		glVertex3f( 0.6f, -0.6f, 0.1f);
		glTexCoord2f(1.0f, 1.0f);		glVertex3f( 0.6f,  0.6f, 0.1f);
		glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.6f,  0.6f, 0.1f);
		glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.6f, -0.6f, 0.1f);
		glEnd();
		glPopMatrix();

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glDisable(GL_BLEND);
	}

	Timing();
}

void CPassingText::Timing()
{
	if(!bStarted)
	{
		if(GetTickCount() - nTick > 13000+205000)
		{
			CurrentText = 0;

			if(FadeIn())
			{
				bStarted = true;	
				nTick = GetTickCount();
			}
		}
	}
	else
	if(CurrentText < MAX_TEXTS)
	{
		if(GetTickCount() - nTick > 3000)
		{
			Transition();
		}
	}
}

void CPassingText::Transition()
{
	if(transition == trans_done)
	{
		transition = trans_fadeout;
	}
	else
	if(transition == trans_fadeout)
	{
		if(CurrentText == 6)
		{
			if(GetTickCount() - nTick < 23000)
				return;
		}

		if(FadeOut())
		{
			transition = trans_fadein;
			CurrentText++;
		}
	}
	else
	if(transition == trans_fadein)
	{
		if(FadeIn())
		{
			transition = trans_done;
			nTick = GetTickCount();
		}
	}
}

bool CPassingText::FadeOut()
{
	alpha -= 0.01f;

	if(alpha <= 0.0f)
	{
		return true;
	}
	return false;
}

bool CPassingText::FadeIn()
{
	alpha += 0.01f;

	if(alpha >= 1.0f)
	{
		return true;
	}
	return false;
}