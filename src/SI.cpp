#include "SI.hh"
#include <iostream>

/*******************************/
//Znajdz rekurencyjnie najlepszy
//ruch, za pomoca minimax
/*******************************/
Wezl SI::bestRuch(Plansza& glowna, bool gracz)
{
  std::vector<Wezl> ruchy;               //Tablica z ruchami mozliwymi

  if(gracz) glowna.turn = false;         //Z powodu takiego ze zmienilismy ture, a chcemy spr poprzedni
  else glowna.turn = true;

  glowna.zwyciezca = -99;

  glowna.checkWin();                         //Sprawdz wygrana
  if(glowna.zwyciezca == -99) glowna.checkDraw();  //Jezlein nie wygrana moze remis
  
  Wezl buff;                               //Buff do zwracania
  if(glowna.zwyciezca == -1){ buff.punkty = 100; return buff; } //Jesli wygrana O, daj 100
  if(glowna.zwyciezca == 0) { buff.punkty = 0; return buff; }  //Jesli remis zworc 0
  if(glowna.zwyciezca == 1) { buff.punkty = -50; return buff; }//Jesli wygrana X, daj -50


  for(unsigned int idx = 0; idx < glowna.board.size(); ++idx)     //Przeszukaj cala tablice
    {
      for(unsigned int jdx = 0; jdx < glowna.board.size(); ++jdx)
	{
	  if(glowna.board[idx][jdx] == ' ')                       //Gdy puste pole
	    {
	      Wezl temp;                                       //Stworz wezel, z obecnymi x,y
	      temp.X = idx;
	      temp.Y = jdx;                                          
	      
	      if(gracz){ glowna.board[idx][jdx] = 'X'; glowna.ostatni.X = idx; glowna.ostatni.Y = jdx; }            //W zaleznosci czyja tura wstaw X albo O, potem bedzie usunieta, + ustaw ostatni
	      else{ glowna.board[idx][jdx] = 'O'; glowna.ostatni.X = idx; glowna.ostatni.Y = jdx; }    

	      if(gracz){ temp.punkty = bestRuch(glowna, false).punkty;}  //Rekurencyjnie sprawdz punkty
	      else{ temp.punkty = bestRuch(glowna, true).punkty;}      //Zmien rowniez ture
	      // std::cout<<temp.punkty<<std::endl;
	      ruchy.push_back(temp);            //Zwroc wezel, z przypisanymi juz punktami z rekurencji
	      glowna.board[idx][jdx] = ' ';     //Napraw to co wstawilismy
	    }
	}
    }

  
  int tenRuch = -99;
  if(gracz == true)            //W zaleznosci czy X czy O
    {
      int najWyn = 99999;
      for(unsigned int idx = 0; idx < ruchy.size(); ++idx) //Dla wszystkich ruchow
	{// std::cout<<ruchy[idx].punkty<<std::endl;
	  if(ruchy[idx].punkty < najWyn)             //Jak dla X najWyn jest wiekszy od obecnego
	    {
	      tenRuch = idx;
	      najWyn = ruchy[idx].punkty;            //Ustaw obecny jako najmniejszy + zapisz jego idx
	    }
	}
    }
  else
    {
      int najWyn = -99999;
      for(unsigned int idx = 0; idx < ruchy.size(); ++idx)
	{// std::cout<<ruchy[idx].punkty<<std::endl;
	  if(ruchy[idx].punkty > najWyn)     //Jak dla O najWyn jest mniejszy od obecnego
	    {
	      tenRuch = idx;
	      najWyn = ruchy[idx].punkty;    //Ustaw obecny jako najwiekszy, + znaj jego index
	    }
	}
    }

  return ruchy[tenRuch];                   //Zwroc najlepszy ruch
  
}








/*******************************/
//To samo co powyzej, jedyna
//roznica to zliczanie rekurencji
/*******************************/
Wezl SI::bestRuch(Plansza& glowna, bool gracz, int licznik)
{ // std::cout<<licznik<<std::endl;
  --licznik;                           //Zmniejsz licznik o 1
  std::vector<Wezl> ruchy;
  
  if(gracz)  glowna.turn = false;         //Z powodu takiego a nie innego zrobienia checkWin()
  else glowna.turn = true;

  glowna.zwyciezca = -99;

  glowna.checkWin();                         //Sprawdz wygrana, jesli jest daj 100 punktow
  if(glowna.zwyciezca == -99) glowna.checkDraw();
  
  Wezl buff;             
  if(glowna.zwyciezca == -1){ buff.punkty = 100; return buff; }
  if(glowna.zwyciezca == 0) { buff.punkty = 0; return buff; }
  if(glowna.zwyciezca == 1) { buff.punkty = -50; return buff; }
  if(licznik == 0) { buff.punkty = 0; return buff; } //Jak licznik bedzie 0 potraktuj jak remis
  
  for(unsigned int idx = 0; idx < glowna.board.size(); ++idx)
    {
      for(unsigned int jdx = 0; jdx < glowna.board.size(); ++jdx)
	{
	  if(glowna.board[idx][jdx] == ' ')
	    {
	      Wezl temp;
	      temp.X = idx;
	      temp.Y = jdx;                                          
	      
	      if(gracz){ glowna.board[idx][jdx] = 'X'; glowna.ostatni.X = idx; glowna.ostatni.Y = jdx; } 
	      else{ glowna.board[idx][jdx] = 'O'; glowna.ostatni.X = idx; glowna.ostatni.Y = jdx; }
	      
	      if(gracz){ temp.punkty = bestRuch(glowna, false, licznik).punkty;}
	      else{ temp.punkty = bestRuch(glowna, true, licznik).punkty;}
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

/*******************************/
//Wykonaj ruch na oficialnej tab
//+ sprawdz czy koniec
/*******************************/
void SI::zrobTo(Plansza& glowna)
{
  Wezl najlepszy = bestRuch(glowna, false, licznik);   //Ustaw najlepszy wezel
  // std::cout<<najlepszy.punkty<<"<----------"<<std::endl;
  glowna.board[najlepszy.X][najlepszy.Y] = 'O';        //Wstaw O w najlepsze X i Y
  glowna.ostatni.X = najlepszy.X; glowna.ostatni.Y = najlepszy.Y;    //Po to by dzialalo checkWin()

  glowna.turn = false;                  //Kalibrujemy, tura - O, i gra idzie dalej
  glowna.isOn = true;                   
  glowna.zwyciezca = -99;               //Oficjalnie jeszcze nie wiemy kto wygral wiec -99
  
  glowna.checkWin();                    //Sprawdz win, draw
  glowna.checkDraw();

  glowna.turn = true;                  //Zmien ture
}
