#include <iostream>
#include "Fraction.hpp"

int main() {
    Fraction fraction;

    std::cout << "Entrez une fraction au format a/b : ";
    std::cin >> fraction;

    std::cout << "La fraction que vous avez entrée est : " << fraction << std::endl;
    
    //ecriture
    fraction.write(fraction);

    string myPath = "fractions.txt";
    //lecture
    std::cout << "La fraction que vous avez entrée dans le fichier est : " << fraction.read(myPath) << std::endl;
    return 0;
}