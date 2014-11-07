#include <GL/glew.h>
#include <GL/glaux.h>
#include "stdio.h"
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include "CObject.h"
#include "CGraphics.h"
#include <math.h>
#include "CInput.h"

#include <sys/stat.h>
#include <libpng13/png.h>

GLuint CGraphics::projTexture;
int CGraphics::width=640;
int CGraphics::height=480;
float CGraphics::lx=0.0f;
float CGraphics::ly=0.0f;
float CGraphics::lz=-1.0f;

float CGraphics::x=1.44f;
float CGraphics::y=0.5f;
float CGraphics::z=3.89f;
GLuint CGraphics::Textures[MAX_TEXTURES]; 
GLuint CGraphics::Md2Textures[MAX_TEXTURES];
CGraphics::Md2_Model_t CGraphics::Md2_Model[MAX_MODELS];
CGraphics::Pixmap_T CGraphics::Pixmaps[MAX_PIXMAPS];  // bo prywatne

CGraphics::CGraphics(int argc,char **argv,int width,int height):debug(true,"CGraphics")
{
  debug<<"Stworzono obiekt grafiki";  
  InitOpenGL(argc,argv,width,height);     
}

CGraphics::~CGraphics()
{
  

}


bool isInString(char *string, const char *search) {
	int pos=0;
	int maxpos=strlen(search)-1;
	int len=strlen(string);	
	char *other;
	for (int i=0; i<len; i++) {
		if ((i==0) || ((i>1) && string[i-1]=='\n')) {				// New Extension Begins Here!
			other=&string[i];			
			pos=0;													// Begin New Search
			while (string[i]!='\n') {								// Search Whole Extension-String
				if (string[i]==search[pos]) pos++;					// Next Position
				if ((pos>maxpos) && string[i+1]=='\n') return true; // We Have A Winner!
				i++;
			}			
		}
	}	
	return false;													// Sorry, Not Found!
}


void CGraphics::InitOpenGL(int argc, char **argv,int width,int height)
{
    // jakies zmienne
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

    debug<<"InitOpengl()";
    CGraphics::width=width;
    CGraphics::width=width;
    glutInit(&argc,argv);

    glutInitWindowSize(width,height);
  
    int cx = GetSystemMetrics(SM_CXSCREEN); // pobieramy  rozdzialke
    int cy = GetSystemMetrics(SM_CYSCREEN);

    glutInitWindowPosition(cx/2-width/2,cy/2-height/2);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Gra (c) Marcin Lapaj 2009");
    glutFullScreen();
    CInput::Mouse_Init();
    
    
    
    
    
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glEnable (GL_LIGHTING);
    
    
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    
    GLenum err = glewInit();
    
    
    
    if (err == GLEW_OK) {std::cout<<"GLEW OK";}
    
    
/*
   if (GLEW_ARB_vertex_program)
{
   cout<<"Core extensions of OpenGL 1.1 to 1.5 are available!\n";
}
*/
/*    
    //Make sure multitexturing is supported

	if(!glMultiTexCoord2fARB && !glActiveTextureARB)

	{
		char c;
		cin>>c;
		exit(0);
	}
*/	
    

 
}

void CGraphics::MainLoop()
{
    glutMainLoop();
}


void CGraphics::DisplayFunction(void (*wsk_func)())
{

 if (wsk_func) glutDisplayFunc(wsk_func);
 else {
      debug<<"Laduje standardowa funkcje display";
      glutDisplayFunc(SimpleDisplay);
      }
}

void CGraphics::IdleFunction(void (*wsk_func)())
{

 if (wsk_func) glutIdleFunc(wsk_func);
 else {
      debug<<"Laduje standardowa funkcje idle";
      glutIdleFunc(SimpleIdle);
      }
}




