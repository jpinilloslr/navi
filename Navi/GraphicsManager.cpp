#include "GraphicsManager.h"


CGraphicsManager::CGraphicsManager()
{
	ScenesManager = new CScenesManager();
	CurrentScreen = menu;
	ScenesManager->LoadMenu();
	ScenesManager->LoadScene();
	ScenesManager->LoadCredits();
}


CGraphicsManager::~CGraphicsManager()
{
	delete ScenesManager;
}

void CGraphicsManager::Draw()
{
	if(CurrentScreen == game)
		ScenesManager->DrawCurrentScene();
	else
	if(CurrentScreen == credits)
		ScenesManager->DrawCredits();
	else
		ScenesManager->DrawMenu();
	
	if(GetScenesManager()->GetCurrentScene()->GetGrid()->Done())
	{
		SetScreen(menu);
		GetScenesManager()->GetCurrentScene()->GetGrid()->Reset();
		GetScenesManager()->GetCurrentScene()->GetTimer()->SetRecord();
	}
}