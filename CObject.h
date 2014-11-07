#ifndef COBJECT
#define COBJECT

#include <list>
using namespace std;

// WKONCU ABSTRAKCYJNA KLASA PRZECIWNIK
class CObject
{
  private:

  static list<CObject*> ListaObiektow;         // lista naszych wrogow :D hehe
  protected:
  static float CObject::Kwadrat(float x);
  float x,z;
  float kat;
  enum E_CATEGORY { CAT_NONE,CAT_ENEMY,CAT_ITEM,CAT_PLAYER,CAT_DOOR};

  public:
           E_CATEGORY Category; // dla testow
  static void Add(CObject *obiekt);
  static void CObject::Objects_Remove();
  static void Objects_Render();    // dla listy obiektow
  static void Objects_Update();    // dla listy obiektow
  static bool Objects_Check(float &s_x,float &s_z,float &x,float &z,CObject *obiekt=NULL);     // dla listy obiektow
  static void CObject::Rotate_Players();
  static bool Check_Aim(float x,float z);       // sprawdzamy czy wrog lezy w danym kacie
  virtual void Render() =0;
  virtual void Update() =0;  

  bool Check_Aim(float x,float z,float katx,float katy);
};

#endif
