#ifndef CITEM
#define CITEM
#include "CObject.h"
#include <list>
#include "CEnemy.h"
#include "CPlayer.h"
#include "CSound.h"


using namespace std;

// WKONCU ABSTRAKCYJNA KLASA PRZECIWNIK
class CItem: public CObject // stad mamy Kategorie
{
  private:
  static list<CItem*> ListaPrzedmiotow;         // lista naszych wrogow :D hehe
  static float Kwadrat(float x);
  protected:
  CItem() {Category=CAT_ITEM; State=E_NORMAL;}// dziedziczymy ten konstruktor
  enum E_STATE { E_NORMAL,E_PICKED_UP };
  E_STATE State;
  float x,z;
  static unsigned int picked;
// dzwiek
  ALfloat SoundPos[3]; // nasz glos
  ALfloat SoundVel[3]; // nasz glos
  float kat;

  public:
  int Enemy_Number;
  static void Add(CItem *obiekt);
  static void Items_Render();    // dla listy obiektow
  static void Items_Update();    // dla listy obiektow
  static void Items_Remove();
  static bool Items_Check(float &s_x,float &s_z,float &x,float &z,CObject *obiekt=NULL);     // dla listy obiektow
  static bool Check_Aim(float x,float z);       // sprawdzamy czy wrog lezy w danym kacie
  
  static unsigned int Items_Picked();    // dla listy obiektow
  static unsigned int Items_Total();    // dla listy obiektow
  
  virtual void Render() =0;
  virtual void Update() =0;  
  virtual void Pick_Up(CPlayer &Player) {

          } // czyli bedzie umieral jak umrze ustawi na DIED

};

#endif

