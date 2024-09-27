#include <iostream>
#include "Fraction.hpp"

int main() {
  Fraction * pf;
  //espace memoire pour le pointeur
  pf = new Fraction(7, 5);

  // alloc case memoire pour un objet
  malloc(sizeof(Fraction));

  //affecter 7 au numerateur, 5 au denominateur
  *pf = Fraction(7, 5);
  std::cout << *pf << std::endl; // utilise de la fonction amie
  delete pf;
  //detruite la fraction pointee par pf
  return EXIT_SUCCESS;
}