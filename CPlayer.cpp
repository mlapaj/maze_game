#include "CPlayer.h"
#include "CGraphics.h"
#include "CBottle.h"
#include "CInput.h"
#include "CMap.h"
#include "CLogic.h"
#include "Math.h"
#include "CEnemy.h"
#include "CItem.h"
#include <sstream>
#include <iostream>

CPlayer::CPlayer(float x,float z)
{
State=E_ALIVE;
zy=0;
Health=100;
                        red_key=false;
                        blue_key=false;                        
                        green_key=false;  
Category=CAT_PLAYER; // obiekt nalezy do kategorii Player
position[0]=CGraphics::x;
position[1]=CGraphics::y;
position[2]=CGraphics::z;
SoundVel[0]=0;
SoundVel[1]=0;
SoundVel[2]=0;
orientation[0]=CGraphics::x;
orientation[1]=CGraphics::y;
orientation[2]=CGraphics::z;
orientation[3]=CGraphics::x+CGraphics::lx;
orientation[4]=CGraphics::y+CGraphics::ly;
orientation[5]=CGraphics::z+CGraphics::lz;
il_dzwiek=0;
message_time=0;
CSound::CSound::Listener_Pos(position,orientation);
il_akcji=0;
kierunek=0;  // 0 stoi
numer_animacji=0;
kat=0;
once=false;
sound_once=false; // do odtwarzania tylko raz np e_dying
Ammo=10; //  bede tak laskawy i dam gosciowi 10 ammo
}


void CPlayer::Ikona()
{
   glClear(GL_DEPTH_BUFFER_BIT);

   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   // losujemy ikone

   if (il_zmiana<=0)
    {
        il_zmiana = rand() % 50; // losuje nowa dlugosc
        
        srand( (unsigned)time( NULL ) ); // "wymieszaj" 
        int losuj = rand() % 3;
        switch (losuj)
        {
          case 0: texnum=100; break;
          case 1: texnum=101; break;
          case 2: texnum=102; break;
          default: texnum=100; break;
        }              
    }
   il_zmiana--;
   
   
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(texnum));
   glTranslatef(-0.0,-0.14,-0.15);
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.02);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.02);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );
 
}




void CPlayer::Celownik()
{
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glLoadIdentity();  
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(103)); // celownik
   glTranslatef(-0.01,-0.01,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.02);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.02);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );
    
}



void CPlayer::Butelka()
{
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glLoadIdentity();  
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(109)); // celownik
   glTranslatef(-0.14,-0.14,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.02);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.02);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );
    
}


void CPlayer::Wrog()
{
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glLoadIdentity();  
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(108)); // celownik
   glTranslatef(-0.20,-0.14,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.02);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.02);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );
    
}


void CPlayer::Ammon()
{
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glLoadIdentity();  
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(107)); // celownik
   glTranslatef(-0.06,-0.14,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.02);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.02);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );
    
}


void CPlayer::Red_Screen()
{
  
   static int i=0;
   if ((draw_red_screen==true) && (i>20)) i=0; // czyli ktos ustawil flage draw_red
   if (i<10){
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glDisable(GL_TEXTURE_2D);
   glLoadIdentity();  
   glTranslatef(-0.5,-0.5,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor4f(1.0f,0.0f,0.0f,float(i)/float(10));   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,1);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,1,1);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,1,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );
   } 



   if ((i>10) && (i<20)){
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glDisable(GL_TEXTURE_2D);
   glLoadIdentity();  
   glTranslatef(-0.5,-0.5,float(20-i)/float(20)); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor4f(1.0f,0.0f,0.0f,0.5f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,1);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,1,1);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,1,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );
   } 
   
   i+=1;
   if (i>20)  draw_red_screen=false;

  


}



void CPlayer::Bron()
{
    glRotatef(4.0,0,1,0);  
    glScalef(0.3,0.3,0.3);
    glTranslatef(0.19,-0.52,-0.1);  
      
    char *tekst;
    ///////////// moze mozna by to lepiej rozegrac ale styka to
    switch(numer_animacji){
                           case 0: tekst="stationary"; break;
                           case 1: tekst="sway"; break;
                           case 2: tekst="pow"; break;
                           default: tekst="sway"; break;
                           }

if (CGraphics::DisplayInterpolatedMd2(10,tekst,current_frame,next_frame,interpol))
{
// czyli tutaj wykonal raz animacje wiec 

}

}

