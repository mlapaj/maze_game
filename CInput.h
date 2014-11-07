#include "CDebug.h"
#ifndef CINPUT
#define CINPUT
#include <GL/glut.h>
#include "CGraphics.h"


class CInput
{
private:
       static CDebug debug;      
       static bool gora;      
       static bool dol;      
       static bool lewo;      
       static bool prawo; 
       static bool button;        
       static bool Left_Button; // lewy od myszki
       static bool Right_Button; // lewy od myszki
       static int Przyrost_X;
       static int Przyrost_Y;
       static int Mouse_posX,Mouse_oldposX;    
       static int Mouse_posY,Mouse_oldposY;
public:
       static int Klawisz;


       CInput();
       void Perform();
       friend void Perform();      
       static void KeyDown(int key);
       static void KeyUp(int key);       
       static void KeyDown_Normal(unsigned char key);
       static void KeyUp_Normal(unsigned char key);  
       static void Flush();
       static bool KUp(){return gora;}
       static bool KDown(){return dol;}
       static bool KLeft(){return lewo;}              
       static bool KRight(){return prawo;}       
       static bool KButton(){return button;} 
       static bool Mouse_Init(){
              glutWarpPointer(CGraphics::width/2,CGraphics::height/2);

              Mouse_oldposY=CGraphics::width/2;
              Mouse_oldposX=CGraphics::height/2;
              Mouse_posX=CGraphics::width/2;
              Mouse_posY=CGraphics::height/2;
              glutSetCursor(GLUT_CURSOR_NONE);
              }
       static void Mouse_dxdy(int &dx,int &dy); 
       static bool Mouse_LButton(){return Left_Button;}  
       static bool Mouse_RButton(){return Right_Button;}                   
       friend void MouseMotion(int x, int y);
       friend void MouseEntry(int akcja);  
       friend void MouseAction(int,int,int,int);         
};


void SterowanieSpecialDown(int key, int x, int y);
void SterowanieSpecialUp(int key, int x, int y);
void SterowanieDown(unsigned char key, int x, int y);
void SterowanieUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void MouseAction(int button, int state,int x, int y);
#endif 
