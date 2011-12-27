#pragma hdrstop
#include "CAudioEngine.h"

#pragma comment(lib, "openal32.lib")
#pragma comment(lib, "alut.lib")

CAudioEngine::CAudioEngine()
{
	alutInit(NULL, NULL);
	alGenBuffers(MAX_SOUNDS, Buffer);
	alGenSources(MAX_SOUNDS, Source);

	for(int i=0; i<MAX_SOUNDS; i++)
		bPlaying[i] = false;

	alEnable(AL_DISTANCE_MODEL);
	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

	//alListenerf(AL_GAIN, 1.0f);
}

CAudioEngine::~CAudioEngine()
{
	alDeleteBuffers(MAX_SOUNDS, Buffer);
	alDeleteSources(MAX_SOUNDS, Source);
	alutExit();
}

bool CAudioEngine::LoadFile(int nSource, char *szFile)
{
    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
	ALboolean loop;

	// Load wav data into a buffer.

	alutLoadWAVFile(szFile, &format, &data, &size, &freq, &loop);
	alBufferData(Buffer[nSource], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alSourcei (Source[nSource], AL_BUFFER,   Buffer[nSource]);

	alSourcef (Source[nSource], AL_PITCH, 1.0f);
	alSourcef (Source[nSource], AL_GAIN, 1.0f);
	//alSourcef (Source[nSource], AL_MAX_DISTANCE, 1000.0f);
	alSourcef (Source[nSource], AL_REFERENCE_DISTANCE, 25.0f);
	//alSourcef (Source[nSource], AL_ROLLOFF_FACTOR, 1.0f);

	// Do another error check and return.
	if (alGetError() == AL_NO_ERROR)
		return AL_TRUE;

	return AL_FALSE;
}

void CAudioEngine::BindSourceToBuffer(int nSource, int nBuffer)
{
	alSourcei (Source[nSource], AL_BUFFER,   Buffer[nBuffer]);
	alSourcef (Source[nSource], AL_GAIN, 1.0f);
	alSourcef (Source[nSource], AL_REFERENCE_DISTANCE, 25.0f);
}

void CAudioEngine::SetSourcePos(int nSource, float x, float y, float z)
{
	float f[3];
	f[0] = x; f[1] = y; f[2] = z;

	alSourcefv(Source[nSource], AL_POSITION, f);
}

void CAudioEngine::SetListenerPos(float x, float y, float z)
{
	float f[3];
	f[0] = x; f[1] = y; f[2] = z;

	alListenerfv(AL_POSITION, f);
}

void CAudioEngine::Play(int nSource, bool loop)
{
	int State;
	alGetSourcei(Source[nSource], AL_SOURCE_STATE, &State);

	if(State != AL_PLAYING)
	{
		alSourcePlay(Source[nSource]);
		alSourcei (Source[nSource], AL_LOOPING, loop);
		bPlaying[nSource] = true;
	}
}

void CAudioEngine::Stop(int nSource)
{
	alSourceStop(Source[nSource]);
	bPlaying[nSource] = false;
}

void CAudioEngine::Pause(int nSource)
{
	alSourcePause(Source[nSource]);
	bPlaying[nSource] = false;
}

void CAudioEngine::SetVolume(int nSource, float f)
{
	alSourcef (Source[nSource], AL_GAIN, f);
}

void CAudioEngine::SetPith(int nSource, float f)
{
	alSourcef(Source[nSource], AL_PITCH, f);
}
