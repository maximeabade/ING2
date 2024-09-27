#include "Fraction.hpp"

// Default constructor
Fraction::Fraction()
{
    numerateur = 0;
    denominateur = 1;
}

// Constructor with numerator only
Fraction::Fraction(int n)
{
    numerateur = n;
    denominateur = 1;
}

// Constructor with numerator and denominator
Fraction::Fraction(int n, int d)
{
    numerateur = n;
    denominateur = d;
}

// Overloaded multiplication operator
Fraction Fraction::operator*(const Fraction& f)
{
    Fraction result;
    result.numerateur = numerateur * f.numerateur;
    result.denominateur = denominateur * f.denominateur;
    return result;
}

// Destructor
Fraction::~Fraction()
{
    // Destructor code here (if needed)
}

// Overloaded output stream operator
std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
    out << f.numerateur << "/" << f.denominateur;
    return out;
}

// Overloaded input stream operator
std::istream& operator>>(std::istream& in, Fraction& f)
{
    in >> f.numerateur;
    in.ignore(); // Ignore the '/' character
    in >> f.denominateur;
    return in;
}