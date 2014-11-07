#include <iostream>
#include <math.h>
#include "CDoor.h"
#include "CLogic.h"
#include "CGraphics.h"
#include <list>

#include <gl/glut.h>
using namespace std;
list<CDoor*> CDoor::ListaDrzwi; // gitara mamy nasza liste :D



void CDoor::Add(CDoor *obiekt)
{
    ListaDrzwi.push_back(obiekt);

}


void CDoor::Doors_Render()
{
list<CDoor*>::iterator it;
for(it = ListaDrzwi.begin() ; it != ListaDrzwi.end() ; ++it)
{      
        glPushMatrix();
        (*it)->Render();
        glPopMatrix();

}
}


void CDoor::Doors_Update()
{
list<CDoor*>::iterator it;
for(it = ListaDrzwi.begin() ; it != ListaDrzwi.end() ; ++it)
{      
        glPushMatrix();
        (*it)->Update();
        glPopMatrix();

}
}


bool CDoor::Doors_Check(float &s_x,float &s_z,float &x,float &z,CObject *obiekt) 
{
     bool flag = false;
// sprawdzamy my czy nie kolidujemy z nim 
// oraz sprawdza poszzewgolny wojownik czy nie koliduje z wojownikiem     
if  ((s_x!=x) || (s_z!=z))
{
list<CDoor*>::iterator it;
for(it = ListaDrzwi.begin() ; it != ListaDrzwi.end() ; ++it) // dla kazdego wroga sprawdz 
{                                                              // czy nie ma kolizj

         float przod=(*it)->x-1.0;
         float tyl=(*it)->x+1.0;
         float lewo=(*it)->z-1.0;         
         float prawo=(*it)->z+1.0;                  
         if ((x<=tyl) && (przod<=x) && (z>=lewo) && (prawo>=z) && ((*it)!=obiekt)) // "gwozdz" funkcji
 {
   
 if ((obiekt->Category)!=CAT_PLAYER){
                                     x=s_x; z=s_z;
                                     }                                   
   
if ((obiekt->Category)==CAT_PLAYER)   
   
{
   // kolizja
   
    CDoor *obj = (CDoor*) *it;
    if ((obj->State!=E_OPENED) || (obj->State==E_OPENING))  // wkoncu chodzimy po denacie
     {
     CPlayer *player = (CPlayer*) obiekt;
     if (obj->State!=E_OPENED) 
     obj->Trigger(*player); // sprawdzamy co koliduje i pozwalamy na ruch w jednym kier
                                       
     flag=true;
  
  
     
     // znow sprawdzamy czy jestesmy przy drzwiach
     
         float przod=(*it)->x-0.6;
         float tyl=(*it)->x+0.6;
         float lewo=(*it)->z-0.6;         
         float prawo=(*it)->z+0.6;                  
         if ((x<=tyl) && (przod<=x) && (z>=lewo) && (prawo>=z) && ((*it)!=obiekt)) // "gwozdz" funkcji
         {
          if (obj->State!=E_OPENED){ 
                                       x=s_x;
                                       z=s_z;

                                     }
          flag=true;   
         }
     
        break;
     }
}
 } // mamy kolizje
}
//if (x==s_x)   CGraphics::TextOut(0,0.01,"Kol z wrogiem");
// przydaloby sie dla wojownika jeszcze na wszelki wypadek sprawdzic czy nie koliduje z nami


if ((obiekt!=NULL) && ((obiekt->Category)!=CAT_PLAYER)) {

         float przod=CGraphics::x-0.4;
         float tyl=CGraphics::x+0.4;
         float lewo=CGraphics::z-0.4;         
         float prawo=CGraphics::z+0.4; 

         if ((x<=tyl) && (przod<=x) && (z>=lewo) && (prawo>=z) && ((*it)!=obiekt)) // "gwozdz" funkcji
 { 


 if ((x+0.1<=tyl) && (przod<=x+0.1)) x=s_x;
 if ((z+0.1>=lewo) && (prawo>=z+0.1)) z=s_z;
   flag=true;
 } // mamy kolizje


}

return flag;
}


}

void CDoor::Doors_Remove()
{

    while (!ListaDrzwi.empty())
  {
    delete (ListaDrzwi.back());
    ListaDrzwi.pop_back();
  }
}
