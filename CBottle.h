#ifndef CBOTTLE
#define CBOTTLE
#include "CItem.h"
#include "CSound.h"


class CBottle: public CItem
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
   static unsigned int num_botles;
   static unsigned int num_picked;
  CBottle(float x,float z);
  CBottle::~CBottle();
  void Render();      
  void Update();
  void Pick_Up(CPlayer &Player);            
      
      
};
#endif
