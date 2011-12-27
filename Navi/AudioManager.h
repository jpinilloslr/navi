#ifndef CAudioManagerH
#define CAudioManagerH

#include "CAudioEngine.h"

enum Sounds { sndMusic = 0, sndReveal, sndBonus, sndStart, sndWrong, sndMenuOver, sndMenuClick };

class CAudioManager
{
	private:
		CAudioEngine *AE;
	public:
		CAudioManager(void);
		~CAudioManager(void);
		void LoadSounds(char *szFile);
		void Reveal();
		void Bonus();
		void Start();
		void Wrong();
		void MenuOver();
		void MenuClick();
		void Music();
};

#endif