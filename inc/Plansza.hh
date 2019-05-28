#ifndef PLANSZA_HH
#define PLANSZA_HH

#include <iostream>
#include <vector>

//SEITE - KRZYRZYK = TRUE, KOLKO = FALSE


class Plansza
{
public:
  std::vector<std::vector<char>> board;
  bool isOn;
  bool turn;
  int zwyciezca;
  
  Plansza(int wymX, int wymY);

  void makeRuch();
  void checkDraw();
  void checkWin();
  void display();
  
  bool retWinner(bool seite){ if(seite) zwyciezca = 1; else zwyciezca = -1; return seite; };
};


#endif