void CGraphics::InputFunction(void (*wsk_func_key)(unsigned char,int,int),void (*wsk_func_key_up)(unsigned char,int,int),void (*wsk_special_key)(int,int,int),void (*wsk_special_key_up)(int,int,int),void (*wsk_motion)(int,int),void (*wsk_entry)(int),void (*wsk_action)(int,int,int,int))
{

 if (wsk_special_key) glutSpecialFunc(wsk_special_key);
 else {
      debug<<"Brak obslugi klawiatury DOWN";
      }
 if (wsk_special_key_up) glutSpecialUpFunc(wsk_special_key_up);
 else {
      debug<<"Brak obslugi klawiatury UP";
      }      




 if (wsk_func_key) glutKeyboardFunc(wsk_func_key);
 else {
      debug<<"Brak obslugi klawiatury DOWN";
      }
 if (wsk_func_key_up) glutKeyboardUpFunc(wsk_func_key_up);
 else {
      debug<<"Brak obslugi klawiatury UP";
      }      


 if (wsk_motion) glutPassiveMotionFunc(wsk_motion);
 else {
      debug<<"Brak funkcji motion";
      }
///////// UWAGA UZYJE DOMYLSNEGO MOUSE MOTION 
///////// UWAGA UZYJE DOMYLSNEGO MOUSE MOTION 
 if (wsk_motion) glutMotionFunc(wsk_motion);
 else {
      debug<<"Brak funkcji motion";
      }

 if (wsk_entry) glutEntryFunc(wsk_entry);
 else {
      debug<<"Brak funkcji entry";
      }


 if (wsk_entry) glutMouseFunc(wsk_action);
 else {
      debug<<"Brak funkcji entry";
      }



}

void CGraphics::ResizeFunction(void (*wsk_func_resize)(int,int))
{

 if (wsk_func_resize) glutReshapeFunc(wsk_func_resize);
 else {
      debug<<"Laduje standardowa funkcje resize";
      glutReshapeFunc(SimpleResize);
      }
}



 void CGraphics::SimpleDisplay(void)
{
      // rysuj pilke
  static int slices = 16;
  static int stacks = 32;
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0,1,0);

    glPushMatrix();
        glTranslated(0,0,-3);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    glutSwapBuffers();        
}




 void CGraphics::SimpleIdle(void){
      glutPostRedisplay();
      Sleep(10);

      }




void CGraphics::SimpleResize(int width,int height){
    const float ar = (float) width / (float) height;    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glFrustum(-ar, ar, -0.5, 0.5, 1, 100.0);    
    gluPerspective(90,ar,0.1,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


void CGraphics::Kamera_Obrot(float kat,float kat2=0) {
	lx = sin(kat);
	ly = -sin(kat2);	
	lz = -cos(kat);	    	
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}




void  CGraphics::Kamera_Ruch(int i,int j,CObject *obiekt,bool (*wsk_func)(float&,float&,CObject *obiekt)) {
    float tmp_x = x;
    float tmp_z = z;
    
    // najpierw liczymy tymczasowo
    tmp_x = tmp_x + j*(lz)*0.1;
    tmp_z = tmp_z - j*(lx)*0.1;
    tmp_x = tmp_x + i*(lx)*0.1;
    tmp_z = tmp_z + i*(lz)*0.1;
    
  	if (wsk_func!=0){ // jesli jest funkcja kolizyjna
    
    
    wsk_func(tmp_x,tmp_z,obiekt); // tu mamy dostep do grafiki ale potrzebny dostep do mapy
    // ruch dozwolony wiec mozemy spokojnie sobie zmienic                          
    x = tmp_x;
	z = tmp_z;
	x = tmp_x;
	z = tmp_z;
	


	
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f); 
    
    return;
    }
    else 
    {
    // czyli nie ma funkcji kolizyjnej wpisujemy nowe wartosci
    x = tmp_x;
	z = tmp_z;
	x = tmp_x;
	z = tmp_z;
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);         
    }
}




void CGraphics::TextOut(float x, float y,const char *string)
{
int i, len;
glDisable(GL_LIGHTING);
glColor3f(1.0f,1.0f,0.0f);
glRasterPos3f(x,y,-0.1f);
for (i = 0, len = strlen(string); i < len; i++)
{
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)string[i]);
}
glEnable(GL_LIGHTING);
}

