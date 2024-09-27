#include <iostream>
#include "Fraction.hpp"

//Constructeur par défaut
Fraction::Fraction() : Fraction(0,1)
{
}

//Constructeur par parametre
Fraction::Fraction (int n):numerateur{n}, denominateur{1}
{
}

//Constructeur par parametres
Fraction::Fraction(int n, int d): numerateur{n}, denominateur{d}
{
}

//Destructeur
Fraction::~Fraction()
{
}