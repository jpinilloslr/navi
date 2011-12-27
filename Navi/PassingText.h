#ifndef CPassingTextH
#define CPassingTextH

#include <Windows.h>
#include "glUtil\CTextureLoader.h"

#define MAX_TEXTS 7

enum trans_states { trans_fadein = 0, trans_fadeout, trans_done };

class CPassingText
{
	private:
		float alpha;
		unsigned int nTick;
		int CurrentText;
		GLuint Textures[MAX_TEXTS];

		trans_states transition;
		bool bStarted;

		void Timing();
		bool FadeOut();
		bool FadeIn();
		void Transition();
	public:
		CPassingText(void);
		~CPassingText(void);
		void Load();
		void Start();
		void Draw();
		void StopPassingText()	{ bStarted = true; CurrentText = 10; }
};

#endif