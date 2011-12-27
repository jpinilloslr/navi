#ifndef CMagicCubeH
#define CMagicCubeH

#include "glUtil\CLoaderRSM.h"
#include "ParticleSystem.h"
#include <math.h>

enum cube_state { stShow = 1, stHide, stClose, stShowing, stHiding, stClosing };

class MagicCube
{
	private:
		UINT ParticlesTick;
		bool ShowParticles;
		ParticleSystem *PS;
		CLoaderRSM *RSM;
		GLuint texture;
		int value;

		float posX;
		float posY;
		float rotZ;
		float rotY;
		float scale;

		cube_state state;

		void Showing();
		void Hiding();
		void Closing();
	public:
		bool Select;
		MagicCube(void);
		~MagicCube(void);
		void Draw();
		void DrawPS();

		void SetPosX(float x)	{	posX = x;	}
		void SetPosY(float y)	{	posY = y;	}
		float GetPosX()			{	return posX;	}
		float GetPosY()			{	return posY;	}

		void Reset();
		void Show();
		void Hide();
		void Close();

		cube_state GetState()	{	return state;	}
		void SetValue(int i)	{	value = i;	}
		int GetValue()			{	return value;	}
		void LoadTexture();
		void Shoot();
};

#endif;