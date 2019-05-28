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
	      ostatni.X = X;
	      ostatni.Y = Y;
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
  //Check poziom
  
  for(unsigned int idx = 0; idx < board.size(); ++idx)
    {
      if(turn)
	{
	  if(board[ostatni.X][idx] != 'X') break;
	  if(idx == board.size() - 1)
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
	  if(board[idx][ostatni.Y] != 'X') break;
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

  if(ostatni.X == ostatni.Y)
    {
      
      for(unsigned int idx = 0; idx < board.size(); ++idx)
	{
	  
	  if(turn)
	    {
	      if(board[idx][idx] != 'X') break;
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
      for(unsigned int idx = board.size() - 1; idx >= 0; --idx)
	{
	  
	  if(turn)
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
