#include <iostream>
#include <vector>
#include "Guirlande.hpp"
#include "Ampoule.hpp"
#include "Electrique.hpp"

using namespace std;

int main() {

  // Déclaration du chemin du fichier
  string path = "./guirlandes.txt";

  // Lecture des guirlandes depuis le fichier
  vector<Guirlande> guirlandes = Guirlande::read(path);

  // Parcours des guirlandes
  for (Guirlande guirlande : guirlandes) {

    // Calcul du prix total avant marge
    guirlande.setPriceTotalBeforeMargin(guirlande.getPriceAmpoules() + guirlande.getPriceCable());

    // Calcul du prix total après marge
    guirlande.setPriceTotalAfterMargin(guirlande.getPriceTotalBeforeMargin() * 1.1);

    // Affichage des informations de la guirlande
    cout << "Guirlande : " << guirlande.getRepresentation() << endl;
    cout << "  - Longueur : " << guirlande.getLength() << endl;
    cout << "  - Prix ampoules : " << guirlande.getPriceAmpoules() << endl;
    cout << "  - Prix câble : " << guirlande.getPriceCable() << endl;
    cout << "  - Prix total avant marge : " << guirlande.getPriceTotalBeforeMargin() << endl;
    cout << "  - Prix total après marge : " << guirlande.getPriceTotalAfterMargin() << endl;
    cout << endl;

    // Ecriture de la guirlande et de son prix dans un fichier
    Guirlande::write("./guirlandes_data.txt", guirlande);
  }

  return 0;
}
