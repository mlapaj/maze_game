#ifndef CLOGIC
#define CLOGIC

#include "CMap.h"
#include "CDebug.h"

#include "CEnemy.h"
#include "CObject.h"
#include "CItem.h"




#define C_FRONT 1
#define C_BACK 2
#define C_LEFT 3
#define C_RIGHT 4
#define MAX_MAPS 3


bool Collision(float&,float&);

class CLogic
{
private:
       // nie pamietam do czego to ale wazne
          static float x;
          static float y;
          static int z;
          static int lz;
          static int lr;
          static int Current_Map;
          static bool next_map;
          static char *Maps[MAX_MAPS];
       friend void Time_r(int val); // nasz kolega pomaga nam ogarnac wszystko
       friend bool CEnemy::Check_Aim(float x,float z,float katx,float katy); // pomaga nam ogarnac cele 
       friend bool CItem::Check_Aim(float x,float z); // pomaga nam ogarnac cele        
       CDebug debug;
       CObject *Objects;       
       static CMap Mapa;
       
       
public:
       CLogic();      
  void Perform(void);
  static void Restart();
  static void Next_Level();
  friend void Perform();
  
};




#endif 
