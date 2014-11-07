#ifndef CDOOR_RED
#define CDOOR_RED
#include "CObject.h"
#include "CDoor.h"
#include "CSound.h"
#include "CPlayer.h"
#include <list>

class CDoor_Red: public CDoor
{
       int current_frame,next_frame;
       int need_key_time;
       int czas_otwarcia;
       unsigned int type;
       float interpol;
       void Need_Key();
  public:
         
       CDoor_Red(int x, int z,int type);
  void Render();      
  void Update();
  bool Trigger(CPlayer &player);
};
#endif
