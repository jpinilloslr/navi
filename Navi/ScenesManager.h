#ifndef CScenesManagerH
#define CScenesManagerH

#include "Scene.h"
#include "GameMenu.h"
#include "Credits.h"

enum Scenes { scene_intro=0, scene_test, scene_lab }; 

class CScenesManager
{
	private:
		CScene *gScene;
		GameMenu *gMenu;
		Credits *gCredits;
	public:
		CScenesManager();
		~CScenesManager();
		void LoadMenu();
		void LoadScene();
		void LoadCredits();
		void DrawCurrentScene();
		void DrawMenu();
		void DrawCredits();
		CScene *GetCurrentScene()	{	return gScene;	}
		GameMenu *GetMenu()			{	return gMenu;	}
		Credits *GetCredits()			{	return gCredits;	}
};

#endif