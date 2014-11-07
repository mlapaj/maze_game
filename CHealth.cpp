#include "CHealth.h"
#include "CGraphics.h"
#include <iostream>

CHealth::CHealth(float x_w,float z_w):CItem()
{
x=x_w;
z=z_w;
il_akcji=0;
kierunek=0;  // 0 stoi
numer_animacji=0;
kat=0;
once=false;
sound_once=false; // do odtwarzania tylko raz np e_dying
interpol=1;     // w przypadku obiektu z jedna klatka
}


void CHealth::Render()
{
     
   glTranslatef(x,-0.25,z);     
   glScalef(0.5f,0.5f,0.5f);
    char *tekst;
    ///////////// moze mozna by to lepiej rozegrac ale styka to
    switch(numer_animacji){
                           case 0: tekst="Frame"; break;                        
                           default: tekst="Frame"; break;
                           }
   glRotatef((kat*360)/(2*3.14),0,1,0);  
//   glColor3f(0,1,0);
   if (State!=E_PICKED_UP) CGraphics::DisplayInterpolatedMd2(8,tekst,current_frame,next_frame,interpol);
}


void CHealth::Update()
{

     numer_animacji=0;
     interpol=1;  // koniec jesli koniec animacji - w tym przypadku najlepiej dziala
     // do poprawy
     kat=kat+0.1;

}


void CHealth::Pick_Up(CPlayer &Player) {
if ((State!=E_PICKED_UP)) {
                            if (Player.Health<80) {Player.Health+=20; State=E_PICKED_UP;}
                            if ((Player.Health>80) && (Player.Health<100)) {Player.Health=100; State=E_PICKED_UP;}
                            if (Player.Health==100) Player.Health=100;                            

                            }
Play_Sound(); // bo to sie nie zmienilo
}




void CHealth::Play_Sound()
{


   if (State==E_PICKED_UP){
   if (sound_once==false){
   SoundPos[0]=x;SoundPos[1]=0.5f;SoundPos[2]=z;
   SoundVel[0]=0.0;SoundVel[1]=0.0;SoundVel[2]=0.0;                          
   CSound::Play_Sound(5,SoundPos,SoundVel);
   sound_once=true;
   } 
   }





}



