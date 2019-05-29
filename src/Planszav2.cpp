#include "Plansza.hh"

using namespace std;

/*******************************/
//Stworz Plansze XxY
//
/*******************************/
Plansza::Plansza(int wymX, int wymY)
{ 
  vector<char> temp;
  
  for(int idx = 0; idx < wymX; ++idx)
    {
      board.push_back(temp);
      
      for(int jdx = 0; jdx < wymY; ++jdx)
	{
	  board[idx].push_back(' ');
	}
    }

  zwyciezca = -99;                          //Ustaw zwyciezce na cos innego - na nikogo
  isOn = true;                              //Odpal gre, zaczyna X
  turn = true;
}


void Plansza::makeRuch()
{
  while(true)                              //Dopoki nie bedzie dobrego ruchu
    {
      int X, Y;
      turn ? cout<<"Ruch: X\n" : cout<<"Ruch: Y\n"; 
      cin>>X;
      cin>>Y;

      if(turn)                             //W zaleznosci od tury, jak bedzie miejsce wykonaj ruch
	{
	  if(board[X][Y] == ' ')
	    {
	      board[X][Y] = 'X';
	      ostatni.X = X;
	      ostatni.Y = Y;
	      break;
	    }
	  else
	    {
	      cout<<"Pole zajete!\n";     //Jak nie to do skutku
	      continue;
	    }
	}else
	{
	  if(board[X][Y] == ' ')
	    {
	      board[X][Y] = 'O';
	      ostatni.X = X;
	      ostatni.Y = Y;
	      break;
	    }
	  else
	    {
	      cout<<"Pole zajete!\n";
	      continue;
	    }
	}
    }

  checkWin();                                  //Sprawdz czy player nie wygral, albo remis
  checkDraw();
}



/*******************************/
//Sprawdz czy remis
//
/*******************************/
void Plansza::checkDraw()
{
  bool flag{ false  };
  
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      for(unsigned int jdx = 0; jdx < board.size(); ++jdx)
	{
	  if(board[idx][jdx] == ' ')                 //Gdy wolne miejsce zakoncz sprawdzanie
	    {
	      flag = true;
	      break;
	    }
	}

      if(flag) break;
      if(idx == board.size() - 1)                    //Jezeli przeleci wszystko = remis
	{
	  isOn = false;
	  zwyciezca = 0;
	}
    }

}

/*******************************/
//Check wygrana w odniesieniu do
//ostatniego ulozonego elementu
/*******************************/
void Plansza::checkWin()
{
  //Check poziom 
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      if(turn)
	{
	  if(board[ostatni.X][idx] != 'X') break;        //Jezeli nie bedzie X w poziomie, nie ma win
	  if(idx == board.size() - 1)                    //Jezeli do konca to wygrana w zal od turn
	    {
	      retWinner(true);
	      isOn = false;
	      return;
	    }
	}
      else
	{
	  if(board[ostatni.X][idx] != 'O') break;
	  if(idx == board.size() - 1)
	    {
	      retWinner(false);
	      isOn = false;
	      return;
	    }
	}
    }


  //Check pion  
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      if(turn)
	{
	  if(board[idx][ostatni.Y] != 'X') break;            //Identyczna zasada ja w poziomie
	  if(idx == board.size() - 1)
	    {
	      retWinner(true);
	      isOn = false;
	      return;
	    }
	}
      else
	{
	  if(board[idx][ostatni.Y] != 'O') break;
	  if(idx == board.size() - 1)
	    {
	      retWinner(false);
	      isOn = false;
	      return;
	    }
	}
    }

  //Check przekatna
  if(ostatni.X == ostatni.Y)                     //Jak indexy poprzedniego takie same = lezy na przek
    {      
      for(unsigned int idx = 0; idx < board.size(); ++idx)
	{
	  
	  if(turn)
	    {
	      if(board[idx][idx] != 'X') break;    //Identyczna zasada jak wyzej, lecimy po przekatnej
	      if(idx == board.size() - 1)
		{
		  retWinner(true);
		  isOn = false;
		  return;
		}
	    }
	  else
	    {
	      if(board[idx][idx] != 'O') break;
	      if(idx == board.size() - 1)
		{
		  retWinner(false);
		  isOn = false;
		  return;
		}
	    }

	}
      
    }


  //Check przeciwPrzekatna
  if(ostatni.Y == static_cast<int>(board.size()) - 1 - ostatni.X)
    {
      unsigned int jdx = 0;
      for(int idx = static_cast<int>(board.size()) - 1; idx >= 0; --idx)
	{
	  
	  if(turn)                           //Identyczna zasada jak wyzej, lecimy po antyprzekatnej
	    {
	      if(board[jdx][idx] != 'X') break; 
	      if(idx == 0)
		{
		  retWinner(true);
		  isOn = false;
		  return;
		}
	    }
	  else
	    {
	      if(board[jdx][idx] != 'O') break;
	      if(idx == 0)
		{
		  retWinner(false);
		  isOn = false;
		  return;
		}
	    }
	  
	  ++jdx;

	}
      
    }

  
}


void Plansza::display()               //Wyswietl tablice, z obrobka: |
{
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      for(unsigned int jdx = 0; jdx < board[idx].size(); ++jdx)
	{
	  cout<<"|"<<board[idx][jdx];
	}
      cout<<"|"<<endl;
    }
}
