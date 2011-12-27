#include "SystemManager.h"


CSystemManager::CSystemManager()
{
	Input		= new CInputManager();
	Graphics	= new CGraphicsManager();
	Audio		= new CAudioManager();
	PerformanceController = new CPerformanceController();

	Audio->LoadSounds("SYSTEM\\SOUNDS");
	Graphics->GetScenesManager()->GetCurrentScene()->GetGrid()->SetAudio(Audio);
	Finished = false;
	bStarted = false;
}

CSystemManager::~CSystemManager()
{
	delete PerformanceController;
	delete Graphics;
	delete Input;
	delete Audio;
}

void CSystemManager::Start(bool Fullscreen, int WidthResolution, int HeightResolution)
{
	PerformanceController->EnableVerticalSync(true);
	PerformanceController->SetProcessorAffinity();

	if(Fullscreen)
		PerformanceController->SwitchToFullScreen(WidthResolution, HeightResolution, 32);
}

void CSystemManager::DrawGraphics()
{
	if(!bStarted)
	{
		bStarted = true;
		Audio->Music();
	}

	Graphics->Draw();
}

void CSystemManager::ProcessMouseInput(int x, int y)
{
	input_object object;
	input_type type;
	int param;

	if(Graphics->GetScreen() == game)
	{
		Input->ProcessInGameMouseInput(x, y);
	}
	else
	if(Graphics->GetScreen() == credits)
	{
		Input->ProcessInCreditsMouseInput(x, y);
	}
	else
	if(Graphics->GetScreen() == menu)
	{
		Input->ProcessInMenuMouseInput(x, y);
	}

	object = Input->GetObject();
	param = Input->GetObjectParam();	
	type = Input->GetEventType();	

	if(object == cube)
	{
		if(type == it_click)
		{
			if(Graphics->GetScenesManager()->GetCurrentScene()->GetGrid()->IsCubeVisible(param-1))
			{
				Audio->Reveal();
				Graphics->GetScenesManager()->GetCurrentScene()->GetGrid()->ShowCube(param-1);
			}
		}
	}

	if(object == menuentry)
	{
		Graphics->GetScenesManager()->GetMenu()->StopPassingText();

		if(param == 1)
		{
			if(type == it_click)
			{
				Audio->MenuClick();
				Graphics->GetScenesManager()->GetCurrentScene()->GetGrid()->Reset();
				Graphics->GetScenesManager()->GetCurrentScene()->GetTimer()->Reset();
				Graphics->GetScenesManager()->GetCurrentScene()->GetTimer()->Start();
				Audio->Bonus();
				Graphics->SetScreen(game);
			}
		}
		if(param == 2)
		{
			if(type == it_click)
			{
				Audio->MenuClick();
				Graphics->GetScenesManager()->GetCredits()->Reset();
				//Audio->Start();
				Graphics->SetScreen(credits);
			}
		}
		if(param == 3)
		{
			if(type == it_click)
			{
				Audio->MenuClick();
				Finished = true;
			}
		}
		if(param == 4)
		{
			if(type == it_click)
			{
				Audio->MenuClick();
				Graphics->SetScreen(menu);
			}
		}
	}
}

void CSystemManager::ProcessMouseOver(int x, int y)
{
	input_object object;
	input_type type;
	int param;
	bool backbtn;

	if(Graphics->GetScreen() == game)
	{
		Input->ProcessInGameMouseOver(x, y);
	}
	else
	if(Graphics->GetScreen() == credits)
	{
		Input->ProcessInCreditsMouseOver(x, y);
	}
	else
	if(Graphics->GetScreen() == menu)
	{
		Input->ProcessInMenuMouseOver(x, y);
	}

	object = Input->GetObject();
	param = Input->GetObjectParam();	
	type = Input->GetEventType();	
	backbtn = false;

	Graphics->GetScenesManager()->GetCurrentScene()->GetGrid()->SelectCube(-1);

	if(object == cube)
	{
		if(type == it_mouseover)
		{
			if(Graphics->GetScenesManager()->GetCurrentScene()->GetGrid()->IsCubeVisible(param-1))
			{
				Graphics->GetScenesManager()->GetCurrentScene()->GetGrid()->SelectCube(param-1);
			}
		}
	}

	if(object == menuentry)
	{
		if(type == it_mouseover)
		{				
			//Audio->MenuOver();
			Graphics->GetScenesManager()->GetMenu()->SelectMenu(param);
		}

		if(param == 4)
		{
			backbtn = true;
		}
	}

	Graphics->GetScenesManager()->GetCredits()->SelectBackButton(backbtn);
}
