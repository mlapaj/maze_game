#ifndef CENEMY
#define CENEMY
#include "CObject.h"
#include "CEnemy.h"
#include "CSound.h"
#include "CPlayer.h"


#include <list>
using namespace std;

// WKONCU ABSTRAKCYJNA KLASA PRZECIWNIK
class CEnemy: public CObject
{
  private:
  static list<CEnemy*> ListaWrogow;         // lista naszych wrogow :D hehe
  protected:
  CEnemy() {Category=CAT_ENEMY;}// dziedziczymy ten konstruktor
  float x,z;
  float kat;
  static unsigned int killed;
  ALfloat SoundPos[3];
  ALfloat SoundVel[3];
  
  enum E_STATE { E_WALKING,E_DYING,E_DIED,E_TRIGGERED,E_SHOOTING };
  E_STATE State;
  virtual void Die() {
          if ((State!=E_DIED) && (State!=E_DYING)) { State=E_DYING; killed+=1;}

          } // czyli bedzie umieral jak umrze ustawi na DIED
  
  public:
  int Enemy_Number;
  static void Add(CEnemy *obiekt);
  static unsigned int Enemies_Killed();    // dla listy obiektow
  static unsigned int Enemies_Total();    // dla listy obiektow
  static void Enemies_Render();    // dla listy obiektow
  static void Enemies_Update();    // dla listy obiektow
  static void Enemies_Remove();
  static bool Enemies_Check(float &s_x,float &s_z,float &x,float &z,CObject *obiekt=NULL);     // dla listy obiektow
  static bool Check_Aim(float x,float z,float katx,float katy);       // sprawdzamy czy wrog lezy w danym kacie
  virtual void Render() =0;
  virtual void Update() =0;  
  virtual void Trigger(CPlayer &player) = 0;
};

#endif
