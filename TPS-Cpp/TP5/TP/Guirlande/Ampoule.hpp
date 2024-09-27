/*
DANS ce fichier on va faire un héritage de Electrique pour creer nos ampoules
Une ampoule est définie par son intensit, qui est soit egale à 0.5 soit à 0.05
Son prix est de 5 euros si son intensité est de 0.5 et de 0.5 euros si son intensité est de 0.05
Sa representation est "O" si son intensité est de 0.5 et "o" si son intensité est de 0.05
*/

#ifndef AMPOULE_HPP
#define AMPOULE_HPP
#include "Electrique.hpp"
#include <iostream>
using namespace std;

class Ampoule : public Electrique {
    public:
        Ampoule(float intensity = 0.5);
        double getPrice() const;
        char getRepresentation() const;
        double price;
        char representation;
};


#endif // AMPOULE_HPP