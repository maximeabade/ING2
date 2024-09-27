/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 14/02/2024                                 /////
/////NAME: Fraction.CPP                                             /////
/////INPUTS:int, fractions                                          /////
/////OUTPUTS: fractions, void                                       /////
/////BRIEF: On définit les fonctions nécessaires à la surcharge     /////                                                               
/////       et l'utilisation des opérations sur les fractions       /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Fraction.hpp"

// Constructeur
Fraction::Fraction() : Fraction(0, 1) {}
Fraction::Fraction(int n) : numerateur(n), denominateur(1) {}

Fraction::Fraction(int n, int d) {
  if (d == 0) {
    std::cerr << "Erreur : dénominateur nul !" << std::endl;
    exit(1);
  }
  denominateur = d;
  numerateur = n;
}

// Destructeur
Fraction::~Fraction() {}

// C'est une fonction AMIE, pas une méthode membre
std::ostream& operator<<(std::ostream& out, const Fraction& f) {
  out << "Fraction : " << f.numerateur << "/" << f.denominateur << std::endl;
  return out;
}
Fraction Fraction::operator * (const Fraction& f) {
  numerateur *= f.numerateur;
  denominateur *= f.denominateur;
  return *this;
}