GLuint CGraphics::Texture(int i)
{
   return Textures[i];
}



bool CGraphics::FileExists(const char *strFilename) 
{
  struct stat stFileInfo;
  bool blnReturn;
  int intStat;
  intStat = stat(strFilename,&stFileInfo);
  if(intStat == 0) {
    blnReturn = true;
  } else {
    blnReturn = false;
  }  
  return(blnReturn);
}   



void CGraphics::LoadTextures()
{
     
     
     
  for (int i=0;i<=MAX_TEXTURES;i++)
  {
   std::stringstream filename;
   filename<<"Textures\\"<<i<<".png";
   if (FileExists(filename.str().c_str())) LoadTexture(filename.str().c_str(),Textures[i]);
  }
}



unsigned char* glxReadPNG (const char* file, unsigned int* w, unsigned int* h)
{
	FILE* f;
	unsigned char sig[8];
	png_structp png_ptr;
	png_infop   info_ptr;
	unsigned char* image_data;
	int bit_depth;
	int color_type;
	unsigned int rowbytes;
	png_uint_32 i;
	png_bytepp row_pointers;

	if ((f = fopen(file, "rb")) == NULL)
		return NULL;
	fread(sig, sizeof(*sig), sizeof(sig), f);
	if (!png_check_sig(sig, sizeof(*sig))) {
		fclose(f);
		return NULL;
	}
	if ((png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)) == NULL) {
		fclose(f);
		return NULL;
	}
	if ((info_ptr = png_create_info_struct(png_ptr)) == NULL) {
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fclose(f);
		return NULL;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(f);
		return NULL;
	}
	png_ptr->io_ptr = (png_voidp) f;
	png_set_sig_bytes(png_ptr, 8);

	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, (png_uint_32*)w, (png_uint_32*)h, &bit_depth, &color_type, NULL, NULL, NULL);
	if (color_type & PNG_COLOR_MASK_ALPHA)
		png_set_strip_alpha(png_ptr);
	if (bit_depth > 8)
		png_set_strip_16(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);
	png_read_update_info(png_ptr, info_ptr);

	rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	if ((image_data = (unsigned char*) malloc(*h * rowbytes)) == NULL) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(f);
		return NULL;
	}
	if ((row_pointers = (png_byte **) malloc(*h * sizeof(png_bytep))) == NULL) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(f);
		free(image_data);
		return NULL;
	}

	for (i = 0; i < *h; i++)
		row_pointers[*h - 1 - i] = image_data + i*rowbytes;
	png_read_image(png_ptr, row_pointers);
	free(row_pointers);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(f);
	return image_data;
}





