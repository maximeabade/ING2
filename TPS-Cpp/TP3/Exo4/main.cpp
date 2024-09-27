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
  f=2*f1;
  cout << f;

  return EXIT_SUCCESS;
}
