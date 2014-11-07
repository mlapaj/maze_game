#include "CBottle.h"
#include "CGraphics.h"
#include <iostream>

unsigned int CBottle::num_botles =0;
unsigned int CBottle::num_picked =0;

CBottle::CBottle(float x_w,float z_w):CItem()
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
num_botles+=1;
}

CBottle::~CBottle()
{
num_botles-=1;
num_picked=0;
}                    


void CBottle::Render()
{
   glTranslatef(x,-0.5,z);     
   glScalef(2.0f,2.0f,2.0f);
    char *tekst;
    ///////////// moze mozna by to lepiej rozegrac ale styka to
    switch(numer_animacji){
                           case 0: tekst="Frame"; break;                        
                           default: tekst="Frame"; break;
                           }
   glRotatef((kat*360)/(2*3.14),0,1,0);  
   if (State!=E_PICKED_UP) CGraphics::DisplayInterpolatedMd2(1,tekst,current_frame,next_frame,interpol);
}


void CBottle::Update()
{

     numer_animacji=0;
     interpol=1;  // koniec jesli koniec animacji - w tym przypadku najlepiej dziala
     // do poprawy
     kat=kat+0.1;

}


void CBottle::Pick_Up(CPlayer &Player) {
if ((State!=E_PICKED_UP)) {
                            State=E_PICKED_UP;
                            picked+=1;
                            num_picked+=1;
                            }
Play_Sound(); // bo to sie nie zmienilo
}

 


void CBottle::Play_Sound()
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



