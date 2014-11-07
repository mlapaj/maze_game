#ifndef CHEALTH
#define CHEALTH
#include "CItem.h"
#include "CSound.h"


class CHealth: public CItem
{
 private:

       int current_frame,next_frame;
       void Play_Sound();
       float interpol;    
       int il_akcji;
       int il_dzwiek;
       int kierunek;
       bool once;
       bool sound_once;              
       char numer_animacji;
       void Die();
       

 public:

  CHealth(float x,float z);
  void Render();      
  void Update();
  void Pick_Up(CPlayer &Player);            
      
      
};
#endif
