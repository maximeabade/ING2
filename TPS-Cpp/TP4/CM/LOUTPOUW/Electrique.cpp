#include "Electrique.hpp"
#include <iostream>

using namespace std;

Electrique::Electrique(float tension, float intensite) {
    this->tension = tension;
    this->intensite = intensite;
}

void Electrique::afficher() const {
    cout << "Tension : " << tension << "V" << endl;
    cout << "Intensite : " << intensite << "A" << endl;
}