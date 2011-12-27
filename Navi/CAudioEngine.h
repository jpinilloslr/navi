#ifndef CAudioEngineH
#define CAudioEngineH

#include <al.h>
#include <alc.h>
#include <alut.h>
#include <windows.h>

#define MAX_SOUNDS 150

class CAudioEngine
{
	private:
		ALuint Buffer[MAX_SOUNDS];
		ALuint Source[MAX_SOUNDS];
		bool bPlaying[MAX_SOUNDS];
	public:
		CAudioEngine();
		~CAudioEngine();
		bool LoadFile(int nSource, char *szFile);
		void BindSourceToBuffer(int nSource, int nBuffer);
		void SetSourcePos(int nSource, float x, float y, float z);
		void SetListenerPos(float x, float y, float z);
		void Play(int nSource, bool loop);
		void Stop(int nSource);
		void Pause(int nSource);
		void SetVolume(int nSource, float f);
		void SetPith(int nSource, float f);
		bool IsPlaying(int i)  { if(i < MAX_SOUNDS && i >= 0) return bPlaying[i];}
};

#endif
