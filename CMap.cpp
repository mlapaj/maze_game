#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/glaux.h>
#include "CObject.h"
#include "CDoor_Silver.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "CMap.h"
#include "math.h"
#include "CGraphics.h"
// wrogowie
#include "CZombie.h"
#include "CCandleBra.h"
// narazie jest plomien bo kolizje sa w graczch takie jak dla przedmiotow 

// przedmioty
#include "CBottle.h"
#include "CAmmo.h"
#include "CRedKey.h"
#include "CBlueKey.h"
#include "CGreenKey.h"
#include "CHealth.h"
// gracze
#include "CPlayer.h"
// drzwi
#include "CDoor_Silver.h"
#include "CDoor_Red.h"
#include "CDoor_Blue.h"
#include "CDoor_Green.h"
#include "CDoor_Exit.h"
 int* CMap::Map;  // our map
 int CMap::Map_X; // map size X
 int CMap::Map_Y; // map size Y

CMap::CMap():debug(true,"CMap")
{
       debug<<"Stworzono obiekt mapy";  
        // mapa 8x8
       Map_X=8; // 8 w x
       Map_Y=8; // 8 w y
       Map = new int[64];
       memset (Map,0,sizeof(Map)); // zerujemy tablice

       Map[2]=1;       
       Map[3]=1;    
       Map[4]=1;    
       Map[5]=1;    

       Map[20]=1;    


}

void CMap::RenderMap()
{
// tworzymy plaszczyzne




for (int a=1;a<=Map_Y;a++){         // dla kazdego y 
    for (int b=1;b!=Map_X+1;b++){     // dla kazdego x (od 0 do 8) czyli 7 iteracji
        int sciana=Map[(b-1)+(a-1)*(Map_X)];
        if ((sciana>=0) && (sciana<5)) {        
        glPushMatrix();
        glTranslatef(a-1,0,b-1);                                 
        Brick(sciana);
        glPopMatrix();        
        }
    }
    
}
}

                 
void CMap::Brick(int tekstura)
{
     
if (tekstura==0)
{

glPushMatrix();

 glActiveTextureARB(GL_TEXTURE0_ARB);
 glEnable(GL_TEXTURE_2D);           
 glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(0));

 glBegin(GL_POLYGON);
      glTranslatef(0.5,0,0.5);   
      glNormal3f( 0.0f, -20.0f, 0.0f);	
      glTexCoord2d(0.0,0.0);  glVertex3f(0,1,0);
      glTexCoord2d(1,0.0);  glVertex3f(1,1,0);
      glTexCoord2d(1,1);  glVertex3f(1,1,1);
      glTexCoord2d(0.0,1);  glVertex3f(0,1,1);      
 glEnd();
 
 
 glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(254));
 glBegin(GL_POLYGON);
   glNormal3f( 0.0f, 20.0f, 0.0f);	 
      glColor3f(1.0f,1.0f,1.0f);
      glTexCoord2d(0.0,0.0); glVertex3f(0,0,1);      
      glTexCoord2d(1,0.0);   glVertex3f(1,0,1);
      glTexCoord2d(1,1);     glVertex3f(1,0,0);
      glTexCoord2d(0.0,1);   glVertex3f(0,0,0);
 glEnd();

glPopMatrix();
return;
}
     
     
   glActiveTextureARB(GL_TEXTURE0_ARB);
   glEnable(GL_TEXTURE_2D);           
   glBindTexture( GL_TEXTURE_2D, CGraphics::Texture(tekstura-1));
   glColor3f(1.0f,1.0f,1.0f);
   // jedna sciana
