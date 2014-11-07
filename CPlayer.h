#ifndef CPLAYER
#define CPLAYER
#include "CObject.h"
#include <gl/glut.h>
class CPlayer: public CObject
{
 private:
       enum E_STATE { E_ALIVE,E_DEAD };
       E_STATE State;
       int current_frame,next_frame;
       void Play_Sound();
       float interpol;
       int il_akcji;
       int zz,lr;  // do obslugi   ]
       float zx,zy;  //  klawiatury  ]    
       unsigned int il_dzwiek;
       int message_time;
       unsigned int message_id;
       bool draw_red_screen;
       
       // cechy playera
       unsigned int Ammo;

       bool red_key;
       bool blue_key;
       bool green_key;       
       
       int kierunek;
       float position[3];
       float SoundVel[3];       
       float orientation[6];
 
       bool once;
       bool sound_once;

       char numer_animacji;
       void Ikona();
       void Celownik();
       void Die();
       void Bron();
       void Butelka();
       void Wrog();
       void Ammon();
       void Red_Screen();
       void Numer(int numer,float x, float y);
 public:
       float Health; 
       CPlayer(float x,float z);
  void Render();      
  void Rotate();
  void Update();
  bool Got_Red_Key(){ return red_key;}
  bool Got_Blue_Key(){ return blue_key;}
  bool Got_Green_Key(){ return green_key;}
  bool Set_Red_Key(){ red_key=true;}
  bool Set_Blue_Key(){ blue_key=true;}
  bool Set_Green_Key(){ green_key=true;}
  void CPlayer::Game_Over();
  float Get_X(){ return x;}
  float Get_Z(){ return z;}
  float Get_Angle() { return zx;}
  float Is_Dead(){ if (State==E_DEAD) return true; else return false;}  
  void Draw_Key();
  void Hit(float odleglosc);
  void Restart();

  bool Is_Exit_Possible();
  void Need_Red_Key();
  void Need_Green_Key();
  void Need_Blue_Key();  
  void AddAmmo(int num){Ammo+=num;}
  bool Check_Aim(float x,float z,float katx); 
  friend bool Collision(float &x,float &z,CObject *obiekt);    
};

bool Collision(float &x,float &z,CObject *obiekt);
#endif
