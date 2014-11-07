#ifndef CDOOR
#define CDOOR
#include "CObject.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CSound.h"
#include <list>

#include <list>
using namespace std;

// WKONCU ABSTRAKCYJNA KLASA PRZECIWNIK
class CDoor: public CObject
{
  private:
  static list<CDoor*> ListaDrzwi;         // lista naszych wrogow :D hehe
  protected:
  CDoor() {Category=CAT_DOOR;}// dziedziczymy ten konstruktor
  float x,z,y;
  float kat;
    ALfloat SoundPos[3];
  ALfloat SoundVel[3];
      enum E_STATE { E_CLOSED,E_OPENING,E_CLOSING,E_OPENED };
  E_STATE State;
  virtual bool Trigger(CPlayer &obiekt) {
          } // czyli bedzie umieral jak umrze ustawi na DIED
  
  public:
  int Enemy_Number;
  static void Add(CDoor *obiekt);
  static void Doors_Render();    // dla listy obiektow
  static void Doors_Update();    // dla listy obiektow
  static void Doors_Remove();
  static bool Doors_Check(float &s_x,float &s_z,float &x,float &z,CObject *obiekt=NULL);     // dla listy obiektow
  virtual void Render() =0;
  virtual void Update() =0;  

};


#endif