//   glTranslatef(-0.5,0,-0.5); 
   glBegin( GL_QUADS );
   glNormal3f( 0.0f, 0.0f, 50.0f);	
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.0,1.0);
   glTexCoord2d(4.0,0.0); glVertex3d(1.0,0.0,1.0);
   glTexCoord2d(4.0,4.0); glVertex3d(1.0,1.0,1.0);
   glTexCoord2d(0.0,4.0); glVertex3d(0.0,1.0,1.0);
   glEnd();
   
   
   glBegin( GL_QUADS );
   glNormal3f( 0.0f, 0.0f, -50.0f);	
   glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.0,0.0);
   glTexCoord2d(0.0,4.0); glVertex3d(1.0,1.0,0.0);
   glTexCoord2d(0.0,0.0); glVertex3d(1.0,0.0,0.0);
   glTexCoord2d(4.0,0.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   
   
   glBegin( GL_QUADS );
   glNormal3f( -50.0f, 0.0f, 0.0f);	
   glTexCoord2d(4.0,0.0); glVertex3d(0.0,0.0,1.0);
   glTexCoord2d(4.0,4.0); glVertex3d(0.0,1.0,1.0);
   glTexCoord2d(0.0,4.0); glVertex3d(0.0,1.0,0.0);
   glTexCoord2d(0.0,0.0); glVertex3d(0.0,0.0,0.0);
   glEnd();
   
   
   glBegin( GL_QUADS );
   glNormal3f( 50.0f, 0.0, 0.0f);	
   glTexCoord2d(4.0,0.0); glVertex3d(1.0,0.0,0.0);
   glTexCoord2d(4.0,4.0); glVertex3d(1.0,1.0,0.0);
   glTexCoord2d(0.0,4.0); glVertex3d(1.0,1.0,1.0);
   glTexCoord2d(0.0,0.0); glVertex3d(1.0,0.0,1.0);
   


   glEnd();
  
}

bool CMap::Check(float &s_x,float &s_z,float &x,float &z)
{
bool flag=false;
float dz=0,dx=0;
 if ((z<=0.3) || (z>=Map_X-0.3)) {
            z=s_z;
            } 
 if ((x<=0.3) || (x>=Map_Y-0.3)) {
            x=s_x;
             
            } 
if (s_x-x>0) dx=-0.3;
if (s_x-x<0) dx=0.3;
if (s_x-x==0) dx=0.0;

if (s_z-z>0) dz=-0.3;
if (s_z-z<0) dz=0.3;
if (s_z-z==0) dz=0.0;

// poprawki zeby nie podchodzic za blisko scian




  // przednia z
 if (Map[(int)floor(z+dz)+Map_X*(int)floor(x-dx)]>0) { 
    z=s_z;
    flag=true;
}
 if (Map[(int)floor(z-dz)+Map_X*(int)floor(x+dx)]>0) { 
    x=s_x;
    flag=true;
}

 if (Map[(int)floor(z+dz)+Map_X*(int)floor(x+dx)]>0) { 
 if (Map[(int)floor(z+dz)+Map_X*(int)floor(s_x+dx)]>0) {    flag=true;   z=s_z;}
 if (Map[(int)floor(s_z+dz)+Map_X*(int)floor(x+dx)]>0) {    flag=true;   x=s_x;}
}


return flag;
}


