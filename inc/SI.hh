#ifndef SI_HH
#define SI_HH

#include <vector>

#include "Plansza.hh"

struct Wezl
{
  int X;
  int Y;
  int punkty;
};

class SI
{
public:
  static Wezl bestRuch(Plansza& glowna, bool gracz);
  static Wezl bestRuch(Plansza& glowna, bool gracz, int licznik);
  static void zrobTo(Plansza& glowna);
};


#endif
