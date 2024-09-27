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

//NEXT STEP: REDEFINITION DES METHODES + - ET / POUR FRACTION
/*
+ : de fraction a fraction, faire un return de fraction( fraction1.num * fraction2.den + fraction2.num * fraction1.den , fraction1.den * fraction2.den )
    de fraction a entier, faire un return de fraction( fraction.num + entier * fraction.den , fraction.den )
    de entier a fraction, faire un return de fraction( entier * fraction.den + fraction.num , fraction.den )

- : de fraction a fraction, faire un return de fraction( fraction1.num * fraction2.den - fraction2.num * fraction1.den , fraction1.den * fraction2.den )
    de fraction a entier, faire un return de fraction( fraction.num - entier * fraction.den , fraction.den )
    de entier a fraction, faire un return de fraction( entier * fraction.den - fraction.num , fraction.den )

/ : de fraction a fraction, faire un return de fraction( fraction1.num * fraction2.den , fraction1.den * fraction2.num )
    de fraction a entier, faire un return de fraction( fraction.num , fraction.den * entier )
    de entier a fraction, faire un return de fraction( entier * fraction.den , fraction.num )
*/