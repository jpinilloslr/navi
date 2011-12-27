#ifndef CGridH
#define CGridH

#include "MagicCube.h"
#include "AudioManager.h"

#define MAX_CUBES 16

class Grid
{
	private:
		MagicCube *Cubes[MAX_CUBES];
		CAudioManager *Audio;
		ParticleSystem *PS;

		void SetValues();
		bool bDone;
		UINT DoneTick;
	public:
		Grid(void);
		~Grid(void);
		void Draw();
		void ShowCube(int n);
		void SetAudio(CAudioManager *a)	{	Audio = a;	}
		bool Done();
		void Reset();
		bool IsCubeVisible(int cube);
		void SelectCube(int n);
};

#endif;