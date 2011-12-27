#include "InputManager.h"


CInputManager::CInputManager()
{
}


CInputManager::~CInputManager()
{
}

bool CInputManager::IsKeyPressed(int nVirtualKey)
{
	return ((GetKeyState(nVirtualKey) != 0) && (GetKeyState(nVirtualKey) != 1));
}

void CInputManager::ProcessInGameMouseInput(int x, int y)
{
	RECT rect;
	rect.left = 113;
	rect.right = 187;
	rect.top = 23;
	rect.bottom = 99;

	for(int i=0; i<16; i++)
	{
		if((x > rect.left) && (x < rect.right))
		{
			if((y > rect.top) && (y < rect.bottom))
			{
				object = cube;
				object_param = i+1;
				type = it_click;
			}
		}
		rect.left += 40+74;
		rect.right += 40+74;

		if(((i+1) % 4 == 0))
		{
			rect.left = 113;
			rect.right = 187;
			rect.top += 40+74;
			rect.bottom += 40+74;
		}
	}

				/*char szText[255];
				sprintf_s(szText, "X: %d, Y: %d", x, y);
				MessageBoxA(NULL, szText, "", MB_OK);	*/
}

void CInputManager::ProcessInGameMouseOver(int x, int y)
{
	RECT rect;
	rect.left = 113;
	rect.right = 187;
	rect.top = 23;
	rect.bottom = 99;

	for(int i=0; i<16; i++)
	{
		if((x > rect.left) && (x < rect.right))
		{
			if((y > rect.top) && (y < rect.bottom))
			{
				object = cube;
				object_param = i+1;
				type = it_mouseover;
			}
		}
		rect.left += 40+74;
		rect.right += 40+74;

		if(((i+1) % 4 == 0))
		{
			rect.left = 113;
			rect.right = 187;
			rect.top += 40+74;
			rect.bottom += 40+74;
		}
	}
				/*char szText[255];
				sprintf_s(szText, "X: %d, Y: %d", x, y);
				MessageBoxA(NULL, szText, "", MB_OK);	*/
}

void CInputManager::ProcessInMenuMouseInput(int x, int y)
{
	RECT rectStart;
	rectStart.left = 269;
	rectStart.right = 371;
	rectStart.top = 337;
	rectStart.bottom = 365;

	RECT rectCredits;
	rectCredits.left = 254;
	rectCredits.right = 390;
	rectCredits.top = 374;
	rectCredits.bottom = 401;

	RECT rectExit;
	rectExit.left = 282;
	rectExit.right = 356;
	rectExit.top = 412;
	rectExit.bottom = 439;

	if((x > rectStart.left) && (x < rectStart.right))
	{
		if((y > rectStart.top) && (y < rectStart.bottom))
		{
			object = menuentry;
			object_param = 1;
			type = it_click;
		}
	}


	if((x > rectCredits.left) && (x < rectCredits.right))
	{
		if((y > rectCredits.top) && (y < rectCredits.bottom))
		{
			object = menuentry;
			object_param = 2;
			type = it_click;
		}
	}

	if((x > rectExit.left) && (x < rectExit.right))
	{
		if((y > rectExit.top) && (y < rectExit.bottom))
		{
			object = menuentry;
			object_param = 3;
			type = it_click;
		}
	}

				/*char szText[255];
				sprintf_s(szText, "X: %d, Y: %d", x, y);
				MessageBoxA(NULL, szText, "", MB_OK);	*/
}

void CInputManager::ProcessInMenuMouseOver(int x, int y)
{
	RECT rectStart;
	rectStart.left = 269;
	rectStart.right = 371;
	rectStart.top = 337;
	rectStart.bottom = 365;

	RECT rectCredits;
	rectCredits.left = 254;
	rectCredits.right = 390;
	rectCredits.top = 374;
	rectCredits.bottom = 401;

	RECT rectExit;
	rectExit.left = 282;
	rectExit.right = 356;
	rectExit.top = 412;
	rectExit.bottom = 439;

	if((x > rectStart.left) && (x < rectStart.right))
	{
		if((y > rectStart.top) && (y < rectStart.bottom))
		{
			object = menuentry;
			object_param = 1;
			type = it_mouseover;
		}
	}


	if((x > rectCredits.left) && (x < rectCredits.right))
	{
		if((y > rectCredits.top) && (y < rectCredits.bottom))
		{
			object = menuentry;
			object_param = 2;
			type = it_mouseover;
		}
	}

	if((x > rectExit.left) && (x < rectExit.right))
	{
		if((y > rectExit.top) && (y < rectExit.bottom))
		{
			object = menuentry;
			object_param = 3;
			type = it_mouseover;
		}
	}

				/*char szText[255];
				sprintf_s(szText, "X: %d, Y: %d", x, y);
				MessageBoxA(NULL, szText, "", MB_OK);	*/
}

void CInputManager::ProcessInCreditsMouseInput(int x, int y)
{
	RECT rect;
	rect.left = 5;
	rect.right = 109;
	rect.top = 407;
	rect.bottom = 438;

	if((x > rect.left) && (x < rect.right))
	{
		if((y > rect.top) && (y < rect.bottom))
		{
			object = menuentry;
			object_param = 4;
			type = it_click;
		}
	}
}

void CInputManager::ProcessInCreditsMouseOver(int x, int y)
{
	RECT rect;
	rect.left = 5;
	rect.right = 109;
	rect.top = 407;
	rect.bottom = 438;

	if((x > rect.left) && (x < rect.right))
	{
		if((y > rect.top) && (y < rect.bottom))
		{
			object = menuentry;
			object_param = 4;
			type = it_mouseover;
		}
	}	
}

input_object CInputManager::GetObject()
{
	input_object o = object;
	object = none;
	return o;
}