#include "SI.hh"
#include <iostream>

Wezl SI::bestRuch(Plansza& glowna, bool gracz)
{
  std::vector<Wezl> ruchy;

  if(gracz)  glowna.turn = false;         //Z powodu takiego a nie innego zrobienia checkWin()
  else glowna.turn = true;

  glowna.zwyciezca = -99;

  glowna.checkWin();                         //Sprawdz wygrana, jesli jest daj 100 punktow
  if(glowna.zwyciezca == -99) glowna.checkDraw();
  
  Wezl buff;                                  //POTENC BLAD - MOZE NIE BYC zmiany tury
  if(glowna.zwyciezca == -1){ buff.punkty = 100; return buff; }
  if(glowna.zwyciezca == 0) { buff.punkty = 0; return buff; }
  if(glowna.zwyciezca == 1) { buff.punkty = -50; return buff; }


  for(unsigned int idx = 0; idx < glowna.board.size(); ++idx)
    {
      for(unsigned int jdx = 0; jdx < glowna.board.size(); ++jdx)
	{
	  if(glowna.board[idx][jdx] == ' ')
	    {
	      Wezl temp;
	      temp.X = idx;
	      temp.Y = jdx;                                          
	      
	      if(gracz){ glowna.board[idx][jdx] = 'X'; } 
	      else{ glowna.board[idx][jdx] = 'O'; }      //By sie nam tura zm

	      if(gracz){ temp.punkty = bestRuch(glowna, false).punkty;}
	      else{ temp.punkty = bestRuch(glowna, true).punkty;}
	      // std::cout<<temp.punkty<<std::endl;
	      ruchy.push_back(temp);
	      glowna.board[idx][jdx] = ' ';
	    }
	}
    }

  
  int tenRuch = -99;
  if(gracz == true)
    {
      int najWyn = 99999;
      for(unsigned int idx = 0; idx < ruchy.size(); ++idx)
	{// std::cout<<ruchy[idx].punkty<<std::endl;
	  if(ruchy[idx].punkty < najWyn)
	    {
	      tenRuch = idx;
	      najWyn = ruchy[idx].punkty;
	    }
	}
    }
  else
    {
      int najWyn = -99999;
      for(unsigned int idx = 0; idx < ruchy.size(); ++idx)
	{// std::cout<<ruchy[idx].punkty<<std::endl;
	  if(ruchy[idx].punkty > najWyn)
	    {
	      tenRuch = idx;
	      najWyn = ruchy[idx].punkty;
	    }
	}
    }

  return ruchy[tenRuch];
  
}


void SI::zrobTo(Plansza& glowna)
{
  Wezl najlepszy = bestRuch(glowna, false);
  // std::cout<<najlepszy.punkty<<"<----------"<<std::endl;
  glowna.board[najlepszy.X][najlepszy.Y] = 'O';

  glowna.turn = false;
  glowna.isOn = true;
  glowna.zwyciezca = -99;
  
  glowna.checkWin();
  glowna.checkDraw();

  glowna.turn = true;
}
