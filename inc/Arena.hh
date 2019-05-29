#ifndef ARENA_HH
#define ARENA_HH

#include <iostream>

#include "SI.hh"

/*******************************/
//3 przypadki - win, lose, draw
//
/*******************************/
enum class Zufall
  {
    END_X,
    END_O,
    END_DRAW
  };

/*******************************/
//Funkcja do obslugiwania gry
//
/*******************************/
class Arena
{
public:
  static void startThaGame(Plansza& battlefield);       //Petla gry
  static void callMeister(Zufall stan);                 //Wyswietl status gry na konec
};



#endif
