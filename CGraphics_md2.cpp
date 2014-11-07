#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/glaux.h>
#include <sstream>
#include <iostream>
#include "stdio.h"
#include "CGraphics.h"
#include <math.h>
#include "CInput.h"




bool CGraphics::Md2_Repeated=false; // jesli sie powtorzylo to ustawia na true


// precalculated normal vectors
vec3_t   CGraphics::anorms[ NUMVERTEXNORMALS ] = {
#include    "anorms.h"

};

 

// precalculated dot product results

float    CGraphics::anorms_dots[ SHADEDOT_QUANT ][256] = {

#include    "anormtab.h"

};





GLfloat xrot;         // Obrót na osi X ( NOWE )
GLfloat yrot;         // Obrót na osi Y ( NOWE )
GLfloat zrot;         // Obrót na osi Z ( NOWE ) 


//vec3_t          *m_vertices;        // macierz wierzcholkow
//int             *m_glcmds;          // macierz polecen opengl
//float           m_scale;            // scale value




bool CGraphics::LoadMd2(const char *filename, Md2_Model_t &Md2_Model){

 char            *buffer;        // buffer storing frame data
 FILE *plik;
 md2_t *header = new md2_t;
 frame_t         *frame;         // temporary variable
 vec3_t          *ptrverts;      // pointer on m_vertices
 int             *ptrnormals;    // pointer on m_lightnormals

    std::cout<<"Laduje model: "<<filename<<"\n";
    // ladujemy teksture
    plik = fopen(filename,"rb");
    if (plik==0) return 0;
    fread(header,1,sizeof(md2_t),plik);
    if ((header->ident!=844121161) || (header->version!=8)) return -1;
    Md2_Model.n_frames =  header->num_frames;
    // tworzymy prezstrzen nazw klatek
    Md2_Model.nazwa = new char* [Md2_Model.n_frames]; // tyle wskaznikow

    Md2_Model.n_xyz = header->num_xyz;
    Md2_Model.n_glcmds = header->num_glcmds;
    Md2_Model.m_vertices      = new vec3_t[ Md2_Model.n_xyz * Md2_Model.n_frames ]; // !!tworzy nowe wierzcholki dla wszystkich klatek
    Md2_Model.m_glcmds        = new int[ Md2_Model.n_glcmds ];            // !!tworzy nowe komendy
    Md2_Model.m_lightnormals  = new int[ Md2_Model.n_xyz * Md2_Model.n_frames ];
    
    
    frame = new frame_t[Md2_Model.n_frames];  // tworzy nowa klatki    
    fseek(plik,header->ofs_glcmds,SEEK_SET);
    fread((char *)Md2_Model.m_glcmds,Md2_Model.n_glcmds ,sizeof( int ),plik);
    frame->verts = new vertex_t[Md2_Model.n_xyz];    
    fseek(plik,header->ofs_frames,SEEK_SET);
    for (int k=0;k<Md2_Model.n_frames;k++){ // DLA WSZYSTKICH RAMEK
    fread(&(frame->scale[0]),sizeof(float),3,plik);
    fread(&(frame->translate[0]),sizeof(float),3,plik);    
    fread(&(frame->name[0]),sizeof(char),16,plik);    
    fread(frame->verts,sizeof(vertex_t),Md2_Model.n_xyz,plik);    
    Md2_Model.nazwa[k] = new char[sizeof(frame[0].name)];
    strcpy(Md2_Model.nazwa[k],frame[0].name);
//    std::cout<<Md2_Model.nazwa[k];
    // tutaj zrobimy zeby ladowal w wektorach
    

    for (int i=0;i<Md2_Model.n_xyz;i++){
    Md2_Model.m_vertices[Md2_Model.n_xyz*k+i][0] = (frame[0].verts[i].v[0] * frame[0].scale[0]) + frame[0].translate[0]; 
    Md2_Model.m_vertices[Md2_Model.n_xyz*k+i][1] = (frame[0].verts[i].v[1] * frame[0].scale[1]) + frame[0].translate[1]; 
    Md2_Model.m_vertices[Md2_Model.n_xyz*k+i][2] = (frame[0].verts[i].v[2] * frame[0].scale[2]) + frame[0].translate[2]; 
    Md2_Model.m_lightnormals[Md2_Model.n_xyz*k+i] = frame->verts[i].lightnormalindex;                             
 } 
}    

     }







bool CGraphics::LoadModels()
{
  for (int i=0;i<=MAX_MODELS;i++)
  {
   
   std::stringstream filename;
   filename<<"Models\\"<<i<<".png";
   if (FileExists(filename.str().c_str())) LoadTexture(filename.str().c_str(),Md2Textures[i]); // tekstura
   filename.str(""); // czyscimy
   filename<<"Models\\"<<i<<".md2";
   if (FileExists(filename.str().c_str())) LoadMd2(filename.str().c_str(),Md2_Model[i]);
   
  }

}



