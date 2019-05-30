#include "Arena.hh"

#include <ctime>

using namespace std;


/*******************************/
//Glowna petla gry
//na zmiane X i AI
/*******************************/
void Arena::startThaGame(Plansza& battlefield)
{
  clock_t start, stop;
  
  while(battlefield.isOn)                       //Dopoki sa wolne pola
    {
      battlefield.display();                    //Wyswietl tablice
      
      if(battlefield.turn)                      //Gdy X
	{
	  battlefield.makeRuch();               //Rusz sie gracz
	  battlefield.turn = !battlefield.turn; //Zmien ture

	  cout<<"\n\n";
	}
      else                                      //Gdy O
	{
	  cout<<"Ruch: O[SI]\n\n\n";
	  start = clock();
	  SI::zrobTo(battlefield);              //Niech AI wykona ruch
	  stop = clock();
	  cout<<"Ruch wykonano w czasie: "<<double(stop-start)/CLOCKS_PER_SEC<<endl;
	}
      if(!battlefield.isOn)                     //Gdy koniec, wyswietl odpowiednia grafike
	{
	  if(battlefield.zwyciezca == 1) callMeister(Zufall::END_X);
	  if(battlefield.zwyciezca == -1) callMeister(Zufall::END_O);
	  if(battlefield.zwyciezca == 0) callMeister(Zufall::END_DRAW);
	}
    }

}



/*******************************/
//Switch w zaleznosci od stanu
//
/*******************************/
void Arena::callMeister(Zufall stan)
{
  switch(stan)
    {
    case Zufall::END_X:
      {
	cout<<"|********************|\n";
	cout<<"|     Wygrywa X!     |\n";
	cout<<"|********************|\n";
	break;
      }

    case Zufall::END_O:
      {
	cout<<"|********************|\n";
	cout<<"|     Wygrywa O!     |\n";
	cout<<"|********************|\n";
	break;
      }

    case Zufall::END_DRAW:
      {
	cout<<"|******************|\n";
	cout<<"|      REMIS!      |\n";
	cout<<"|******************|\n";
	break;
      }
    }

  cin.clear();
  cin.ignore(256, '\n');                       //Czekaj na reakcje uzytkownika i zamknij program
  cin.get();
}
