#include <iostream>
#include "Fraction.hpp"

int main() {

    Fraction fraction;

    // Gestion du dénominateur nul avec try/catch
    try {
        std::cout << "Entrez une fraction au format a/b : ";
        std::cin >> fraction;

        // Vérification du dénominateur
        if (fraction.denominateur == 0) {
            throw std::invalid_argument("Le dénominateur ne peut pas être nul.");
        }

        // Opérations sur la fraction
        std::cout << "La fraction que vous avez entrée est : " << fraction << std::endl;

        // Ecriture dans un fichier
        fraction.write(fraction);

        // Lecture depuis un fichier
        std::string myPath = "fractions.txt";
        std::cout << "La fraction lue depuis le fichier est : " << fraction.read(myPath) << std::endl;

    } catch (std::invalid_argument e) {
        // Affichage d'un message d'erreur
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
