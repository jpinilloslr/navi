#include "Grid.h"


void Grid::SetValues()
{
	int vector[MAX_CUBES];
	int pointer = 0;
	bool bRepeated = false;
	int n;
	
	srand(GetTickCount());

	while(pointer < MAX_CUBES/2)
	{
		do
		{			
			n = (double)rand() / (RAND_MAX + 1) * (9 - 1) + 1;
		
			bRepeated = false;

			for(int i=0; i<pointer; i++)
			{
				if(vector[i]==n)
					bRepeated = true;
			}
		} while(bRepeated);

		vector[pointer] = n;
		pointer++;
	}

	while(pointer < MAX_CUBES)
	{
		do
		{
			n = (double)rand() / (RAND_MAX + 1) * (9 - 1) + 1;

			bRepeated = false;
		
			for(int i=MAX_CUBES/2; i<pointer; i++)
			{
				if(vector[i]==n)
					bRepeated = true;
			}
		} while(bRepeated);

		vector[pointer] = n;
		pointer++;
	}

	for(int i=0; i<MAX_CUBES; i++)
	{
		Cubes[i]->SetValue(vector[i]);
		Cubes[i]->LoadTexture();
	}
}

Grid::Grid(void)
{
	bDone = false;
	DoneTick = 0;
	Audio = NULL;
	float x = -4.5f;
	float y = 4.0f;

	for(int i=0; i<MAX_CUBES; i++)
	{
		Cubes[i] = new MagicCube();
		Cubes[i]->SetPosX(x);
		Cubes[i]->SetPosY(y);

		x+=3.0f;

		if(((i+1) % 4 == 0))
		{
			y-= 3.0f;
			x =-4.5f;
		}
	}

	PS = new ParticleSystem();
	PS->LoadTexture("SYSTEM\\PARTICLES\\particle.jpg");
	PS->SetSystemSpeed(1.0f);
	PS->SetParticlesSize(0.3f);
	PS->SystemGravity.y = -0.001f;
	PS->Emisor.z = -20.0f;
	PS->UseSingleColor = true;

	SetValues();	
}

Grid::~Grid(void)
{
	for(int i=0; i<MAX_CUBES; i++)
	{
		delete Cubes[i];
	}

	delete PS;
}

void Grid::Draw()
{

	for(int i=0; i<MAX_CUBES; i++)
	{
		Cubes[i]->Draw();
	}

	for(int i=0; i<MAX_CUBES; i++)
	{
		Cubes[i]->DrawPS();
	}

	int nVisibleCubes = 0;
	int value1 = -1;
	int value2 = 0;

	for(int i=0; i<MAX_CUBES; i++)
	{
		if((Cubes[i]->GetState() == stShow) )
		{
			nVisibleCubes++;

			if(value1 != -1)
				value2 = Cubes[i]->GetValue();
			else
				value1 = Cubes[i]->GetValue();
		}
	}

	if(nVisibleCubes > 1)
	{
		if(value1 == value2)
		{
			if(Audio)
				Audio->Bonus();

			for(int i=0; i<MAX_CUBES; i++)
				if(Cubes[i]->GetState()==stShow)
					Cubes[i]->Close();
		}
		else
		{
			if(Audio)
				Audio->Wrong();
			for(int i=0; i<MAX_CUBES; i++)
				Cubes[i]->Hide();
		}
	}

	if(PS->Emisor.z < 400.0f)
	{
		PS->Emisor.y = -0.5f;
		PS->Emisor.z += 0.8f;
		PS->Draw();
	}

	bDone = true;

	for(int i=0; i<MAX_CUBES; i++)
	{
		if((Cubes[i]->GetState() != stClose) )
		{
			bDone = false;
		}
	}

	if((bDone) && (DoneTick == 0))
		DoneTick = GetTickCount();

}

void Grid::ShowCube(int n)
{
	if((n >= 0) && (n<16))
	{
		int nVisibleCubes = 0;
		cube_state state = Cubes[n]->GetState();

		if((state == stHide) || (state == stHiding))
			Cubes[n]->Show();
		else
		if((state == stShow) || (state == stShowing))
			Cubes[n]->Hide();

	}
}

bool Grid::Done()
{
	if(bDone)
	{
		if(GetTickCount() - DoneTick > 3000)
			return true;
	}

	return false;
}

void Grid::Reset()
{
	bDone = false;
	DoneTick = 0;
	SetValues();

	PS->SetSystemSpeed(2.0f);
	PS->SetParticlesSize(0.3f);
	PS->SystemGravity.y = -0.001f;
	PS->Emisor.z = -20.0f;	

	for(int i=0; i<MAX_CUBES; i++)
	{
		Cubes[i]->Reset();
	}
}

bool Grid::IsCubeVisible(int n)
{
	if((n >= 0) && (n<16))
	{
		cube_state state = Cubes[n]->GetState();

		return (state != stClose);			
	}

	return false;
}


void Grid::SelectCube(int n)
{
	if((n >= 0) && (n<16))
	{
		Cubes[n]->Select = true;		
	}
	else
	if(n == -1)
	{
		for(int i=0; i<MAX_CUBES; i++)
			Cubes[i]->Select = false;
	}
}