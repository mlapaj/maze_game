#include <iostream>
#include "CDebug.h"
using namespace std;

CDebug::CDebug(bool value, const char *t_nazwa)
{
 is_debug=value;
 nazwa = new char[strlen(t_nazwa)];
 strcpy(nazwa,t_nazwa);

}

void CDebug::Notice(const char *tekst)
{
cout<<"Info "<<nazwa<<": "<<tekst<<endl;
}

CDebug::~CDebug()
{
  delete nazwa;
}

                  
void CDebug::operator<<(const char *tekst)
{
cout<<"Info "<<nazwa<<": "<<tekst<<endl; 
}
 
