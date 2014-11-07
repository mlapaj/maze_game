#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "CMap.h"
#include "CZombie.h"
#include "CGraphics.h"



using namespace std;

CZombie::CZombie(float x,float z):CEnemy()
{
abc=0;
last_play=0;
los=false;
p_player=0;
CZombie::x=x;
CZombie::z=z;
il_akcji=0;
kierunek=0;  // 0 stoi
interpol=1;     // w przypadku obiektu z jedna klatka
current_frame=0;
next_frame=0;
numer_animacji=0;
State=E_WALKING;
kat=0;
once=false;
ALuint last_sound;
sound_once=false; // do odtwarzania tylko raz np e_dying
// wczytujemy dzwieki
// dla kazdego zombie jedno zrodlo i przypisz wspolzedne




}

void CZombie::Render()
{
   // przywracamy wlasciwy kat
    glTranslatef(x,-0.3,z);  
    int modnum =0;
    char *tekst;
    ///////////// moze mozna by to lepiej rozegrac ale styka to
    switch(numer_animacji){
                           case 0: tekst="stand"; break;
                           case 1: tekst="walk"; break;
                           case 2: {tekst="die"; modnum=5; }break;                           
                           case 3: {tekst="die"; modnum=5; } break;  
                           case 4: tekst="attacka"; break;                                                    
                           case 5: tekst="attackb"; break;                                                    
                           case 6: tekst="attackc"; break;                                                    
                           default: tekst="stand"; break;
                           }
    glRotatef((kat*360)/(2*3.14),0,1,0);  
if (CGraphics::DisplayInterpolatedMd2(modnum,tekst,current_frame,next_frame,interpol))
{
// czyli tutaj wykonal raz animacje wiec 

if (State==E_DYING){ State=E_DIED;  once=false;}                                                                                
}

}


void CZombie::Update()
{

if ((p_player!=NULL) && (p_player->Is_Dead()==true)) {State=E_WALKING; numer_animacji=1;}

// akcja dla zombiego ktory cie zauwazyl... lepiej chwyc sie mocno 
// za klawiature :-) heehehe
if (((State==E_TRIGGERED) || (State==E_SHOOTING))  && (p_player!=NULL))
   {
      
       //
       if (State==E_TRIGGERED) {opozn_ruch=0; il_akcji=20;} // ustawia akcje raz
       float odleglosc=sqrt(Kwadrat(p_player->Get_X()-x)+Kwadrat(p_player->Get_Z()-z));                    
       if (odleglosc>5) State=E_WALKING; else State=E_SHOOTING;
       
       
   
   }

if ((State==E_SHOOTING) && (p_player!=NULL))
{
  // strzela potwor
  
  
  // tu bedzie ustawial do strzelania
  float i=0;
  float j=0;                    
  float stare_z=z;                 
  float stare_x=x;
  float nowe_z=0;
  float nowe_x=0;

    // mamy lx

   opozn_ruch--;
   if ((il_akcji>20) && (il_akcji<100) && (opozn_ruch<=0)){
   opozn_ruch=50;                                    
   float odleglosc=sqrt(Kwadrat(p_player->Get_X()-x)+Kwadrat(p_player->Get_Z()-z));
  float angle_sin=((p_player->Get_X()-stare_x)/odleglosc);
  float angle_cos=((p_player->Get_Z()-stare_z)/odleglosc);
  float s_kat = asin((p_player->Get_X()-stare_x)/odleglosc);
  
  if ((angle_sin>=0) && (angle_sin<1) && (angle_cos>=0) && (angle_cos<1))
  {
   kat=3.14+s_kat;
           } // CZYLI OD ZERO DO 90 
  
  else if ((angle_sin>=0) && (angle_sin<1) && (angle_cos>=-1) && (angle_cos<0))
  {

  kat=2*3.14-s_kat;

  }  // OD 90 DO 180
  
  else if ((angle_sin>=-1) && (angle_sin<0) && (angle_cos>=-1) && (angle_cos<0))
  {
//  abc=abc+0.1;
//  std::cout<<"ABC:"<<abc<<"!!!\n";
  kat=-s_kat;

  }  // OD 180 DO 270 DODAJEMY  PI/2
  
  else if ((angle_sin>=-1) && (angle_sin<0) && (angle_cos>=0) && (angle_cos<1))
  {
  kat=s_kat+3.14;
  }  
                   
 }



  if ((il_akcji>90) && (il_akcji<=100)){numer_animacji=4;   interpol=interpol+0.1; }
  if (il_akcji==90) {
                     SoundPos[0]=x;SoundPos[1]=0.5f;SoundPos[2]=z;
                     SoundVel[0]=0.0;SoundVel[1]=0.0;SoundVel[2]=0.0;
                     last_play=CSound::Play_Sound(13,SoundPos,SoundVel);
                     seria=10;  
                    }
  if ((il_akcji>20) && (il_akcji<=90)){ if (seria==0){ p_player->Check_Aim(x,z,kat); seria=10;} seria=seria-1; numer_animacji=5;  interpol=interpol+0.5;  }  
  if ((il_akcji>17) && (il_akcji<=20)){  numer_animacji=6;   interpol=interpol+0.1; }    




  if ((il_akcji>0)  && (il_akcji<17))
  {
     
{  // poczatek E_WALKING


if (los==false){
                                    /// losuj raz
                    kierunek = rand() % 4;
                    numer_animacji=1; 
                 //   kat= rand() % 3;
                    lx = sin(kat);
                    lz = cos(kat);	   // losujemy nowy kat narazie
                    los=true; // mamy los
                }

if (kierunek==0) {numer_animacji=0;}
else {numer_animacji=1; i=-0.1;}
nowe_x = stare_x + i*(lx)*0.2;
nowe_z = stare_z + i*(lz)*0.2;
CMap::Check(stare_x,stare_z,nowe_x,nowe_z); // kolizja przywraca stara wartosc
CEnemy::Enemies_Check(stare_x,stare_z,nowe_x,nowe_z,this);
if ((kierunek!=0) && ((stare_x==nowe_x) || (stare_z==nowe_z))) // jesli sie oczywiscie ruszamy
{
// czyli mamy kolizje
// zmienmy kat
 kat= kat+3.14;
 lx = sin(kat);
 lz = cos(kat);	    
}
z=nowe_z;
x=nowe_x;
// kontrolujemy co sie dzieje
interpol=interpol+0.15; 
} // koniec dla walking               
                    
                    
                    
                    
  }
  if (il_akcji==0){ los=false; il_akcji=100;  }

  
  il_akcji--;
}














// uaktualnij pozycje
Play_Sound();
// zakladamy ze martwy zombie to martwy zombie
// jesli zmienilismy stan na E_DYING to umierajmy do jasnej ....  !
if (State==E_DYING){
if (once==false) {


interpol=0;
current_frame=0;
next_frame=0;
once=true;
CGraphics::Md2_Repeated=false;
}
numer_animacji=2;

interpol=interpol+0.1;  // koniec jesli koniec animacji
return;
}
if (State==E_DIED) return;

float stare_z=z;                 
float stare_x=x;
float nowe_z=0;
float nowe_x=0;
float lx=sin(kat);
float lz=cos(kat);
float i=0;
float j=0;






if (State==E_WALKING)
{  // poczatek E_WALKING
if (il_akcji==0) {
                 il_akcji = rand() % 300; // losuje nowa dlugosc
                 // losuje kierunek
                 kierunek = rand() % 4;
                 numer_animacji=1; 
                 kat= rand() % 3;
                 lx = sin(kat);
                 lz = cos(kat);	    	
                 }

if (kierunek==0) {numer_animacji=0;}
else {numer_animacji=1; i=-0.1;}
nowe_x = stare_x + i*(lx)*0.2;
nowe_z = stare_z + i*(lz)*0.2;
CMap::Check(stare_x,stare_z,nowe_x,nowe_z); // kolizja przywraca stara wartosc
CEnemy::Enemies_Check(stare_x,stare_z,nowe_x,nowe_z,this);
if ((kierunek!=0) && ((stare_x==nowe_x) || (stare_z==nowe_z))) // jesli sie oczywiscie ruszamy
{
// czyli mamy kolizje
// zmienmy kat
 kat= kat+3.14;
 lx = sin(kat);
 lz = cos(kat);	    
}
z=nowe_z;
x=nowe_x;
// kontrolujemy co sie dzieje
interpol=interpol+0.1; 
il_akcji--;
} // koniec dla walking

}