void CPlayer::Numer(int numer,float x, float y)
{
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glPushMatrix();


   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   // zrobimy troche brzydko ale dzialac bedzie

   char napis[50]; // maksymalna dlugosc
   itoa(numer,napis,10);
   int texnum=0;
   for (int i=0;i<strlen(napis);i++){

   switch(napis[i])
   {
    case '0':  texnum=110; break;
    case '1':  texnum=111; break;
    case '2':  texnum=112; break;
    case '3':  texnum=113; break;
    case '4':  texnum=114; break;
    case '5':  texnum=115; break;
    case '6':  texnum=116; break;
    case '7':  texnum=117; break;
    case '8':  texnum=118; break;
    case '9':  texnum=119; break;
    default:  texnum=119; break;
   }
   glLoadIdentity();  
   glTranslatef(x+0.01*i,-0.01+y,-0.1); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(texnum)); // celownik
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.01);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.01,0.01);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.01,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);

   glEnd();
       
   }

   glPopMatrix(); 
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );

}


void CPlayer::Render()
{  


   glLoadIdentity();
   Bron();

   if (draw_red_screen==true) Red_Screen();
   glLoadIdentity();
   glClear(GL_DEPTH_BUFFER_BIT); // tutaj mozemy rysowac gui i bedzie na wierzchu
   Ikona();
   Ammon();
   Celownik(); 
   Butelka();
   Wrog();

   if (State==E_DEAD) {   glLoadIdentity();
                          Game_Over(); 
                          if (CInput::KButton()==true) CLogic::Restart();
                          }


   if(red_key==true)  { glLoadIdentity(); glColor3f(1.0f,0.0f,0.0f);  Draw_Key(); }
   if(green_key==true){ glLoadIdentity(); glTranslatef(0.01,0,0);    glColor3f(0.0f,1.0f,0.0f);   Draw_Key(); }   
   if(blue_key==true) { glLoadIdentity(); glTranslatef(0.02,0,0);    glColor3f(0.0f,0.0f,1.0f);   Draw_Key(); }


   glLoadIdentity();
   Numer(CEnemy::Enemies_Killed(),-0.12f,-0.082f);
   Numer(CBottle::num_botles-CBottle::num_picked,-0.08f,-0.082f);
   Numer(int(floor(Health)),0.020f,-0.082f);
   Numer(Ammo,-0.025f,-0.082f);

   stringstream napis;
   glLoadIdentity();
   
   if (message_time>0){                      
                         message_time--;
                         if ((message_time!=0) && (message_id==0))  Need_Red_Key();
                         if ((message_time!=0) && (message_id==1))  Need_Blue_Key();
                         if ((message_time!=0) && (message_id==2))  Need_Green_Key();                         
                         // skonczyl sie czas
                         }

}
  
