#ifndef CDOOR_SILVER
#define CDOOR_SILVER
#include "CObject.h"
#include "CDoor.h"
#include "CSound.h"
#include "CPlayer.h"
#include <list>

class CDoor_Silver: public CDoor
{
       int current_frame,next_frame;
       int czas_otwarcia;
       unsigned int type;
       float interpol;
  public:
         
       CDoor_Silver(int x, int z,int type);
  void Render();      
  void Update();
  bool Trigger(CPlayer &player);
};
#endif