void CZombie::Die()
{
CEnemy::Die();
if((State!=E_DIED) && (State!=E_DYING)) {current_frame=0; next_frame=0; // ustawiamy ramke od nowa;9
interpol=0;}
CSound::stop(last_play);
}



void CZombie::Play_Sound()
{
   SoundPos[0]=x;SoundPos[1]=0.5f;SoundPos[2]=z;
   SoundVel[0]=0.0;SoundVel[1]=0.0;SoundVel[2]=0.0;

   // plays sound
   if (State==E_DYING){
   
   if (sound_once==false){
   srand( (unsigned)time( NULL ) ); // "wymieszaj" 
   int losuj = rand() % 4;
   int soundnum=1;
   switch (losuj)
      {
          //
          case 0: soundnum=2; break;
          case 1: soundnum=3; break;
          case 2: soundnum=4; break;          
          case 3: soundnum=6; break;                    
          default: soundnum=1; break;
      }
   
   CSound::Play_Sound(soundnum,SoundPos,SoundVel);
   sound_once=true;
   } // czyli wykona tylko raz      
   }



   // plays sound
   if (State==E_WALKING)
   {
   
  
   
    if (il_dzwiek<=0)
    {
        il_dzwiek = rand() % 500; // losuje nowa dlugosc
        int soundnum=1;
        srand( (unsigned)time( NULL ) ); // "wymieszaj" 
        int losuj = rand() % 2;
        switch (losuj)
        {
          case 0: soundnum=0; break;
          case 1: soundnum=1; break;
          default: soundnum=0; break;
        } 
             
   CSound::Play_Sound(soundnum,SoundPos,SoundVel);
    }
   il_dzwiek--;
   }

}

void CZombie::Trigger(CPlayer &player)
{
p_player=&player;
if (player.Is_Dead()==true) return; // martwy
if (State==E_WALKING) {                      
State=E_TRIGGERED;
srand( (unsigned)time( NULL ) ); // "wymieszaj" 
int losuj = rand() % 4;
int soundnum=1;
switch (losuj)
      {
          //
          case 0: soundnum=11; break;
          case 1: soundnum=12; break;
          default: soundnum=11; break;
      }
   
 CSound::Play_Sound(soundnum,SoundPos,SoundVel);
}




}


