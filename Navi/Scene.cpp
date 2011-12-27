#include "Scene.h"


CScene::CScene()
{
	ActiveScene = true;
	SceneModel = new CLoaderRSM();
	SGrid = new Grid();
	Timer = new CGameTimer();
	fSceneRot = 0.0f;
}


CScene::~CScene()
{
	delete SceneModel;
	delete SGrid;
	delete Timer;
}

bool CScene::Load(char *szPath)
{
	bool bSuccess;
	char szCurrentPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, szCurrentPath);
	SetCurrentDirectoryA(szPath);

	bSuccess = (RSM_SUCCESS == SceneModel->Load("scene.rsm"));

	SetCurrentDirectoryA(szCurrentPath);
	return bSuccess;
}

void CScene::Draw()
{
	glPushMatrix();
	glTranslatef(0.0f, -7.0f, 5.0f);
	glRotatef(fSceneRot, 0.0f, 1.0f, 0.0f);
	glDisable(GL_LIGHTING);
	SceneModel->Draw();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	fSceneRot += 0.01;
	if(fSceneRot > 360.0f)
		fSceneRot = 0.0f;

	if(ActiveScene)
	{
		glTranslatef(0.0f, 0.0f, -10.0f);
		SGrid->Draw();
	}

	Timer->Draw();
}