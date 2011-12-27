#ifndef CFPSCounterH
#define CFPSCounterH

#include "glUtil\CFont.h"

class CFPSCounter
{
	private:
		CFont *Font;
		int counter;
		int fps;
	public:
		CFPSCounter();
		~CFPSCounter();
		void Draw();
		void Loop();
};

#endif
