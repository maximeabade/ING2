#include "Ampoule.hpp"
#include "Electrique.hpp"
#include "Guirlande.hpp"
#include <iostream>

using namespace std;

int main() {
    // Création des ampoules
    Ampoule a1(0.05);
    Ampoule a2(0.01);

    // Création d'une guirlande
    vector<Ampoule> ampoules = {a1, a2};
    Guirlande guirlande(ampoules);

    // Affichage initial
    guirlande.afficher();

    // Allumage de toutes les ampoules
    guirlande.allumer();

    // Affichage après allumage
    guirlande.afficher();

    // Calcul et affichage de la puissance consommée par chaque guirlande
    cout << "Puissance consommée par la guirlande : " << guirlande.puissance() << "W" << endl;

    return 0;
}