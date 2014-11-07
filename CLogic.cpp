#include <iostream>
#include <sstream>
#include <math.h> 
#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/glaux.h>
#include "CObject.h"
#include "CEnemy.h"
#include "CItem.h"
#include "CLogic.h"
#include "CInput.h"
#include "CGraphics.h"

#include "CSound.h"
#include <iostream>

float CLogic::x=3.14;
float CLogic::y=0;
int CLogic::z=0;
int CLogic::lr=0;
int CLogic::Current_Map = 0;
bool CLogic::next_map=false;
char *CLogic::Maps[MAX_MAPS] = { "map01.dat","map02.dat","map03.dat" };

void Time_r(int val)
{
      if (CLogic::next_map==true){CLogic::next_map=false;
                         CLogic::Current_Map++;
                         if (CLogic::Current_Map==MAX_MAPS) CLogic::Current_Map=0;
                         std::cout<<"nastepna mapa"<<CLogic::Current_Map;

                         CLogic::Restart();
                        }

      CObject::Objects_Update();
            glutTimerFunc(20,Time_r,0); // uruchom siebie za 5 sekund
 

}     

void updateSpot();
void initSpot();


using namespace std;
CMap CLogic::Mapa;

CLogic::CLogic():debug(true,"CLogic")
{
                             
       debug<<"Stworzono obiekt logiki";  
       // wczytujemy dzwiek
       CSound::Load_Sounds();       
       char filename[50];
       strcpy(filename,"Maps\\");
       strcat(filename,Maps[Current_Map]);   
       Mapa.LoadMap(filename);
       // wczytujemy modele
       CGraphics::LoadPixmaps();
       // wczytujemy tekstury
   CGraphics::LoadTextures();

       // wczytujemy modele
       CGraphics::LoadModels();
       // wczytujemy mape
   if (GLEW_ARB_multitexture) 
   {
    cout<<"GL_TEXTURE1_ARB";                                         
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glEnable(GL_TEXTURE_2D);  
   }
   CGraphics::LoadFlashLight();



       glutTimerFunc(100,Time_r,0);      

       CObject::Add(new CPlayer(1,1));

       
       
   initSpot();


       

       
}

void initSpot()
    {
        float noAmbient[] = {0.0f, 0.0f, 0.0f, 0.0f};    
        float diffuse[]   = {1.0f, 1.0f, 1.0f, 0.0f};
        float position[]  = {CGraphics::x, 0.0f, CGraphics::z, 1.0f};
       
        glLightfv(GL_LIGHT2, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, position);

        updateSpot();
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50.0f);
    
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION,10.0f);
    }
   
void updateSpot()
    {

        float direction[] = {CGraphics::x, 0.5, CGraphics::z};
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 180);
    }



void CLogic::Perform(void)
{

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    


    

    
        CObject::Rotate_Players(); // obrot kamery nie jeset krrempowany 
if (Current_Map==2) { glEnable(GL_LIGHTING);  glEnable(GL_LIGHT2); } else {
                    glDisable(GL_LIGHTING); glDisable(GL_LIGHT2); glDisable(GL_LIGHT3);} 

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    Mapa.RenderMap();    
    CObject::Objects_Render(); // renderuje wszystkich wrogow
    glutSwapBuffers();        
}                 


void CLogic::Restart()
{

  CObject::CObject::Objects_Remove();
  char filename[50];
  strcpy(filename,"maps\\");
  strcat(filename,Maps[Current_Map]);   
  Mapa.LoadMap(filename);}     


void CLogic::Next_Level()
{     
       next_map=true;       
}     
