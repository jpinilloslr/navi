#include "ScenesManager.h"


CScenesManager::CScenesManager()
{
	gMenu = new GameMenu();
	gScene = new CScene();
	gCredits = new Credits();
}


CScenesManager::~CScenesManager()
{
	delete gScene;
	delete gMenu;
	delete gCredits;
}

void CScenesManager::LoadScene()
{
	char szScenePath[MAX_PATH];
	strcpy_s(szScenePath, MAX_PATH, "SYSTEM\\SCENES\\TEST");

	gScene->Load(szScenePath);
}

void CScenesManager::LoadMenu()
{
	gMenu->Load("SYSTEM\\MENU");
}

void CScenesManager::LoadCredits()
{
	gCredits->Load("SYSTEM\\CREDITS");
}

void CScenesManager::DrawCurrentScene()
{
	gScene->Draw();
}

void CScenesManager::DrawMenu()
{
	gMenu->Draw();
}

void CScenesManager::DrawCredits()
{
	gCredits->Draw();
}