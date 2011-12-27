#ifndef CParticleSystemH
#define CParticleSystemH

#include "CGL.h"
#include "glUtil\CTextureLoader.h"

#define MAX_PARTICLES 500

typedef struct
{
	float  pX;           //posicion
	float  pY;
	float  pZ;

	float  dX;           //direccion
	float  dY;
	float  dZ;

	float  r;            //color
	float  g;
	float  b;

	float life;          //vida
	float fade;
} Particle;

typedef struct
{
	float x;
	float y;
	float z;
} PPoint;

typedef struct
{
	float r;
	float g;
	float b;
} PColor;

class ParticleSystem
{
	private:
		GLuint texture;
		Particle Particles[MAX_PARTICLES];

		float SystemSpeed;
		float ParticlesSize;
		float Intensity;

		int RandomSigne();
	public:
		bool UseSingleColor;

		PPoint Emisor;
		PPoint SystemGravity;
		PColor SystemColor;

		ParticleSystem(void);
		~ParticleSystem(void);

		void Draw();
		void Reset();

		void SetSystemSpeed(float value);
		void SetParticlesSize(float value);
		void SetIntensity(float value);
		float GetSystemSpeed()              { return SystemSpeed; }
		float GetParticlesSize()            { return ParticlesSize; }
		float GetIntensity()                { return Intensity; }

		void LoadTexture(char *szFilename);
};


#endif