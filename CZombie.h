#ifndef CZOMBIEE
#define CZOMBIEE
#include "CEnemy.h"
#include "CPlayer.h"
#include "CSound.h"


class CZombie: public CEnemy
{
 private:
float abc;
       int current_frame,next_frame;
       float interpol;
       void Play_Sound();
       CPlayer *p_player;

       int il_akcji;
       int il_dzwiek;
       int kierunek;
       int seria;
       ALuint last_play;
       int opozn_ruch;
       float lx;
       float lz;
       bool los;       
       bool once;
       bool sound_once;
       
       char numer_animacji;
       void Die();
       

 public:

       CZombie(float x,float z);
  void Render();      
  void Update();
  void Trigger(CPlayer &player);
      
};

#endif