void CMap::LoadMap(const char *filename)
{
using namespace std;
     ifstream plik(filename);
     int x,y;
     plik>>x;
     plik>>y;
     
     if (Map!=NULL) delete Map;
     Map = new int[x*y];
     for (int i=0;i<=x*y;i++) plik>>Map[i];
     Map_X = x;
     Map_Y = y;
     cout<<"x:"<<x<<"y:"<<y<<endl;
     plik.close();
     
     
     // dobra ladujemy tera obiekty typu drzwi i inne
     
for (int a=1;a<=Map_Y;a++){         // dla kazdego y 
    for (int b=1;b!=Map_X+1;b++){     // dla kazdego x (od 0 do 8) czyli 7 iteracji
        int sciana=Map[(b-1)+(a-1)*(Map_X)];
        // przedmioty
        if (sciana==50) {
                       CObject::Add(new CBottle(a,b));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }

        if (sciana==51) {
                       CObject::Add(new CAmmo(a,b));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }


        if (sciana==52) {
                       CObject::Add(new CRedKey(a,b));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }


        if (sciana==53) {
                       CObject::Add(new CBlueKey(a,b));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }

        if (sciana==54) {
                       CObject::Add(new CGreenKey(a,b));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }


        if (sciana==55) {
                      CObject::Add(new CHealth(a,b));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }



        // drzwi 
        if (sciana==100) {
                       CObject::Add(new CDoor_Silver(a-1,b-1,0));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }
        if (sciana==101) {
                       CObject::Add(new CDoor_Silver(a-1,b-1,1));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }
        if (sciana==102) {
                       CObject::Add(new CDoor_Red(a-1,b-1,0));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }        
        if (sciana==103) {
                       CObject::Add(new CDoor_Red(a-1,b-1,1));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }        

        if (sciana==104) {
                       CObject::Add(new CDoor_Blue(a-1,b-1,0));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }        
        if (sciana==105) {
                       CObject::Add(new CDoor_Blue(a-1,b-1,1));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }        

        if (sciana==106) {
                       CObject::Add(new CDoor_Green(a-1,b-1,0));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }        
        if (sciana==107) {
                       CObject::Add(new CDoor_Green(a-1,b-1,1));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }        

        if (sciana==108) {
                       CObject::Add(new CDoor_Exit(a-1,b-1,0));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }        
        if (sciana==109) {
                       CObject::Add(new CDoor_Exit(a-1,b-1,1));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }        

        // czyscimy dana czesc mapy (tego obiektu nie ma)



        // wrogowie
        if (sciana==120) {
                       CObject::Add(new CZombie(a-1,b-1));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }
        if (sciana==121) {
                       CObject::Add(new CCandleBra(a-1,b-1));
                       Map[(b-1)+(a-1)*(Map_X)]=0;
        }



           
    }
   }
     
}


GLuint CMap::TextureLoad()
{
  GLuint texture;
  int width, height;
  BYTE * data;
  FILE * file;
  char filename[]="texture1.raw";
  bool wrap=TRUE;
  // open texture data
  file = fopen( filename, "rb" );
  if ( file == NULL ) return 0;

  // allocate buffer
  width = 240;
  height = 194;
  data = new BYTE[width*height*3];

  // read texture data
  fread( data, width * height * 3, 1, file );
  fclose( file );

  // allocate a texture name
  glGenTextures( 1, &texture );

  // select our current texture
  glBindTexture( GL_TEXTURE_2D, texture );

  // select modulate to mix texture with color for shading
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  // when texture area is small, bilinear filter the closest MIP map
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                   GL_LINEAR_MIPMAP_NEAREST );
  // when texture area is large, bilinear filter the first MIP map
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  // if wrap is true, the texture wraps over at the edges (repeat)
  //       ... false, the texture ends at the edges (clamp)
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                   wrap ? GL_REPEAT : GL_CLAMP );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                   wrap ? GL_REPEAT : GL_CLAMP );

  // build our texture MIP maps
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width,
    height, GL_RGB, GL_UNSIGNED_BYTE, data );

  // free buffer
  delete data;
  return texture;

}



float Kwadrat(float x)   { x = x*x;  return x; }

float CMap::Od_Sciany(float max_odleglosc)
{
float j=0.1;
float dx,dz;
for (j=0;j<max_odleglosc;j+=0.1){
  float tmp_x = CGraphics::x + j*(CGraphics::lx);
  float tmp_z = CGraphics::z + j*(CGraphics::lz);

  float nowy_x=tmp_x+CGraphics::lx;
  float nowy_z=tmp_z+CGraphics::lz;
  
  dx = (CGraphics::x + (j+0.1)*(CGraphics::lx))+CGraphics::lx;
  dz = (CGraphics::z + (j+0.1)*(CGraphics::lz))+CGraphics::lz;
  CMap::Check(nowy_x,nowy_z,dx,dz);
  if (nowy_x==dx) break;
  if (nowy_z==dz) break;

}
 glTranslatef(dx,0.0,dz);     
 // liczymy odleglosc od sciany:
 float odleglosc = sqrt(Kwadrat(CGraphics::x-dx)+Kwadrat(CGraphics::z-dz));
 return odleglosc;     
}
