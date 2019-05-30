#ifndef SI_HH
#define SI_HH

#include <vector>

#include "Stale.hh"
#include "Plansza.hh"

/*******************************/
//Struktura Wezel, ulatwiajacy 
//prace z alg minimax
/*******************************/
struct Wezl
{
  int X;
  int Y;
  int punkty;        //Ile pkt ustawiamy

  Wezl(int x, int y): X{x}, Y{y}
  {};

  Wezl() = default;
};

/*******************************/
//Typ, ze statycznymi metodami
//do wykonania ruchu AI
/*******************************/
class SI
{
public:
  static Wezl bestRuch(Plansza& glowna, bool gracz);                //Znajdz najlepszy ruch
  static Wezl bestRuch(Plansza& glowna, bool gracz, int licznik, int alfa, int beta);
  static void zrobTo(Plansza& glowna);                              //Zrob ten ruch
};


#endif
