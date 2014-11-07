#ifndef CSOUND
#define CSOUND
#include <GL/glut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>


#include "AL/al.h"
#include "AL/alut.h"
#include <vorbis/vorbisfile.h>
#include <cstdio>
#include <iostream>
#include <vector>


#define MAX_SOUNDS 255
#define MAX_SOURCES 10

 
class CSound
{
 private:


 static ALfloat ListenerPos[3];
 static bool FileExists(const char *strFilename);  // pomocnicza
 static ALuint Source[MAX_SOURCES];
 public:
      
 
 static ALenum format;     // internal format
 static ALuint source;



 static void Load_Sounds();   
 static bool CSound::Is_Playing(int num);
 static void   Change_Params(ALuint source,ALfloat sourcePos[3],ALfloat source0Vel[3],ALboolean looping);
 static void   CSound::Listener_Pos(float pos[3],float orientation[6]);
 static void   CSound::Change_Sound(ALuint source,int num);      
 static ALuint CSound::Play_Sound(int soundnum,float SoundPos[],float SoundVel[]);
 static bool CSound::update();
 static bool CSound::stream(ALuint buffer);
 static void CSound::display();
 static bool CSound::playback();
 static bool CSound::playing();
 static bool CSound::stop(ALuint source){alSourceStop(source);}
};



#endif
