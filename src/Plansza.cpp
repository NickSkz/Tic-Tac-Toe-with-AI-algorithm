#include "Plansza.hh"

using namespace std;

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

  zwyciezca = -99;
  isOn = true;
  turn = true;
}


void Plansza::makeRuch()
{
  while(true)
    {
      int X, Y;
      turn ? cout<<"Ruch: X\n" : cout<<"Ruch: Y\n"; 
      cin>>X;
      cin>>Y;

      if(turn)
	{
	  if(board[X][Y] == ' ')
	    {
	      board[X][Y] = 'X';
	      break;
	    }
	  else
	    {
	      cout<<"Pole zajete!\n";
	      continue;
	    }
	}else
	{
	  if(board[X][Y] == ' ')
	    {
	      board[X][Y] = 'O';	     
	      break;
	    }
	  else
	    {
	      cout<<"Pole zajete!\n";
	      continue;
	    }
	}
    }

  checkWin();
  checkDraw();
}


void Plansza::checkDraw()
{
  bool flag{ false  };
  
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      for(unsigned int jdx = 0; jdx < board.size(); ++jdx)
	{
	  if(board[idx][jdx] == ' ')
	    {
	      flag = true;
	      break;
	    }
	}

      if(flag) break;
      if(idx == board.size() - 1)
	{
	  isOn = false;
	  zwyciezca = 0;
	}
    }

}


void Plansza::checkWin()
{
  bool flag{ false };
  //Sprawdz poziome wygranie
  
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      unsigned int licznik{0};
      for(unsigned int jdx = 0; jdx < board.size(); ++jdx)
	{
	  if(turn)              
	    {
	      if(board[idx][jdx] == 'X')
		{
		  ++licznik;
		}
	      else
		{
		  flag = true;
		  break;
		}
	    }
	  
	  else
	    {
	      if(board[idx][jdx] == 'O')
		{
		  ++licznik;
		}
	      else
		{
		  flag = true;
		  break;
		}
	    }

	  if(licznik == board.size())
	    {
	      if(turn) retWinner(true);
	      else retWinner(false);
	      isOn = false;
	      return;
	    }
	}

      if(flag and idx < board.size() - 1) continue;
    }



  //Sprawdzanie w pionie  
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      unsigned int licznik{0};
      for(unsigned int jdx = 0; jdx < board.size(); ++jdx)
	{
	  if(turn)
	    {
	      if(board[jdx][idx] == 'X')
		{
		  ++licznik;
		}
	      else
		{
		  flag = true;
		  break;
		}
	    }
	  
	  else
	    {
	      if(board[jdx][idx] == 'O')
		{
		  ++licznik;
		}
	      else
		{
		  flag = true;
		  break;
		}
	    }

	  if(licznik == board.size())
	    {
	      if(turn) retWinner(true);
	      else retWinner(false);
	      isOn = false;
	      return;
	    }
	}

      if(flag and idx < board.size() - 1) continue;
    }

  

  //Sprawdzenie na przek

  unsigned int licznik{ 0 };
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      if(turn)
	{
	  if(board[idx][idx] == 'X') ++licznik;
	  else break;	      
	}
	  
      else
	{
	  if(board[idx][idx] == 'O') ++licznik;	    	
	  else break;	    
	}

      if(licznik == board.size())
	{
	  if(turn) retWinner(true);
	  else retWinner(false);
	  isOn = false;
	  return;
	}
    }
  
 


  //Sprawdzenie na przeciw-przek
  
  int idx{ 0 };
  licznik = 0;
  for(unsigned int jdx = board.size() - 1; jdx >= 0; --jdx)
    {
      if(turn)
	{
	  if(board[idx][jdx] == 'X') ++licznik;
	  else break;	      
	}
	  
      else
	{
	  if(board[idx][jdx] == 'O') ++licznik;	    	
	  else break;	    
	}

      if(licznik == board.size())
	{
	  if(turn) retWinner(true);
	  else retWinner(false);
	  isOn = false;
	  return;
	}

      ++idx;
    }
  }


void Plansza::display()
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
