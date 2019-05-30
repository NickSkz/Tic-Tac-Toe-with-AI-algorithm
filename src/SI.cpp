#include "SI.hh"
#include <iostream>


/*******************************/
//Wykonaj ruch na oficialnej tab
//+ sprawdz czy koniec
/*******************************/
void SI::zrobTo(Plansza& glowna)
{
  int X{ bestRuch(glowna, false, licznik, -99999, 99999).X };
  int Y{ bestRuch(glowna, false, licznik, -99999, 99999).Y };
  
  glowna.board[X][Y] = 'O';        //Wstaw O w najlepsze X i Y
  glowna.ostatni.X = X; glowna.ostatni.Y = Y;    //Po to by dzialalo checkWin()

  glowna.turn = false;                  //Kalibrujemy, tura - O, i gra idzie dalej
  glowna.isOn = true;                   
  glowna.zwyciezca = -99;               //Oficjalnie jeszcze nie wiemy kto wygral wiec -99
  
  glowna.checkWin();                    //Sprawdz win, draw
  glowna.checkDraw();

  glowna.turn = true;                  //Zmien ture
}



/*******************************/
//Znajdz rekurencyjnie najlepszy
//ruch, za pomoca minimax
/*******************************/
Wezl SI::bestRuch(Plansza& glowna, bool gracz, int licznik, int alfa, int beta)
{
  --licznik;                           //Zmniejsz licznik o 1
  std::vector<Wezl> ruchy;             //Tablica z ruchami mozliwymi
  
  if(gracz)  glowna.turn = false;         //Z powodu takiego a nie innego zrobienia checkWin()
  else glowna.turn = true;

  glowna.zwyciezca = -99;

  glowna.checkWin();                         //Sprawdz wygrana
  if(glowna.zwyciezca == -99) glowna.checkDraw(); // Jak nie wygrana to moze remis
  
  Wezl buff;             
  if(glowna.zwyciezca == -1){ buff.punkty = 100; return buff; } //Jesli wygrana O, daj 100
  if(glowna.zwyciezca == 0) { buff.punkty = 0; return buff; }	//Jesli remis zworc 0	 
  if(glowna.zwyciezca == 1) { buff.punkty = -50; return buff; }	//Jesli wygrana X, daj -50
  if(licznik == 0) { buff.punkty = 0; return buff; } //Jak licznik bedzie 0 potraktuj jak remis

  
  for(unsigned int idx = 0; idx < glowna.board.size(); ++idx)  //Przeszukaj cala tablice
    {
      for(unsigned int jdx = 0; jdx < glowna.board.size(); ++jdx)
	{
	  if(glowna.board[idx][jdx] == ' ')   //Gdy bedize puste pole
	    {
	      Wezl temp(idx, jdx);            //Stworz wezel pomocniczy z obecnymi x i y
     
	      if(gracz){ glowna.board[idx][jdx] = 'X'; glowna.ostatni.X = idx; glowna.ostatni.Y = jdx; }    //W zaleznosci od tury wstawiamy X albo O, ustalajac zm odp. za ostatnie wstawienie
	      else{ glowna.board[idx][jdx] = 'O'; glowna.ostatni.X = idx; glowna.ostatni.Y = jdx; }
	      
	      if(gracz){ temp.punkty = bestRuch(glowna, false, licznik, alfa, beta).punkty;}
	      else{ temp.punkty = bestRuch(glowna, true, licznik, alfa, beta).punkty;}	//Wywolaj rekurencyjnie minimax dla nizszych wezlow, zmieniajac naprzemiennie ture      	     
	      
	      ruchy.push_back(temp);       //dodaj wezel do listy mozliwych
	      glowna.board[idx][jdx] = ' ';    //Wyczysc to co wstawiles, by nie zaklocilo gry
	      
	      if(gracz)                                        //Obcinanie alfa-beta
		{
		  if(beta > temp.punkty) beta = temp.punkty;   //Jak beta wieksze, zamien
		  //  std::cout<<alfa<<"  "<<beta<<std::endl;
		  if(beta <= alfa) break;                //Jak wczesniej mielismy lepsze, przerwij
		}
	      else
		{		 
		  if(alfa < temp.punkty) alfa = temp.punkty;   //Jak alfa mniejsze zamien
		  if(beta <= alfa) break;
		}
	      
	    } 
	}
    }

  int najWyn;                        //Zmienna przechowujaca najkorzystniejszy wynik w zal od tury
  if(gracz) najWyn = 99999;
  else najWyn = -99999;

  
  int tenRuch;           
  if(gracz)                               //Gdy X to chcemy minimalizowac rezultat
    {
      for(unsigned int idx = 0; idx < ruchy.size(); ++idx)   
	{// Wiec gdy dany wezel ma wart mniejsza niz najmniejszy wynik, on bedzie najmn, zapisujem idx
	  if(ruchy[idx].punkty < najWyn){ najWyn = ruchy[idx].punkty; tenRuch = idx; }
	}
    }
  else                                    //Gdy Y to maxymalizujemy rezultat
    {
      for(unsigned int idx = 0; idx < ruchy.size(); ++idx)   
	{// Wiec gdy dany wezel ma wart wieksza niz najwiekszy wynik, on bedzie najw, zapisujem idx
	  if(ruchy[idx].punkty > najWyn){ najWyn = ruchy[idx].punkty; tenRuch = idx; }
	}
    }

  return ruchy[tenRuch];               //Zwroc ten najlepszy wezel dla danej tury
  
}









