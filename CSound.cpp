#include "CSound.h"
#include <sstream>
#include <sys/stat.h>
#define BUFFER_SIZE     32768       // 32 KB buffers
using namespace std;
   
ALfloat CSound::ListenerPos[3];
ALuint CSound::Source[MAX_SOURCES];
ALuint CSound::source;

static ALfloat ListenerVel[]={0.0,0.0,0.0};
static ALfloat ListenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};
OggVorbis_File  oggStream;     // stream handle
vorbis_info*    vorbisInfo;    // some formatting data
vorbis_comment* vorbisComment; // user comments  
ALenum CSound::format;     // internal format

ALuint  buffer[MAX_SOUNDS];
ALuint BuforOgg; // front and back buffers






bool CSound::FileExists(const char *strFilename) 
{
  struct stat stFileInfo;
  bool blnReturn;
  int intStat;
  intStat = stat(strFilename,&stFileInfo);
  if(intStat == 0) {
    blnReturn = true;
  } else {
    blnReturn = false;
  }  
  return(blnReturn);
}   





void LoadOGG(char *fileName, vector<char> &buffer, ALenum &format, ALsizei &freq)
    {
    int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
    int bitStream;
    long bytes;
    char array[BUFFER_SIZE];                // Local fixed size array
    FILE *f;
    f = fopen(fileName, "rb");
    vorbis_info *pInfo;
    OggVorbis_File oggFile;
    // Try opening the given file
    if (ov_open(f, &oggFile, NULL, 0) != 0)
        {
        cerr << "Blad dekodowania";
        exit(-1);
        }
    // end if


    pInfo = ov_info(&oggFile, -1);
    if (pInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;
    freq = pInfo->rate;
    do
        {
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
        if (bytes < 0)
            {
            ov_clear(&oggFile);
            cerr << "Blad dekodowania ogg";
            exit(-1);
            }
        buffer.insert(buffer.end(), array, array + bytes);
        }
    while (bytes > 0);
    ov_clear(&oggFile);
    }


void CSound::Load_Sounds()
{
  std::cout<<"Laduje dzwieki\n";
  for (int i=0;i<MAX_SOUNDS;i++)
  {      
    std::stringstream filename;
    filename<<"Sounds\\"<<i<<".wav";
    
     ALsizei size,freq;
    ALenum  format;
    ALvoid  *data;
    ALboolean loop;
    if (FileExists(filename.str().c_str())) 
       {
       int error;
       alGetError();        
       buffer[i]=0;
       alGenBuffers(1, &buffer[i]);
       if ((error = alGetError()) != AL_NO_ERROR)
       {
       std::cout<<"error";
       system("pause");
       exit(0);
       }
       std::cout<<"Wczytuje:"<<filename.str()<<"\n";
       char *nazwa = new char[strlen(filename.str().c_str())];
       strcpy(nazwa,filename.str().c_str());
       std::cout<<"Nazwa:"<<nazwa;
       alutLoadWAVFile(nazwa,&format,&data,&size,&freq,&loop);
       std::cout<<"BUFOR:"<<buffer[i];
       alBufferData(buffer[i],format,data,size,freq);
       alutUnloadWAV(format,data,size,freq);
       }
    filename.str(""); // czyscimy   e


   } 
  
// nasza pozycja  
        alListenerfv(AL_POSITION,ListenerPos);
        alListenerfv(AL_VELOCITY,ListenerVel);
        alListenerfv(AL_ORIENTATION,ListenerOri);

  for (int i=0;i<MAX_SOURCES;i++){
        
       	alGetError();
    	alGenSources(1, &Source[i]);

    	if(alGetError() != AL_NO_ERROR) 
    	{
        	printf("- Error creating sources !!\n");
        	system("Pause");
        	exit(2);
    	}
      }
    // Create sound buffer and source

   ALint state;                            // The state of the sound source
    ALuint bufferID;                        // The OpenAL sound buffer ID
    ALuint sourceID;                        // The OpenAL sound source
    ALenum format;                          // The sound data format
    ALsizei freq;                           // The frequency of the sound data
    vector<char> bufferData;                // The sound buffer data from file


    alGenBuffers(1, &bufferID);
    alGenSources(1, &sourceID);

    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(sourceID, AL_POSITION, 0.0f, 0.0f, 0.0f);
    LoadOGG("music\\maze.ogg", bufferData, format, freq);
    alBufferData(bufferID, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);
    alSourcei(sourceID, AL_BUFFER, bufferID);

    alSourcePlay(sourceID);

}


void   CSound::Change_Params(ALuint source,ALfloat sourcePos[3],ALfloat sourceVel[3],ALboolean looping)
     {

        alSourcef(source, AL_PITCH, 1.0f);
    	alSourcef(source, AL_GAIN, 1.0f);
    	alSourcefv(source, AL_POSITION, sourcePos);
    	alSourcefv(source, AL_VELOCITY, sourceVel);
    	alSourcei(source, AL_LOOPING, looping);
    	
     }

void   CSound::Change_Sound(ALuint source,int num)
     {

    	alSourcei(source, AL_BUFFER,buffer[num]);
    	
     }




void   CSound::Listener_Pos(float pos[3],float orientation[6])
{
   
   alListenerfv(AL_POSITION,pos);
   alListenerfv(AL_ORIENTATION,orientation);   
}



bool CSound::Is_Playing(int num)
{
    ALenum state;    
    alGetSourcei(Source[num], AL_SOURCE_STATE, &state);    
    return (state == AL_PLAYING);
}

ALuint   CSound::Play_Sound(int soundnum,float SoundPos[3],float SoundVel[3])
{
 
  for (int i=0;i<MAX_SOURCES;i++){
  if (!Is_Playing(i)) {
                      Change_Sound(Source[i],soundnum);
                      Change_Params(Source[i],SoundPos,SoundVel,false);
                      alSourcePlay(Source[i]);
                      return(Source[i]);
                      }
  }
// mamy nasze i - numer kanalu

}