void CGraphics::CalculateNormal( float *p1, float *p2, float *p3 )
{
   float a[3], b[3], result[3];
   float length;

   a[0] = p1[0] - p2[0];
   a[1] = p1[1] - p2[1];
   a[2] = p1[2] - p2[2];

   b[0] = p1[0] - p3[0];
   b[1] = p1[1] - p3[1];
   b[2] = p1[2] - p3[2];

   result[0] = a[1] * b[2] - b[1] * a[2];
   result[1] = b[0] * a[2] - a[0] * b[2];
   result[2] = a[0] * b[1] - b[0] * a[1];

   // wyznacza d³ugoœæ wektora normalnego
   length = (float)sqrt(result[0]*result[0] + result[1]*result[1] + result[2]*result[2]);

   // i normalizuje go
   glNormal3f(result[0]/length, result[1]/length, result[2]/length);
}






bool CGraphics::DisplayInterpolatedMd2(int model_num,int start_frame,int end_frame,int &current_frame,int &next_frame,float &interpol)
{
   bool flag=false;
//   if ((current_frame>start_frame) &&  (current_frame<=end_frame) && (current_frame==end_frame)) { flag=true;}  // trza sprawdzic jeszcze

    glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable( GL_TEXTURE_2D );
    
    glBindTexture(GL_TEXTURE_2D, Md2Textures[model_num]);  
    int  *ptricmds = Md2_Model[model_num].m_glcmds;       // pointer on gl commands


    if (current_frame<start_frame) {
                                                        current_frame=start_frame;
                                                        next_frame=start_frame+1;}
    if (current_frame>end_frame) {
                                                        current_frame=start_frame;
                                                        next_frame=start_frame+1;}
    
      if (interpol >= 1.0)
        {
                   // czyli od nowa



                interpol = 0.0f;
                current_frame++;
                if (current_frame >= end_frame)//model->numFrames)
                       {

                        current_frame = start_frame; //0;

                        }

                next_frame = current_frame + 1;

                if (next_frame >= end_frame){
                        next_frame = start_frame;
                        flag=true;
                       
                        }
        }


    vec3_t *ptrverts = Md2_Model[model_num].m_vertices+ current_frame*Md2_Model[model_num].n_xyz;   // 1 daje nam 1 klatke
    vec3_t *ptr_nextverts = Md2_Model[model_num].m_vertices+ next_frame*Md2_Model[model_num].n_xyz;   // 1 daje nam 1 klatke



    glTranslatef(0,0.3,0);  
    glScalef(0.012f,0.012f,0.012f);         // Obróæ na osi X
    glRotatef(-90,1.0f,.0f,0.0f);         // Obróæ na osi Y
    glRotatef(90,0.0f,0.0f,1.0f);         // Obróæ na osi Y
    glPushAttrib( GL_POLYGON_BIT );
    glFrontFace( GL_CW );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

  while( int i = *(ptricmds++) )
    {
        if( i < 0 )
        {glBegin( GL_TRIANGLE_FAN );i = -i;} // typ triangle_fan
        else
        {glBegin( GL_TRIANGLE_STRIP );} // typ triangle_strip

 for( ; i > 0; i--  )
        {         
                  
          // tutaj jest wsio zwiazane z Vertexami
          // tu bedziemy robili interpolacje ?        
         glTexCoord2f( ((float *)ptricmds)[0], ((float *)ptricmds)[1] );
         vec3_t inter;
         inter[0] =  ptrverts[ ptricmds[2] ][0] + interpol*(ptr_nextverts[ ptricmds[2] ][0]-ptrverts[ ptricmds[2] ][0]);
         inter[1] =  ptrverts[ ptricmds[2] ][1] + interpol*(ptr_nextverts[ ptricmds[2] ][1]-ptrverts[ ptricmds[2] ][1]);
         inter[2] =  ptrverts[ ptricmds[2] ][2] + interpol*(ptr_nextverts[ ptricmds[2] ][2]-ptrverts[ ptricmds[2] ][2]);         
         glNormal3fv( anorms[ Md2_Model[model_num].m_lightnormals[ ptricmds[2] ] ] );
         glVertex3fv( inter );

    	 ptricmds = ptricmds+3;
        }
        glEnd();
    }

    xrot+=0.4f;         // Obrót na osi X
    yrot+=0.4f;         // Obrót na osi Y
    zrot+=0.0f;     
    glDisable( GL_CULL_FACE );
    glPopAttrib();


return flag;
}



// rozwiniecie ogolne
bool CGraphics::DisplayInterpolatedMd2(int model_num,const char *nazwa,int &current_frame,int &next_frame,float &interpol)
{
    int pierwsza,ostatnia;
    int i;
    for (i=0;i<Md2_Model[model_num].n_frames;i++){        
    if (strstr(Md2_Model[model_num].nazwa[i],nazwa)) break;
     }
    pierwsza=i; // mamy pierwsza klatke
    
    for (i=pierwsza;i<Md2_Model[model_num].n_frames;i++){        
    if (!strstr(Md2_Model[model_num].nazwa[i],nazwa)) break;
     }
    ostatnia=i;


     
       // poszukujemy nazwy klatki !!! SLOW !!!

    return DisplayInterpolatedMd2(model_num,pierwsza,ostatnia,current_frame,next_frame,interpol);
}
