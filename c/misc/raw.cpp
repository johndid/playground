#include <iostream>
#include <string>

int main(int,char**)
{
  int input;
  cout << "Enter a number" << endl;
  cin >> input;

  input = (input < 0) ? input : input*(-1);

  if(input <= 80)
  {
    for(int i=0;i<input;i++)
    {
      cout << string(i+1,'*').c_str() << endl;
    } 
  }
  else
  {
    cout << "No starts for you!" << endl;
  } 


  cout << "Triangular number: " << ((input*(input+1))/2) << endl; 

  return 0;
}