void CGraphics::LoadTexture(const char *filename,GLuint &Textures)
{
   GLuint texture;
   png_structp png_ptr = NULL;
   png_infop info_ptr = NULL;
   png_bytep *row_pointers = NULL;
   int bitDepth, colourType;

   FILE *pngFile = fopen(filename, "rb");

   if(!pngFile)
      return;

   png_byte sig[8];

   fread(&sig, 8, sizeof(png_byte), pngFile);
   rewind(pngFile);//so when we init io it won't bitch
   if(!png_check_sig(sig, 8))
      return;

   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,NULL,NULL);

   if(!png_ptr)
      return;

   if(setjmp(png_jmpbuf(png_ptr)))
      return;

   info_ptr = png_create_info_struct(png_ptr);

   if(!info_ptr)
      return;

   png_init_io(png_ptr, pngFile);

   png_read_info(png_ptr, info_ptr);

   bitDepth = png_get_bit_depth(png_ptr, info_ptr);

   colourType = png_get_color_type(png_ptr, info_ptr);

   if(colourType == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb(png_ptr);

   if(colourType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
      png_set_gray_1_2_4_to_8(png_ptr);

   if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha(png_ptr);

   if(bitDepth == 16)
      png_set_strip_16(png_ptr);
   else if(bitDepth < 8)
      png_set_packing(png_ptr);

   png_read_update_info(png_ptr, info_ptr);

   png_uint_32 width, height;
   png_get_IHDR(png_ptr, info_ptr, &width, &height,
         &bitDepth, &colourType, NULL, NULL, NULL);

   int components;
   switch(colourType) // sprawdzamy na potrzeby opengl zeby ustawic
   {
      case PNG_COLOR_TYPE_GRAY:
         components = 1;
      break;
      case PNG_COLOR_TYPE_GRAY_ALPHA:
         components = 2;
      break;
      case PNG_COLOR_TYPE_RGB:
         components = 3;
      break;
      case PNG_COLOR_TYPE_RGB_ALPHA:
         components = 4;
      break;
      default:
         components = -1;
   }

   if(components == -1)
   {
      if(png_ptr)
         png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      return;
   }

   GLubyte *pixels = (GLubyte *)malloc(sizeof(GLubyte) * (width * height * components));

   row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);

   for(int i = 0; i < height; ++i)
        row_pointers[i] = (png_bytep)(pixels + (i * width * components));

   png_read_image(png_ptr, row_pointers);
   png_read_end(png_ptr, NULL);    



     // numer
     glGenTextures(1, &Textures); // generuj jedna teksture
     glBindTexture(GL_TEXTURE_2D, Textures); 
     // Stwórz teksturê
     
     
     // here we has the problems
    GLuint glcolours;
    (components==4) ? (glcolours = GL_RGBA): (0);
    (components==3) ? (glcolours = GL_RGB): (0);
    (components==2) ? (glcolours = GL_LUMINANCE_ALPHA): (0);
    (components==1) ? (glcolours = GL_LUMINANCE): (0);
    std::cout<<"Komponent:"<<components;
     glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );


if (glcolours!=GL_RGBA)
   {
    // anizodropowe
    if (glutExtensionSupported("GL_EXT_texture_filter_anisotropic")){
    GLfloat fLargest;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
    }
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR );  
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, glcolours, GL_UNSIGNED_BYTE, pixels); 
   } else
   {
     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
     glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, glcolours, GL_UNSIGNED_BYTE, pixels);
   } 

   
     png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
     fclose(pngFile);
     free(row_pointers);
     free(pixels);


}




void CGraphics::LoadPixmaps()
{
     
     
  std::cout<<"Wczytuje pixmapy:\n";
  for (int i=0;i<=MAX_PIXMAPS;i++)
  {
   std::stringstream filename;
   filename<<"Textures\\Pixmaps\\"<<i<<".png";  
   if (FileExists(filename.str().c_str())){
                                            std::cout<<(filename.str().c_str())<<"\n";
                                            LoadPixmap(filename.str().c_str(),Pixmaps[i]);
                                           } 
  }
}





