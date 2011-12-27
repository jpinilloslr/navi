#include "AudioManager.h"


CAudioManager::CAudioManager(void)
{
	AE = new CAudioEngine();
}


CAudioManager::~CAudioManager(void)
{
	delete AE;
}

void CAudioManager::LoadSounds(char *szFile)
{
	bool bSuccess;
	char szCurrentPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, szCurrentPath);
	SetCurrentDirectoryA(szFile);

	AE->LoadFile(sndMusic, "music.wav");
	AE->BindSourceToBuffer(sndMusic, sndMusic);

	AE->LoadFile(sndReveal, "reveal.wav");
	AE->BindSourceToBuffer(sndReveal, sndReveal);

	AE->LoadFile(sndBonus, "bonus.wav");
	AE->BindSourceToBuffer(sndBonus, sndBonus);

	AE->LoadFile(sndStart, "start.wav");
	AE->BindSourceToBuffer(sndStart, sndStart);

	AE->LoadFile(sndMenuOver, "menuover.wav");
	AE->BindSourceToBuffer(sndMenuOver, sndMenuOver);

	AE->LoadFile(sndMenuClick, "menuclick.wav");
	AE->BindSourceToBuffer(sndMenuClick, sndMenuClick);

	AE->LoadFile(sndWrong, "wrong.wav");
	AE->BindSourceToBuffer(sndWrong, sndWrong);

	SetCurrentDirectoryA(szCurrentPath);
}

void CAudioManager::Reveal()
{
	AE->Stop(sndReveal);
	AE->Play(sndReveal, false);
}

void CAudioManager::Bonus()
{
	AE->Stop(sndBonus);
	AE->Play(sndBonus, false);
}

void CAudioManager::Start()
{
	AE->Stop(sndStart);
	AE->Play(sndStart, false);
}

void CAudioManager::Wrong()
{
	AE->Stop(sndWrong);
	AE->Play(sndWrong, false);
}

void CAudioManager::MenuOver()
{
	AE->Play(sndMenuOver, false);
}

void CAudioManager::MenuClick()
{
	AE->Play(sndMenuClick, false);
}

void CAudioManager::Music()
{
	AE->Play(sndMusic, true);
}