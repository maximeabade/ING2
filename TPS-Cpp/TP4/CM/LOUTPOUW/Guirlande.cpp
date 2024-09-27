#include "Guirlande.hpp"
#include <iostream>

using namespace std;

Guirlande::Guirlande(vector<Ampoule> ampoules) : Electrique(220, 0) {
    this->ampoules = ampoules;
    for (const Ampoule &ampoule : ampoules) {
        intensite += ampoule.getIntensite();
    }
}

float Guirlande::puissance() const {
    float puissanceTotale = 0;
    for (const Ampoule &ampoule : ampoules) {
        puissanceTotale += ampoule.puissance();
    }
    return puissanceTotale;
}

void Guirlande::afficher() const {
    Electrique::afficher();
    for (const Ampoule &ampoule : ampoules) {
        ampoule.afficher();
    }
    printf("\n");
}

void Guirlande::allumer() {
    for (Ampoule &ampoule : ampoules) {
        ampoule.setIntensite(0.1);
    }
}