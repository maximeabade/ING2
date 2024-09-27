#ifndef __FRACTION_HPP__
#define __FRACTION_HPP__

#include <iostream>

class Fraction {
private:
    int numerateur;
    int denominateur;

public:
    // Constructeurs
    Fraction();
    Fraction(int n);
    Fraction(int n, int d);

    // Opérateur de multiplication
    Fraction operator*(const Fraction& f) const;

    // Fonction d'écriture dans un fichier
    void write(const Fraction& f) const;

    // Destructeur
    ~Fraction();

    // Amis de la classe pour la surcharge des opérateurs
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
    friend std::istream& operator>>(std::istream& in, Fraction& f);
};

#endif
