#include "Fraction.hpp"

#include <fstream>

// Constructeurs
Fraction::Fraction() {
    numerateur = 0;
    denominateur = 1;
}

Fraction::Fraction(int n) {
    numerateur = n;
    denominateur = 1;
}

Fraction::Fraction(int n, int d) {
    numerateur = n;
    denominateur = d;
}

// Opérateur de multiplication
Fraction Fraction::operator*(const Fraction& f) const {
    Fraction result;
    result.numerateur = numerateur * f.numerateur;
    result.denominateur = denominateur * f.denominateur;
    return result;
}

// Fonction d'écriture dans un fichier
void Fraction::write(const Fraction& f) const {
    std::ofstream file("fraction.txt");
    if (file.is_open()) {
        file << f;
        file.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier fraction.txt" << std::endl;
    }
}

// Destructeur
Fraction::~Fraction() {}

// Surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& out, const Fraction& f) {
    out << f.numerateur << "/" << f.denominateur;
    return out;
}

// Surcharge de l'opérateur >>
std::istream& operator>>(std::istream& in, Fraction& f) {
    in >> f.numerateur;
    in.ignore(); // Ignore le '/'
    in >> f.denominateur;
    return in;
}
