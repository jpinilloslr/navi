#ifndef CCreditsH
#define CCreditsH

#include "glUtil\CLoaderRSM.h"
#include "ParticleSystem.h"

class Credits
{
	private:
		GLuint backtexture;
		GLuint backbtntexture;
		GLuint credittexture;
		bool BackMouseOver;

		ParticleSystem *PS;
	public:
		Credits(void);
		~Credits(void);
		void Load(char *szPath);
		void Draw();
		void SelectBackButton(bool b)	{	BackMouseOver = b;	}
		void Reset();
};

#endif