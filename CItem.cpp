#include <iostream>
#include <math.h>
#include "CItem.h"
#include "CLogic.h"
#include "CGraphics.h"
#include <list>



#include <gl/glut.h>
using namespace std;
list<CItem*> CItem::ListaPrzedmiotow; // gitara mamy nasza liste :D
unsigned int CItem::picked=0;



unsigned int CItem::Items_Picked()
{
     return CItem::picked;
}

unsigned int CItem::Items_Total()
{
     return ListaPrzedmiotow.size();
}



void CItem::Add(CItem *obiekt)
{
    ListaPrzedmiotow.push_back(obiekt);

   
   
}


void CItem::Items_Render()
{
list<CItem*>::iterator it;
for(it = ListaPrzedmiotow.begin() ; it != ListaPrzedmiotow.end() ; ++it)
{      
        glPushMatrix();
        glTranslatef(-0.5,0,-0.5); 
        (*it)->Render();
        glPopMatrix();

}
}


void CItem::Items_Update()
{
list<CItem*>::iterator it;
for(it = ListaPrzedmiotow.begin() ; it != ListaPrzedmiotow.end() ; ++it)
{      
        glPushMatrix();
        (*it)->Update();
        glPopMatrix();

}
}


bool CItem::Items_Check(float &s_x,float &s_z,float &x,float &z,CObject *obiekt) 
{
     bool flag = false;
// sprawdzamy my czy nie kolidujemy z nim 
// oraz sprawdza poszzewgolny wojownik czy nie koliduje z wojownikiem     
if  ((s_x!=x) || (s_z!=z))
{
list<CItem*>::iterator it;
for(it = ListaPrzedmiotow.begin() ; it != ListaPrzedmiotow.end() ; ++it) // dla kazdego wroga sprawdz 
{                                                              // czy nie ma kolizj

         float przod=(*it)->x-0.3;
         float tyl=(*it)->x+0.3;
         float lewo=(*it)->z-0.3;         
         float prawo=(*it)->z+0.3;   
                        
         if ((x<=tyl-0.5) && (przod-0.5<=x) && (z>=lewo-0.5) && (prawo-0.5>=z) && ((*it)!=obiekt)) // "gwozdz" funkcji
 {
   // wywolujemy teraz procedure Pick_Up();
   // znalezlismy kolizje
   if ((obiekt!=NULL) && ((obiekt->Category)==CAT_PLAYER)){
                     (*it)->Pick_Up((CPlayer &)(*obiekt));
   /// tutaj wiecej nie mozemy nic zrobic
   flag=true;
   }


 } // mamy kolizje
}

return flag;
}


}


void CItem::Items_Remove()
{

    while (!ListaPrzedmiotow.empty())
  {
    delete (ListaPrzedmiotow.back());
    ListaPrzedmiotow.pop_back();
  }
}





