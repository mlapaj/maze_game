#include "CInput.h"
#include <GL/glut.h>
#include "CGraphics.h"
#include <iostream>
int CInput::Klawisz=0;
bool CInput::gora = FALSE;      
bool CInput::dol = FALSE;     
bool CInput::lewo = FALSE;      
bool CInput::prawo = FALSE;       
bool CInput::button = FALSE;       

int CInput::Przyrost_X = 0;      
int CInput::Przyrost_Y = 0;     


int CInput::Mouse_posX = 0;      
int CInput::Mouse_posY = 0;       
int CInput::Mouse_oldposX = -1;      
int CInput::Mouse_oldposY = -1;  
bool CInput::Left_Button = false;
bool CInput::Right_Button = false;       


CDebug CInput::debug = CDebug(true,"CMap"); 


void SterowanieSpecialDown(int key, int x, int y)
{
     CInput::KeyDown(key);     
}


void SterowanieSpecialUp(int key, int x, int y)
{
     CInput::KeyUp(key);     
}



void SterowanieDown(unsigned char key, int x, int y)
{
     CInput::KeyDown_Normal(key);
}


void SterowanieUp(unsigned char  key, int x, int y)
{
     CInput::KeyUp_Normal(key);
}





void MouseMotion(int x, int y)
{
    CInput::Przyrost_X=x-CInput::Mouse_posX;
    CInput::Przyrost_Y=y-CInput::Mouse_posY;
    CInput::Mouse_posX=x;
    CInput::Mouse_posY=y;
    CInput::debug<<"Ruch myszy";
}


void MouseAction(int button,int state,int x, int y)
{
   bool flag = (state==GLUT_UP) ? false : true;
   
    switch (button)
    {
       case GLUT_LEFT_BUTTON:  CInput::Left_Button=flag;
       case GLUT_RIGHT_BUTTON: CInput::Left_Button=flag;
    }
    
}

void MouseEntry(int state)
{
    CInput::debug<<"Wlazlem w okno";
    CInput::Przyrost_X=0;
    CInput::Przyrost_Y=0;
    // tutaj nie wiemy nic
    CInput::Mouse_oldposX=-1; 
    CInput::Mouse_oldposY=-1;     
}

CInput::CInput()
{
       debug<<"Stworzono obiekt input";  
}


void CInput::Perform(void)
{     
}


void CInput::KeyDown(int key)
{
     debug<<"Dostalem klawisz";
     Klawisz=key;
     switch(key)
     {
        case GLUT_KEY_UP: gora=true;; break;
        case GLUT_KEY_DOWN: dol=true; break;                
        case GLUT_KEY_LEFT: lewo=true; break;                
        case GLUT_KEY_RIGHT: prawo=true; break;   
     } 
}



void CInput::KeyUp(int key)
{
     debug<<"Zdjelem klawisz";
     Klawisz=key;
     switch(key)
     {
        case GLUT_KEY_UP: gora=false; break;
        case GLUT_KEY_DOWN: dol=false; break;
        case GLUT_KEY_LEFT: lewo=false; break;
        case GLUT_KEY_RIGHT: prawo=false; break;
        
     } 
}






void CInput::KeyDown_Normal(unsigned char key)
{
     
     std::cout<<"Dostalem normalny klawisz "<<key<<"\n";
     switch(key)
     {
        case 27: exit(0); break;                  
        case ' ': button=true;; break;
        case 'w': {gora=true; std::cout<<"wkladam gore";} break;
        case 's': dol=true; break;                
        case 'a': lewo=true; break;                
        case 'd': prawo=true; break;           

     } 
}



void CInput::KeyUp_Normal(unsigned char key)
{
     std::cout<<"Zdjelem normalny klawisz "<<key<<"\n";
     switch(key)
     {
        case ' ': button=false; break;
        case 'w': { gora=false; std::cout<<"sciagam gore";} break;
        case 's': dol=false; break;                
        case 'a': lewo=false; break;                
        case 'd': prawo=false; break;      
                
     } 
}








void CInput::Mouse_dxdy(int &dx,int &dy){
              if (Mouse_oldposY!=-1) Przyrost_X=Mouse_posX-Mouse_oldposX;
              if (Mouse_oldposY!=-1) Przyrost_Y=Mouse_posY-Mouse_oldposY;
              dx=Przyrost_X;
              dy=Przyrost_Y;                             
              if ((Przyrost_X!=0) || (Przyrost_Y!=0)){
              glutWarpPointer(CGraphics::width/2,CGraphics::height/2);
              Mouse_oldposY=-1;
              Mouse_oldposX=-1;
              Mouse_posX=CGraphics::width/2;
              Mouse_posY=CGraphics::height/2;
              }
            
              } 

void CInput::Flush(void)
{
     /*
     Klawisz=0;
     gora=FALSE;
     dol=FALSE;
     lewo=FALSE;
     prawo=FALSE;
     */
     Przyrost_X=0;
     Przyrost_Y=0;
}
