#include <iostream>

#include "Plansza.hh"
#include "Arena.hh"

using namespace std;

/*******************************/
//Wywolaj gre, gdzie tablica ma
//rozmiar podanym przez user
/*******************************/
int main()
{
  int size;
  cout<<"Podaj rozmiar planszy: ";
  cin>>size;
  cout<<endl;

  Plansza battlefield(size, size);
  Arena::startThaGame(battlefield);       //Rozpocznij gre
}
