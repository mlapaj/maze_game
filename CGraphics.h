#ifndef CGGRAPHICS
#define CGGRAPHICS
#include "CObject.h"
#include "CDebug.h"
#include <GL/glut.h>
#include <GL/glext.h>
#define MAX_TEXTURES 255
#define MAX_MODELS 255
#define MAX_PIXMAPS 255
#define NUMVERTEXNORMALS        162
#define SHADEDOT_QUANT          16

typedef float vec3_t[3];

class CGraphics{
private:
        
        
typedef struct
{
    int     ident;              
    int     version;            
    int     skinwidth;          
    int     skinheight;         
    int     framesize;          
    int     num_skins;          
    int     num_xyz;            
    int     num_st;             
    int     num_tris;           
    int     num_glcmds;         
    int     num_frames;         
    int     ofs_skins;          
    int     ofs_st;             
    int     ofs_tris;           
    int     ofs_frames;         
    int     ofs_glcmds;         
    int     ofs_end;            
} md2_t;






typedef struct
{
    unsigned char   v[3];                // verteksy
    unsigned char   lightnormalindex;    // swiatla (not working)

} vertex_t;


typedef struct
{
    float       scale[3];       // wsp skali
    float       translate[3];   // wektor translacji
    char        name[16];       // nazwa klatki
    vertex_t    *verts;       // // za nim sa nastepne wierzcholki
} frame_t;
        
        
typedef struct{
    vec3_t          *m_vertices;        // macierz wierzcholkow
    int             *m_glcmds;          // macierz polecen opengl
    int             *m_lightnormals;          // macierz polecen opengl
    float           m_scale;            // scale value
    char      **nazwa;
    int    n_glcmds;
    int n_frames;
    int n_xyz;
} Md2_Model_t;

typedef struct{
        int width;
        int height;
        GLenum format;
        GLenum type;
        GLubyte * pixels;
        } Pixmap_T;       
        
        static vec3_t   anorms[ NUMVERTEXNORMALS ];
        static float    anorms_dots[ SHADEDOT_QUANT ][256];
        CDebug debug;
        void InitOpenGL(int argc, char **argv,int width,int height);        
        static GLuint Textures[MAX_TEXTURES];  // tekstury scian (od zero do 254)
        static GLuint Md2Textures[MAX_TEXTURES];  // tekstury md2   (od 255-)
        static Md2_Model_t Md2_Model[MAX_MODELS]; // TO TRZEBA USTAWIC
        static void LoadTexture(const char *filename,GLuint &Textures);

        static bool CGraphics::FileExists(const char *strFilename); 

        static bool CGraphics::LoadMd2(const char *filename, Md2_Model_t &Model);
        static void CalculateNormal(float *p1,float *p2,float *p3);
        static void CGraphics::LoadPixmap(const char *filename,Pixmap_T &Picture_Table);
        static GLuint projTexture;
        
public:

       static void LoadFlashLight();
       static Pixmap_T Pixmaps[MAX_PIXMAPS]; /// !!!!!!!!!!!!!! LEPIEJ W PRIVATE
       static bool Md2_Repeated; // ustawiane jesli jest juz zapetlone
       static PFNGLWINDOWPOS2FARBPROC glxWindowPos2fARB ;
       static float lx,ly,lz;
       static float x,y,z;
       static int width,height;
       static void SimpleDisplay(void);
       static void SimpleIdle(void);
       static void SimpleResize(int width,int height);
       CGraphics(int argc,char **argv,int width=640,int height=480);      
       void DisplayFunction(void (*wsk_display)() = 0);
       void IdleFunction(void (*wsk_display)() = 0);
       void ResizeFunction(void (*wsk_func_resize)(int,int) =0);
       void InputFunction(void (*wsk_func_key)(unsigned char,int,int),void (*wsk_func_key_up)(unsigned char,int,int),void (*wsk_special_key)(int,int,int),void (*wsk_special_key_up)(int,int,int),void (*wsk_motion)(int,int),void (*wsk_entry)(int),void (*wsk_action)(int,int,int,int));
       void MotionFunction(void (*wsk_func)(int,int)=0);
       void MainLoop();
       static void Kamera_Obrot(float kat,float kat2);
       static void CGraphics::Kamera_Ruch(int i,int j,CObject *obiekt,bool (*wsk_func)(float&,float&,CObject *obiekt));
       static void CGraphics::TextOut(float x,float i,const char *tekst);
       static bool CGraphics::DisplayInterpolatedMd2(int model_num,int start_frame,int end_frame,int &current_frame,int &next_frame,float &interpol);
       static bool CGraphics::DisplayInterpolatedMd2(int model_num,const char *nazwa,int &current_frame,int &next_frame,float &interpol);
       static void CGraphics::DrawPixmap(int num);
       static void CGraphics::AnimateMd2(int num,float procent);
       static void CGraphics::ChangeFrameMd2(int model_num);
       static void CGraphics::LoadTextures();
       static bool CGraphics::LoadModels();
       static void CGraphics::LoadPixmaps();
       // ladowanie tekstur
       static GLuint CGraphics::Texture(int i);
       ~CGraphics();            
};


#endif 


