#include <iostream>

#include "Plansza.hh"
#include "SI.hh"

using namespace std;

int main()
{
  int size;
  cout<<"Podaj rozmiar planszy: ";
  cin>>size;
  cout<<endl;
  
  Plansza test(size,size);

  while(test.isOn)
    {
      test.display();
      
      if(test.turn)
	{
	  test.makeRuch();
	  test.turn = !test.turn;
	}
      else
	{
	  cout<<"\nAI turn\n\n";
	  SI::zrobTo(test);
	}
    }
}
