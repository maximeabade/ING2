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
Fraction Fraction::operator * (int n) {
  numerateur *= n;
  return *this;
}


// Non-member operator overload for int * Fraction
Fraction operator*(int n, const Fraction& f) {
    return Fraction(n * f.numerateur, f.denominateur); // Create a new Fraction
}