void CPlayer::Update()
{
          
if (State==E_DEAD){
if (CGraphics::y>0.2) CGraphics::y-=0.01;
 Health=0;
if (CInput::KButton()){ 
                        
                        
                        CLogic::Restart(); 
                        Ammo=10;
                        Health=100;
                        red_key=false;
                        blue_key=false;                        
                        green_key=false;                        
                        CGraphics::x=1.44f;
                        CGraphics::y=0.5f;
                        CGraphics::z=3.89f;                     
                        CGraphics::lx=0.0f;
                        CGraphics::ly=0.0f;
                        CGraphics::lz=-1.0f;
                        State=E_ALIVE;
                        return;
                      } 
 return;}  // UMARL         

     x=CGraphics::x;
     z=CGraphics::z;
     kat=CGraphics::lx; 

     position[0]=CGraphics::x;
     position[1]=CGraphics::y;
     position[2]=CGraphics::z;
     orientation[0]=CGraphics::x;
     orientation[1]=CGraphics::y;
     orientation[2]=CGraphics::z;
     orientation[3]=CGraphics::x+CGraphics::lx;
     orientation[4]=CGraphics::y+CGraphics::ly;
     orientation[5]=CGraphics::z+CGraphics::lz;
     CSound::CSound::Listener_Pos(position,orientation);
     
     
     
     if ((il_dzwiek<=40) && (numer_animacji==2)){
                          numer_animacji=2;
                          interpol=interpol+0.25;  // koniec jesli koniec animacji
                          }
     else if  ((CInput::KDown()==true) || (CInput::KUp()==true)) numer_animacji=1;
     else  numer_animacji=0;

     // jesli lewy klawisz i ammo >0
     if ((CInput::Mouse_LButton()==true) && (Ammo>0)) 
     { // tutaj bedziemy dzwiek puszczali
     numer_animacji=2;
     if (il_dzwiek>=40){// wykonaj jeden strzal
                        Ammo--;
                        il_dzwiek=0; 
                        CEnemy::Check_Aim(x,z,zx,zy);
                        CSound::Play_Sound(7,position,SoundVel);
                        
                        } // position listenera     
     }
     il_dzwiek++;
     interpol=interpol+0.1;  // koniec jesli koniec animacji
     // komunikaty

     
     
     

}

// obraca myszka
void CPlayer::Rotate()
{
 
 if (State!=E_DEAD)
{

  // UMARL 
 
      // test
        // cale poruszanie zalezne jest od CPU - poruszanie playera wrogow itp  
    if ( (CInput::KUp())  ) zz=1; else 
    if ( (CInput::KDown()) ) zz=-1; else zz=0;    
    if ((CInput::KLeft()) ) lr=1; else
    if ((CInput::KRight()) ) lr=-1; else lr=0;
} else {zz=0;lr=0;}    

        // bedzie sprawdzal czy nie ma kolizji na podstawie X,Z
   
    int dx,dy;
    CInput::Mouse_dxdy(dx,dy);
    zx=zx+((float)dx)/(float)50;

    zy=zy+((float)dy)/(float)50;          
    if (zx>2*3.14) zx=0; // przywracamy wlasciwy kat
    if (zx<0) zx=2*3.14; // przywracamy wlasciwy kat

    if (zy>1) zy=1; 
    if (zy<-1) zy=-1; 
   CGraphics::Kamera_Obrot(zx,zy); // ruch kamery JEST krempowany

 CGraphics::Kamera_Ruch(zz,lr,this,Collision); // ruch kamery JEST krempowany

}



// kolizje trza przerobic jak na wiecej graczy 
bool Collision(float &x,float &z,CObject *obiekt)
{
 CObject::Objects_Check(CGraphics::x,CGraphics::z,x,z,& *obiekt);   // &  * <!!! REFERENCJA DO OBIEKTU W WSKAZNIKU
if (CMap::Check(CGraphics::x,CGraphics::z,x,z)==TRUE) // sprawdza
return TRUE;
else return FALSE;
}



void CPlayer::Need_Red_Key()
 {
   if (message_time<=0){ message_time=100; message_id=0; return;} // za pierwszym razem nie rysuje
//   glLoadIdentity();
//   glClear(GL_DEPTH_BUFFER_BIT); // tutaj mozemy rysowac gui i bedzie na wierzchu
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(120)); // celownik
   glTranslatef(-0.19,0.13,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.32);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.32);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );      
 }


void CPlayer::Need_Blue_Key()
 {
   if (message_time<=1){ message_time=100; message_id=2; return;} // za pierwszym razem nie rysuje
//   glLoadIdentity();
//   glClear(GL_DEPTH_BUFFER_BIT); // tutaj mozemy rysowac gui i bedzie na wierzchu
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(121)); // celownik
   glTranslatef(-0.19,0.13,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.32);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.32);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );      
 }


