#ifndef CGameMenuH
#define CGameMenuH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "CJHTunnel.h"
#include "PassingText.h"
#include "glUtil\CTextureLoader.h"

class GameMenu
{
	private:
		GLuint tunneltexture;
		GLuint menutexture;
		GLuint logotexture;
		CJHTunnel *Tunnel;
		CPassingText *PassingText;

		float selectorx;
		float selectory;
	public:
		GameMenu(void);
		~GameMenu(void);
		void Load(char *szPath);
		void Draw();
		void SelectMenu(int);
		void StopPassingText()	{ PassingText->StopPassingText(); }
};

#endif