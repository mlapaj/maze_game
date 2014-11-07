#include <iostream>
#include <GL/glew.h>
#include "CGraphics.h"
#include "CLogic.h"
#include "CInput.h"
#include <GL/glut.h>
#include "math.h"
#define BUFFER_SIZE 32768


void Perform()
{
     static CLogic Logika;
     Logika.Perform();
     // czyscimy klawisze
     // CInput::Flush();
}





int main(int argc,char **argv){

srand( (unsigned)time( NULL ) ); // "wymieszaj" 
  
alutInit(&argc, argv); // narazie tak musi byc dzis jestem zbyt spiacy     

CGraphics Grafika(argc,argv);    

Grafika.DisplayFunction(Perform);
Grafika.IdleFunction();
Grafika.ResizeFunction();
Grafika.InputFunction(SterowanieDown,SterowanieUp,SterowanieSpecialDown,SterowanieSpecialUp,MouseMotion,MouseEntry,MouseAction);

Grafika.MainLoop();    
}