void CGraphics::LoadPixmap(const char *filename,Pixmap_T &Pixmap)
{
     

   png_structp png_ptr = NULL;
   png_infop info_ptr = NULL;
   png_bytep *row_pointers = NULL;
   int bitDepth, colourType;

   FILE *pngFile = fopen(filename, "rb");

   if(!pngFile)
      return;

   png_byte sig[8];

   fread(&sig, 8, sizeof(png_byte), pngFile);
   rewind(pngFile);//so when we init io it won't bitch
   if(!png_check_sig(sig, 8))
      return;

   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,NULL,NULL);

   if(!png_ptr)
      return;

   if(setjmp(png_jmpbuf(png_ptr)))
      return;

   info_ptr = png_create_info_struct(png_ptr);

   if(!info_ptr)
      return;

   png_init_io(png_ptr, pngFile);

   png_read_info(png_ptr, info_ptr);

   bitDepth = png_get_bit_depth(png_ptr, info_ptr);

   colourType = png_get_color_type(png_ptr, info_ptr);

   if(colourType == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb(png_ptr);

   if(colourType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
      png_set_gray_1_2_4_to_8(png_ptr);

   if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha(png_ptr);

   if(bitDepth == 16)
      png_set_strip_16(png_ptr);
   else if(bitDepth < 8)
      png_set_packing(png_ptr);

   png_read_update_info(png_ptr, info_ptr);

   png_uint_32 width, height;
   png_get_IHDR(png_ptr, info_ptr, &width, &height,
         &bitDepth, &colourType, NULL, NULL, NULL);

   int components;
   switch(colourType) // sprawdzamy na potrzeby opengl zeby ustawic
   {
      case PNG_COLOR_TYPE_GRAY:
         components = 1;
      break;
      case PNG_COLOR_TYPE_GRAY_ALPHA:
         components = 2;
      break;
      case PNG_COLOR_TYPE_RGB:
         components = 3;
      break;
      case PNG_COLOR_TYPE_RGB_ALPHA:
         components = 4;
      break;
      default:
         components = -1;
   }

   if(components == -1)
   {
      if(png_ptr)
         png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      return;
   }

   Pixmap.pixels = (GLubyte *)malloc(sizeof(GLubyte) * (width * height * components));

   row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);

   for(int i = 0; i < height; ++i)
        row_pointers[i] = (png_bytep)(Pixmap.pixels + (i * width * components));

   png_read_image(png_ptr, row_pointers);
   png_read_end(png_ptr, NULL);    

   

     // numer
     // Stwórz teksturê
     
     
     // here we has the problems
    GLuint glcolours;
    (components==4) ? (glcolours = GL_RGBA): (0);
    (components==3) ? (glcolours = GL_RGB): (0);
    (components==2) ? (glcolours = GL_LUMINANCE_ALPHA): (0);
    (components==1) ? (glcolours = GL_LUMINANCE): (0);
    
    Pixmap.width=width;
    Pixmap.height=height;
    Pixmap.format=GL_UNSIGNED_BYTE;
    Pixmap.type=components;
    
     png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
//     glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, glcolours, GL_UNSIGNED_BYTE, pixels);
     fclose(pngFile);
//     free(row_pointers);
    // free(pixels);


}


void CGraphics::DrawPixmap(int num)
    {
//    std::cout<<"rysuje pixmape"<<Pixmaps[num].pixels[2];
     float x=0.0f;
     float y=0.0f;
     glDisable(GL_LIGHTING);
     glColor3f(1.0f,1.0f,0.0f);
     glRasterPos3f(x,y,-0.1f);
     glDrawPixels(Pixmaps[num].width,Pixmaps[num].height,GL_RGB,Pixmaps[num].format,Pixmaps[num].pixels);
     glEnable(GL_LIGHTING);
     
     }

void CGraphics::LoadFlashLight()
{
    const char *name = "lightmap.bmp";
	GLfloat eyePlaneS[] =  {1.0f, 0.0f, 0.0f, 0.5f};
	GLfloat eyePlaneT[] =  {0.0f, 1.0f, 0.0f, 0.5f};
	GLfloat eyePlaneR[] =  {0.0f, 0.0f, 1.0f, 0.0f};
	GLfloat eyePlaneQ[] =  {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat borderColor[4] = {0.6f, 0.6f, 0.6f, 0.6f};

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
	glTexGenfv(GL_S,GL_EYE_PLANE,eyePlaneS);
	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
	glTexGenfv(GL_T,GL_EYE_PLANE,eyePlaneT);
	glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
	glTexGenfv(GL_R,GL_EYE_PLANE,eyePlaneR);
	glTexGeni(GL_Q,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
	glTexGenfv(GL_Q,GL_EYE_PLANE,eyePlaneQ);

	glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);
    glEnable(GL_TEXTURE_GEN_Q);

    AUX_RGBImageRec *Image;
    Image = auxDIBImageLoad(name);
    glGenTextures(1,&projTexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,borderColor);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);


    if(Image)
    {
        if(Image->data)
            free(Image->data);
        free(Image);
    }

}