void CPlayer::Need_Green_Key()
 {
   if (message_time<=0){ message_time=102; message_id=3; return;} // za pierwszym razem nie rysuje
//   glLoadIdentity();
//   glClear(GL_DEPTH_BUFFER_BIT); // tutaj mozemy rysowac gui i bedzie na wierzchu
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(122)); // celownik
   glTranslatef(-0.19,0.13,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.32);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.32);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );      
 }



void CPlayer::Game_Over()
 {

//   glLoadIdentity();
//   glClear(GL_DEPTH_BUFFER_BIT); // tutaj mozemy rysowac gui i bedzie na wierzchu
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(123)); // celownik
   glTranslatef(-0.15,0.02,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana
   glColor3f(1.0f,1.0f,1.0f);   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.32);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.32);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );      
 }


void CPlayer::Draw_Key()
 {
   glClear(GL_DEPTH_BUFFER_BIT); // tutaj mozemy rysowac gui i bedzie na wierzchu
   static int il_zmiana=0;
   static int texnum;
   glDisable( GL_LIGHTING );
   glEnable( GL_TEXTURE_2D );
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(5)); // celownik
   glTranslatef(0.10,-0.14,-0.15); // bo obiekt ma 0.8
   glRotatef(90,0,1,0);
   // jedna sciana   
   glBegin( GL_QUADS );
   //zmienimy odwrotnie
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,0.0,0.02);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.02,0.02);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.02,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );
   glEnable( GL_LIGHTING );      
 }








bool CPlayer::Check_Aim(float x,float z,float katx) 
{
if (State==E_DEAD) return false;  // UMARL
  float stary_tmp_x=x+0.5;
  float stary_tmp_z=x+0.5;
  float tmp_x = x; // pozycja x wroga 
  float tmp_z = z; // pozycja z wroga
  float lx = sin(katx);
  float lz = -cos(katx);	    	


    float odleglosc = sqrt(Kwadrat((x-this->x))+Kwadrat((z-this->z)));
bool flag=false;    
float j=odleglosc-1;
    tmp_x = tmp_x + j*(lx);
    tmp_z = tmp_z + j*(lz);

    float nowy_tmp_x=tmp_x;
    float nowy_tmp_z=tmp_z;
    
    float dx=nowy_tmp_x+0.05f;
    float dz=nowy_tmp_z+0.05f;


         float przod=this->x-2.5;
         float tyl  =this->x+2.5;
         float lewo =this->z-2.5;
         float prawo=this->z+2.5;
     
     

   if ((nowy_tmp_x<=tyl) && (przod<=nowy_tmp_x) && 
       (nowy_tmp_z>=lewo) && (prawo>=nowy_tmp_z)
       ) // "gwozdz" funkcji
    {
     // robimy kolizje w Y
     
     Hit(odleglosc);
     // mamy kolizje

//     std:cout<<"Od wroga"<<odleglosc<<" od sciany"<<CMap::Od_Sciany(odleglosc);
     if (odleglosc<CMap::Od_Sciany(odleglosc)) {
                                               }
     }



}


void CPlayer::Hit(float odleglosc)
{
static int il_health=0;
int old_health = int(floor(Health));
Health=Health-1/(odleglosc+0.01)*1,5;
if (old_health!=int(floor(Health)))
 {
  
  // play sound
  if (il_health<=0){
                     CSound::Play_Sound(14,position,SoundVel);
                     draw_red_screen=true;
                     il_health=5;
                    }
  il_health--;
 }

if (Health<=0) {
                     CSound::Play_Sound(15,position,SoundVel);
                     State=E_DEAD;
               }

//std::cout<<"Zabieram punktow:"<<<<"\n";

}



void CPlayer::Restart(){
                        Ammo=10;
                        Health=100;
                        red_key=false;
                        blue_key=false;                        
                        green_key=false;  
                        CGraphics::x=1.44f;
                        CGraphics::y=0.5f;
                        CGraphics::z=3.89f;                     
                        CGraphics::lx=0.0f;
                        CGraphics::ly=0.0f;
                        CGraphics::lz=-1.0f;
                        State=E_ALIVE;
                        }



bool CPlayer::Is_Exit_Possible()
{
if (CBottle::num_botles-CBottle::num_picked==0) return true; else return false;
}
