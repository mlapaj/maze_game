#ifndef CGREENKEY
#define CGREENKEY
#include "CItem.h"
#include "CSound.h"


class CGreenKey: public CItem
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

  CGreenKey(float x,float z);
  void Render();      
  void Update();
  void Pick_Up(CPlayer &Player);            
      
      
};
#endif
