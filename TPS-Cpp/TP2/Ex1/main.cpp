#include <iostream>
#include "Fraction.hpp"

int main() {

  Fraction f1;
  Fraction f2(10);
  Fraction f3(3, 7);
  Fraction f(5, 6);
  //creer espace memoire pour un objet
    Fraction *f4 = new Fraction(1, 2);

  //affecter 5 au numerateur et 6 au denominateur
    f1.~Fraction();
    f1 = Fraction(5, 6);

std::cout << f << std::endl; //use of friend function

  return EXIT_SUCCESS;
}