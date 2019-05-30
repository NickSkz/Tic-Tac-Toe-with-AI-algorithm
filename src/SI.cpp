#include "SI.hh"
#include <iostream>


/*******************************/
//Wykonaj ruch na oficialnej tab
//+ sprawdz czy koniec
/*******************************/
void SI::zrobTo(Plansza& glowna)
{
  Wezl najlepszy = bestRuch(glowna, false, licznik, -99999, 99999);   //Ustaw najlepszy wezel
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

  
  int tenRuch = -99;           
  if(gracz == true)                               //Gdy X to chcemy minimalizowac rezultat
    {
      int najWyn = 99999;
      for(unsigned int idx = 0; idx < ruchy.size(); ++idx)   
	{// std::cout<<ruchy[idx].punkty<<std::endl;
	  if(ruchy[idx].punkty < najWyn)          //Wiec gdy najwyz wyn wiekszy od obecnego wezl
	    {	      
	      najWyn = ruchy[idx].punkty;        //Ustaw obecny jako najlepszy i zapamietaj jego idx
	      tenRuch = idx;
	    }
	}
    }
  else                                    //Gdy Y to maxymalizujemy rezultat
    {
      int najWyn = -99999;
      for(unsigned int idx = 0; idx < ruchy.size(); ++idx)   
	{// std::cout<<ruchy[idx].punkty<<std::endl;
	  if(ruchy[idx].punkty > najWyn)     //Gdy najWynik mniejszy od obecnego
	    {
	      najWyn = ruchy[idx].punkty;   //Ustaw obecny jako najlepszy i zapamietaj jego idx
	      tenRuch = idx;	      
	    }
	}
    }

  return ruchy[tenRuch];               //Zwroc ten najlepszy wezel dla danej tury
  
}





/*******************************/
//To samo co powyzej, jedyna
//roznica to czysty minimax
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
  if(glowna.zwyciezca == 0) { buff.punkty = 0; return buff; }  	//Jesli remis zworc 0	 
  if(glowna.zwyciezca == 1) { buff.punkty = -50; return buff; } //Jesli wygrana X, daj -50 


  for(unsigned int idx = 0; idx < glowna.board.size(); ++idx)     //Przeszukaj cala tablice
    {      
      for(unsigned int jdx = 0; jdx < glowna.board.size(); ++jdx)
	{
	  if(glowna.board[idx][jdx] == ' ')                       //Gdy puste pole
	    {
	      Wezl temp(idx, jdx);                          //Stworz wezel, z obecnymi x,y   
	      
	      if(gracz){ glowna.board[idx][jdx] = 'X'; glowna.ostatni.X = idx; glowna.ostatni.Y = jdx; }             //W zaleznosci czyja tura wstaw X albo O, potem bedzie usunieta, + ustaw ostatni
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






