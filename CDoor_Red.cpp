#include "CGraphics.h"
#include "Math.h"
#include "CDoor_Red.h"
#include "CMap.h"
#include <iostream>
CDoor_Red::CDoor_Red(int xx, int zz,int s_type)
{
  State=E_CLOSED;
  type=s_type;
  x=xx+0.5;
  z=zz+0.5;
  y=0;
}


void CDoor_Red::Render()
{

   glEnable( GL_TEXTURE_2D );

   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(3));

  if (type==0){
  glTranslatef(x-0.5+0.4,y-0.0001,z-0.5); 
  glScalef(0.3,1,1);}
  if (type==1){
  glTranslatef(x-0.5,y-0.0001,z-0.5+0.4); 
  glScalef(1,1,0.3);}
  
   glColor3f(1,0,0);
   // jedna sciana

   glBegin( GL_QUADS );
   glNormal3f( 0.0f, 0.0f, 50.0f);	
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.0,1.0);
   glTexCoord2d(1.0,0.0); glVertex3d(1.0,0.0,1.0);
   glTexCoord2d(1.0,1.0); glVertex3d(1.0,1.0,1.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.0,1.0);
   glEnd();
   
   
   glBegin( GL_QUADS );
   glNormal3f( 0.0f, 0.0f, -50.0f);	
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.0,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(1.0,1.0,0.0);
   glTexCoord2d(0.0,0.0); glVertex3d(1.0,0.0,0.0);
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   
   
   glBegin( GL_QUADS );
   glNormal3f( -50.0f, 0.0f, 0.0f);	
   glTexCoord2d(1.0,0.0); glVertex3d(0.0,0.0,1.0);
   glTexCoord2d(1.0,1.0); glVertex3d(0.0,1.0,1.0);
   glTexCoord2d(0.0,1.0); glVertex3d(0.0,1.0,0.0);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   
   
   glBegin( GL_QUADS );
   glNormal3f( 50.0f, 0.0, 0.0f);	
   glTexCoord2d(1.0,0.0); glVertex3d(1.0,0.0,0.0);
   glTexCoord2d(1.0,1.0); glVertex3d(1.0,1.0,0.0);
   glTexCoord2d(0.0,1.0); glVertex3d(1.0,1.0,1.0);
   glTexCoord2d(0.0,0.0); glVertex3d(1.0,0.0,1.0);
   glEnd();
   glDisable( GL_TEXTURE_2D );      
}

void  CDoor_Red::Update()
{
 if (State==E_OPENING)
    {   
     if (y<1)  y=y+0.1;
     else {
          czas_otwarcia=20;  
          State=E_OPENED;
          }

    }
 if (State==E_OPENED)
    {


      czas_otwarcia--;
      if (czas_otwarcia<0) czas_otwarcia=20; 
      if (czas_otwarcia==0) {                           
                             std::cout << floor(CGraphics::x);
                             std::cout << x;                 
                            // do zmodyfikowania w Multiplayer
                            if (
                               ((floor(CGraphics::x)<x-1) ||
                                (floor(CGraphics::x)>x+1))
                                ||
                               ((floor(CGraphics::z)>z+1) ||
                                (floor(CGraphics::z)<z-1))
                                )
                            {
                            State=E_CLOSING;
                            CSound::Play_Sound(10,SoundPos,SoundVel);
                            }
      
                            }
    }                        
 if (State==E_CLOSING)
    {
      if (y>0.1)  y=y-0.1;
      else{ y=0; State=E_CLOSED;}
    }

                        
}


bool  CDoor_Red::Trigger(CPlayer &player)
{
      
      
if (State==E_OPENING){
                       // co robi jesli sie otwiera
                      }

if (State==E_CLOSED)
{
 if (player.Got_Red_Key()==true)
 {                   
 SoundPos[0]=x;SoundPos[1]=0.5f;SoundPos[2]=z;
 SoundVel[0]=0.0;SoundVel[1]=0.0;SoundVel[2]=0.0;
 State=E_OPENING;
 CSound::Play_Sound(9,SoundPos,SoundVel);
 }
 else
 { 
     player.Need_Red_Key(); 
     return false;
        }
}
 return true;  
}

