#ifndef CSceneH
#define CSceneH

#include "glUtil\CLoaderRSM.h"
#include "Grid.h"
#include "GameTimer.h"

class CScene
{
	private:
		float fSceneRot;
		Grid *SGrid;
		CGameTimer *Timer;
		CLoaderRSM *SceneModel;
	public:
		bool ActiveScene;
		CScene();
		~CScene();
		bool Load(char *szPath);
		void Draw();
		Grid *GetGrid()	{	return SGrid;	}
		CGameTimer *GetTimer()	{	return Timer;	}
};

#endif