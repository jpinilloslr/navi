#ifndef CPerformanceControllerH
#define CPerformanceControllerH

#include "CGL.h"

class CPerformanceController
{
	public:
		CPerformanceController();
		~CPerformanceController();
		void EnableVerticalSync(bool enableVerticalSync);
		void SetProcessorAffinity();
		void SwitchToFullScreen(int width, int height, int bits);
};

#endif
