#include <iostream>
#include <math.h>
#include "CEnemy.h"
#include "CDoor.h"
#include "CLogic.h"
#include "CGraphics.h"
#include <list>

#include <gl/glut.h>
using namespace std;
list<CEnemy*> CEnemy::ListaWrogow; // gitara mamy nasza liste :D
unsigned int CEnemy::killed=0;

unsigned int CEnemy::Enemies_Killed()
{
     return CEnemy::killed;
}

unsigned int CEnemy::Enemies_Total()
{
     return ListaWrogow.size()-1;
}

void CEnemy::Add(CEnemy *obiekt)
{
    ListaWrogow.push_back(obiekt);

}


void CEnemy::Enemies_Render()
{
list<CEnemy*>::iterator it;
for(it = ListaWrogow.begin() ; it != ListaWrogow.end() ; ++it)
{      
        glPushMatrix();
//        glTranslatef(-0.5,0,-0.5); 
        (*it)->Render();
        glPopMatrix();

}
}


void CEnemy::Enemies_Update()
{
list<CEnemy*>::iterator it;
for(it = ListaWrogow.begin() ; it != ListaWrogow.end() ; ++it)
{      
        glPushMatrix();
        (*it)->Update();
        glPopMatrix();

}
}


bool CEnemy::Enemies_Check(float &s_x,float &s_z,float &x,float &z,CObject *obiekt) 
{
     
     bool flag = false;

// sprawdzamy my czy nie kolidujemy z nim 
// oraz sprawdza poszzewgolny wojownik czy nie koliduje z wojownikiem     
if  ((s_x!=x) || (s_z!=z))
{
list<CEnemy*>::iterator it;


if ((obiekt!=NULL) && ((obiekt->Category)==CAT_PLAYER)) { // trigger dla gracza
for(it = ListaWrogow.begin() ; it != ListaWrogow.end() ; ++it) // dla kazdego wroga sprawdz 
{                                                              // czy nie ma kolizj

         float przod=(*it)->x-2.5;
         float tyl=(*it)->x+2.5;
         float lewo=(*it)->z-2.5;         
         float prawo=(*it)->z+2.5;                  
         if ((x<=tyl) && (przod<=x) && (z>=lewo) && (prawo>=z) && ((*it)!=obiekt)) // "gwozdz" funkcji
 {
   if ((*it)->State!=E_DIED)  // wkoncu chodzimy po denacie
     {
     if ((1.5)<CMap::Od_Sciany(1.5)) {                                               
                                               CPlayer *player = (CPlayer*) obiekt;
                                               (*it)->Trigger(*player);
                                               }
     
     }
     
 } // mamy kolizje
}
}


for(it = ListaWrogow.begin() ; it != ListaWrogow.end() ; ++it) // dla kazdego wroga sprawdz 
{                                                              // czy nie ma kolizj

         float przod=(*it)->x-0.3;
         float tyl=(*it)->x+0.3;
         float lewo=(*it)->z-0.3;         
         float prawo=(*it)->z+0.3;                  
         if ((x<=tyl) && (przod<=x) && (z>=lewo) && (prawo>=z) && ((*it)!=obiekt)) // "gwozdz" funkcji
 {
   if ((*it)->State!=E_DIED)  // wkoncu chodzimy po denacie
     {
     x=s_x; z=s_z; break;
     flag=true;
     }
     
 } // mamy kolizje
}


if ((obiekt!=NULL) && ((obiekt->Category)!=CAT_PLAYER)) {

         float przod=CGraphics::x-0.3;
         float tyl=CGraphics::x+0.3;
         float lewo=CGraphics::z-0.3;         
         float prawo=CGraphics::z+0.3; 

         if ((x<=tyl) && (przod<=x) && (z>=lewo) && (prawo>=z) && ((*it)!=obiekt)) // "gwozdz" funkcji
 { 
   x=s_x; z=s_z;
   flag=true;
 } // mamy kolizje


// sprawdzamy kolizje z drzwiami
if ((obiekt!=NULL) && ((obiekt->Category)!=CAT_ENEMY)) {CDoor::Doors_Check(s_x,s_z,x,z,obiekt);}
}

return flag;
}


}




bool CEnemy::Check_Aim(float x,float z,float katx,float katy) 
{
//     
    

list<CEnemy*>::iterator it;
for(it = ListaWrogow.begin() ; it != ListaWrogow.end() ; ++it)
{      

   float stary_tmp_x=x;
   float stary_tmp_z=x;


  float tmp_x = x; // pozycja x wroga 
  float tmp_z = z; // pozycja z wroga
  float tmp_y = CGraphics::y; // pozycja z wroga
  float lx = sin(katx);
  float lz = -cos(katx);	    	
  float	ly = -sin(katy);	// sprawdza kosinus dla y



// odleglosc troche brzydko bo pierwiastki itp ale kij z tym

    float odleglosc = 

sqrt(Kwadrat((CGraphics::x-(*it)->x))+Kwadrat((CGraphics::z-(*it)->z)));
    float j=odleglosc-1;
bool flag=false;    


    j=odleglosc-1;
    tmp_x = tmp_x + j*(lx);
    tmp_z = tmp_z + j*(lz);
    tmp_y = tmp_y + j*(ly); // mamy odleglosci

    
    float nowy_tmp_x=tmp_x+lx;
    float nowy_tmp_z=tmp_z+lz;
    float nowy_tmp_y=tmp_y+ly-0.2;
    
    float dx=nowy_tmp_x+0.05f;
    float dz=nowy_tmp_z+0.05f;

  
  // sprawdzmy kolizje
         float przod=(*it)->x-0.3;
         float tyl=(*it)->x+0.3;
         float lewo=(*it)->z-0.3;         
         float prawo=(*it)->z+0.3;                  
         
   if ((nowy_tmp_x<=tyl) && (przod<=nowy_tmp_x) && 
       (nowy_tmp_z>=lewo) && (prawo>=nowy_tmp_z) &&
       (nowy_tmp_y>0) && (nowy_tmp_y<0.5)       
       ) // "gwozdz" funkcji
    {
     // robimy kolizje w Y

     // mamy kolizje
//     std:cout<<"Od wroga"<<odleglosc<<" od sciany"<<CMap::Od_Sciany(odleglosc);
     if (odleglosc<CMap::Od_Sciany(odleglosc)) (*it)->Die();  // sciana dalej
     }
}



}


void CEnemy::Enemies_Remove()
{

    while (!ListaWrogow.empty())
  {
    delete (ListaWrogow.back());
    ListaWrogow.pop_back();
  }
}
