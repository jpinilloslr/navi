#include "ParticleSystem.h"

int ParticleSystem::RandomSigne()
{
   int Signe;
   int n = (double)rand() / (RAND_MAX + 1) * (3 - 1) + 1;

   if (n % 2 == 0)
     Signe = 1;
   else
     Signe = -1;

   return Signe;
}

ParticleSystem::ParticleSystem(void)
{
	SystemSpeed = 1.0f;
	ParticlesSize = 0.5f;
	Intensity = 0.0f;

	Emisor.x = Emisor.y = Emisor.z = 0;
	SystemGravity.x = SystemGravity.y = SystemGravity.z = 0;
	SystemColor.r = SystemColor.g = SystemColor.b = 1.0f;

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		srand((GetTickCount()/1000)*i);

		Particles[i].pX = Emisor.x;
		Particles[i].pY = Emisor.y;
		Particles[i].pZ = Emisor.z;


		Particles[i].dX = RandomSigne() * float(rand()%100)/1500.0f+0.0003f;
		Particles[i].dY = RandomSigne() * float(rand()%100)/1500.0f+0.0003f;
		Particles[i].dZ = RandomSigne() * float(rand()%100)/1500.0f+0.0003f;

		if (UseSingleColor)
		{
			Particles[i].r = SystemColor.r;
			Particles[i].g = SystemColor.g;
			Particles[i].b = SystemColor.b;
		} else
		{
			Particles[i].r = ((double)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
			Particles[i].g = ((double)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
			Particles[i].b = ((double)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
		}


		Particles[i].life = 1.0f;
		Particles[i].fade =float((rand()%100)/1500.0f+0.00003f)+Intensity;
	}
}


ParticleSystem::~ParticleSystem(void)
{
}

void ParticleSystem::Reset()
{

   for (int i = 0; i < MAX_PARTICLES; i++)
   {
	 srand((GetTickCount()/1000)*i);

     Particles[i].pX = Emisor.x;
     Particles[i].pY = Emisor.y;
     Particles[i].pZ = Emisor.z;


     Particles[i].dX = RandomSigne() * float(rand()%100)/1500.0f+0.00003f;
     Particles[i].dY = RandomSigne() * float(rand()%100)/1500.0f+0.00003f;
     Particles[i].dZ = RandomSigne() * float(rand()%100)/1500.0f+0.00003f;

     if (UseSingleColor)
     {
       Particles[i].r = SystemColor.r;
       Particles[i].g = SystemColor.g;
       Particles[i].b = SystemColor.b;
     } else
     {
       Particles[i].r = ((double)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
       Particles[i].g = ((double)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
       Particles[i].b = ((double)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
     }


     Particles[i].life = 1.0f;
     Particles[i].fade =float((rand()%100)/1500.0f+0.00003f)+Intensity;
   }
}

void ParticleSystem::Draw()
{
      glEnable(GL_BLEND);
      glDepthMask(0);
	  glBindTexture(GL_TEXTURE_2D, texture);

      for (int i = 0; i< MAX_PARTICLES; i++)
      {
                    float x = Particles[i].pX;
                    float y = Particles[i].pY;
                    float z = Particles[i].pZ;

					srand((GetTickCount()/1000)*i);

                    glColor4f(Particles[i].r, Particles[i].g, Particles[i].b, Particles[i].life);
                    glBegin(GL_TRIANGLE_STRIP);				
							glTexCoord2d(1,1); glVertex3f(x+ParticlesSize,y+ParticlesSize,z);
                            glTexCoord2d(0,1); glVertex3f(x-ParticlesSize,y+ParticlesSize,z);
                            glTexCoord2d(1,0); glVertex3f(x+ParticlesSize,y-ParticlesSize,z);
                            glTexCoord2d(0,0); glVertex3f(x-ParticlesSize,y-ParticlesSize,z);
                    glEnd();

                    Particles[i].pX += Particles[i].dX/(SystemSpeed);
                    Particles[i].pY += Particles[i].dY/(SystemSpeed);
                    Particles[i].pZ += Particles[i].dZ/(SystemSpeed);

                    Particles[i].pX += SystemGravity.x;
                    Particles[i].pY += SystemGravity.y;
                    Particles[i].pZ += SystemGravity.z;

                    Particles[i].life -= Particles[i].fade;

                    if (Particles[i].life < 0.0f)
                    {

                         Particles[i].dX = RandomSigne() * float(rand()%100)/1500.0f+0.0003f;
                         Particles[i].dY = RandomSigne() * float(rand()%100)/1500.0f+0.0003f;
                         Particles[i].dZ = RandomSigne() * float(rand()%100)/1500.0f+0.0003f;

                         Particles[i].pX = Emisor.x;
                         Particles[i].pY = Emisor.y;
                         Particles[i].pZ = Emisor.z;

                         if (UseSingleColor)
                         {
                           Particles[i].r = SystemColor.r;
                           Particles[i].g = SystemColor.g;
                           Particles[i].b = SystemColor.b;
                         } else
                         {
                           Particles[i].r = ((float)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
                           Particles[i].g = ((float)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
                           Particles[i].b = ((float)rand() / (RAND_MAX + 1) * (10 - 1) + 1)/10.0f;
                         }

                         Particles[i].life = 1.0f;
                         Particles[i].fade =(float(rand()%100)/1000.0f+0.003f)+Intensity;
                    }

      }
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glDepthMask(1);
      glDisable(GL_BLEND);
}

void ParticleSystem::SetSystemSpeed(float value)
{
   if (value != 0)
     SystemSpeed = value;
}

void ParticleSystem::SetParticlesSize(float value)
{
   if (value != 0)
     ParticlesSize = value;
}

void ParticleSystem::SetIntensity(float value)
{
     Intensity = value;
}

void ParticleSystem::LoadTexture(char *szFilename)
{
	CTextureLoader TL;
	TL.LoadTexture(szFilename, texture);
}
