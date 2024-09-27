/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 14/02/2024                                 /////
/////NAME: MAIN.CPP                                                 /////
/////INPUTS:int, fractions                                          /////
/////OUTPUTS: exit_success                                          /////
/////BRIEF: utilisation des surcharges des opérateurs sur les       /////                                                               
/////        fractions                                              /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
using namespace std;

#include <iostream>
#include "Fraction.hpp"

int main()
{
  Fraction f1(4,5);
  Fraction f2(3,11);
  Fraction f=f1*f2;
  cout << f;
  f=f1*f2*f;
  cout << f;
  f=f1*2;
  cout << f;

  return EXIT_SUCCESS;
}
