#ifndef CSystemManagerH
#define CSystemManagerH

#include "InputManager.h"
#include "GraphicsManager.h"
#include "AudioManager.h"
#include "PerformanceController.h"

class CSystemManager
{
	private:
		CInputManager *Input;
		CGraphicsManager *Graphics;
		CAudioManager *Audio;
		CPerformanceController *PerformanceController;
		bool bStarted;
	public:
		bool Finished;
		CSystemManager();
		~CSystemManager();
		void Start(bool Fullscreen, int WidthResolution, int HeightResolution);
		void DrawGraphics();

		void ProcessMouseInput(int x, int y);
		void ProcessMouseOver(int x, int y);

};

#endif