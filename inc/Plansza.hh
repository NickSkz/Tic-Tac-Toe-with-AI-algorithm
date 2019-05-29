#ifndef PLANSZA_HH
#define PLANSZA_HH

#include <iostream>
#include <vector>

/*******************************/
//UWAGA! - X == true, O == false
//
/*******************************/


/*******************************/
//Struktura, uzyta do okreslenia
//ostatnio zajetego pola
/*******************************/
struct Pole
{
  int X;
  int Y;
};



/*******************************/
//Typ plansza, definiujacy para-
//metry zwiazane z rozgrywka
/*******************************/
class Plansza
{
public:
  std::vector<std::vector<char>> board;            //Glowna tablica gry
  bool isOn;                                       //Czy gra plynie
  bool turn;                                       //Czyja tura jest X=true, O=false
  int zwyciezca;                                   //Kto wygral X=1, O=-1, DRAW=0        
  Pole ostatni;  
  
  Plansza(int wymX, int wymY);                     //Buduje tablice o wymiarach

  void makeRuch();                                 //Ruch gracza
  void checkDraw();                                //Czy remis
  void checkWin();                                 //Czy wygrana
  void display();                                  //Wyswietl tablice
  
  bool retWinner(bool seite){ if(seite) zwyciezca = 1; else zwyciezca = -1; return seite; }; //Zwraca zwyciezce
};


#endif
