#include "CObject.h"
#include "CDoor.h"
#include "CEnemy.h"
#include "CItem.h"
#include "CPlayer.h"
#include "stdio.h"
#include <iostream>

list<CObject*> CObject::ListaObiektow;
void CObject::Add(CObject *obiekt) // inne obiekty
{
     // moze i ladniejsza jest jakas metoda :D ale ja innej nie znam
    std::cout<<(obiekt->Category==CAT_ITEM);
    switch(obiekt->Category)
    {
    case CAT_ENEMY: CEnemy::Add((CEnemy*)obiekt); break;
    case CAT_ITEM:  CItem::Add((CItem*)obiekt); break;
    case CAT_DOOR:  CDoor::Add((CDoor*)obiekt); break;    
    default:        ListaObiektow.push_back(obiekt); // pozostale obiekty laduja na liscie obiektow
    }
    return;
}



void CObject::Objects_Render()
{
    CEnemy::Enemies_Render(); // rysuj wrogow
    CItem::Items_Render(); // rysuj wrogow
    CDoor::Doors_Render(); // rysuj drzwi
    // pozostale obiekty
    
    list<CObject*>::iterator it;
    
    for(it = ListaObiektow.begin() ; it != ListaObiektow.end() ; ++it) // dla kazdego wroga sprawdz 
    {
           (*it)->Render();
    } 
}


void CObject::Objects_Update()
{
    
    CEnemy::Enemies_Update(); // rysuj wrogow
    CItem::Items_Update(); // rysuj wrogow
    CDoor::Doors_Update(); // rysuj wrogow
    // pozostale obiekty narazie gracze
    
    list<CObject*>::iterator it;
    
    for(it = ListaObiektow.begin() ; it != ListaObiektow.end() ; ++it) // dla kazdego wroga sprawdz 
    {
           (*it)->Update();
    } 



}

bool CObject::Objects_Check(float &s_x,float &s_z,float &x,float &z,CObject *obiekt)
{
    CEnemy::Enemies_Check(s_x,s_z,x,z,obiekt); // rysuj wrogow
    CItem::Items_Check(s_x,s_z,x,z,obiekt); // rysuj wrogow
    CDoor::Doors_Check(s_x,s_z,x,z,obiekt); // rysuj wrogow
}


void CObject::Rotate_Players()
    {
    // obracamy widok graczy
        // pozostale obiekty
    
    list<CObject*>::iterator it;
    
    for(it = ListaObiektow.begin() ; it != ListaObiektow.end() ; ++it) // dla kazdego wroga sprawdz 
    {
           if (((*it)->Category)==CAT_PLAYER) {
                                // wiecej kodu ale ladniej wyglada
                                CPlayer *obiekt;
                                obiekt=(CPlayer*)(*it);   // tak wiemy ze to ten obiekt
                                obiekt->Rotate();
                                }
    } 
    
    }



float CObject::Kwadrat(float x)   { x = x*x;  return x; }






void CObject::Objects_Remove()
{
    CItem::Items_Remove();
    CDoor::Doors_Remove();
    CEnemy::Enemies_Remove();
 // graczy nie usuwamy :-)
    list<CObject*>::iterator it;  
    for(it = ListaObiektow.begin() ; it != ListaObiektow.end() ; ++it) // dla kazdego wroga sprawdz 
    {
           if (((*it)->Category)==CAT_PLAYER) {
                                // wiecej kodu ale ladniej wyglada
                                CPlayer *obiekt;
                                obiekt=(CPlayer*)(*it);   // tak wiemy ze to ten obiekt
                                obiekt->Restart();
                                }
    } 
}
