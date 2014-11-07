#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "CMap.h"
#include "CCandleBra.h"
#include "CGraphics.h"



using namespace std;

CCandleBra::CCandleBra(float x,float z):CEnemy()
{
abc=0;
last_play=0;
los=false;
p_player=0;
CCandleBra::x=x+0.5;
CCandleBra::z=z+0.5;
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

}

void CCandleBra::Render()
{
   // przywracamy wlasciwy kat

    glTranslatef(x,-0.3,z);  
    int modnum =0;
    interpol=1;
    glRotatef((kat*360)/(2*3.14),0,1,0);  
        float noAmbient[] = {40.0f, 40.0f, 0.0f, 1.0f};       //low ambient light
        float diffuse[]   = {40.0f, 40.0f, 0.0f, 1.0f};
        float position[]  = {x+2.5, 0.8f, z+2.5, x};
        
        float direction[] = {-x, 0.5, -z};
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 30.0f);       
        //properties of the light

        glLightfv(GL_LIGHT3, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT3, GL_POSITION, position);
        glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION,1.0f);   
        glDisable(GL_LIGHT2);      
        glEnable(GL_LIGHT3);          
       CGraphics::DisplayInterpolatedMd2(9,"Frame",current_frame,next_frame,interpol);
    // glDisable(GL_LIGHT3);

}


void CCandleBra::Update()
{


}




void CCandleBra::Die()
{

}



void CCandleBra::Play_Sound()
{
 
}

void CCandleBra::Trigger(CPlayer &player)
{

}







