#include "CDebug.h"
#include "GL/gl.h"
#ifndef CMAP
#define CMAP

// ZAKLADAMY ZE WIELKOSC KOSTKI TO ZAWSZE 1x1

class CMap
{
private:
       static int *Map;  // our map
       static int Map_X; // map size X
       static int Map_Y; // map size Y

       CDebug debug;
       int brick_width;
       GLuint  TextureLoad();
public:
       CMap();
       void Brick(int tekstura=0);
       void LoadMap(const char *filename);
       void RenderMap();
       static bool CMap::Check(float &s_x,float &s_z,float &x,float &z);
       static float Od_Sciany(float max_odleglosc);
       void LoadTextures();
       float Restart();
       
      
};

#endif 
