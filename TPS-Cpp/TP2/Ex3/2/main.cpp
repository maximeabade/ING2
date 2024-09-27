using namespace std;

#include <iostream>
#include "Fraction.hpp"

int main(){
    std::cout << "How many Fractions to create?" << std::endl;
    int n;
    std::cin >> n;

    // Tableau de pointeurs de fractions
    Fraction ** ppf  = new Fraction*[n];
    //Initialise le tableau de pointeurs de fractions
    for (int i = 0; i < n; i++){
        std::cout << "Enter the numerator and the denominator of the fraction " << i << std::endl;
        int num, den;
        std::cin >> num >> den;
        ppf[i] = new Fraction(num, den);
    }

    //Fonction amie pour l affichage
    for (int i = 0; i < n; i++){
        std::cout << *ppf[i] << std::endl;
    }

    //liberation de chaque pointeur
    for (int i = 0; i < n; i++){
        delete ppf[i];
    }

    //liberation du tableau
    delete[] ppf;

    return EXIT_SUCCESS;
}