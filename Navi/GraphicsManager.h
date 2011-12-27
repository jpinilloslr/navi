#ifndef CGraphicsManagerH
#define CGraphicsManagerH

#include "CGL.h"
#include "ScenesManager.h"

enum screen { menu, game, credits };

class CGraphicsManager
{
	private:
		CScenesManager *ScenesManager;
		screen CurrentScreen;
	public:
		CGraphicsManager();
		~CGraphicsManager();

		void Draw();
		CScenesManager *GetScenesManager()	{	return ScenesManager;	}

		screen GetScreen()			{	return CurrentScreen;	}
		void SetScreen(screen s)	{	CurrentScreen = s;	}
};

#endif