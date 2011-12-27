#ifndef CInputManagerH
#define CInputManagerH

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

enum input_object {none=0, cube, menuentry};
enum input_type   {it_none=0, it_mouseover, it_click};

class CInputManager
{
	private:
		input_object object;
		input_type type;
		int object_param;
	public:
		CInputManager();
		~CInputManager();
		bool IsKeyPressed(int nVirtualKey);
		void ProcessInGameMouseInput(int x, int y);
		void ProcessInMenuMouseInput(int x, int y);
		void ProcessInCreditsMouseInput(int x, int y);

		void ProcessInGameMouseOver(int x, int y);
		void ProcessInMenuMouseOver(int x, int y);
		void ProcessInCreditsMouseOver(int x, int y);

		input_object GetObject();
		int GetObjectParam()			{	return object_param;	}
		input_type GetEventType()		{	return type;	}
};

#endif
