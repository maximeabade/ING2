#include "Ampoule.hpp"
#include <iostream>

using namespace std;

Ampoule::Ampoule(float intensite) : Electrique(220, intensite) {}

float Ampoule::puissance() const {
    return tension * intensite;
}

void Ampoule::afficher() const {
    if (intensite == 0) {
        cout << ".";
    } else if (intensite <= 0.05) {
        cout << "o";
    } else {
        cout << "O";
    }
}

float Ampoule::getIntensite() const {
    return intensite;
}

void Ampoule::setIntensite(float intensite) {
    this->intensite = intensite;
}