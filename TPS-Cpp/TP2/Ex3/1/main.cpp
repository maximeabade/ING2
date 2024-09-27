#include <iostream>
#include "Fraction.hpp"

int main(){
    std::cout << "How many Fractions to create?" << std::endl;
    int n;
    std::cin >> n;

    //tableau dynamique des fonctions
    Fraction * tf = new Fraction[n];
    // n constructeurs par defaut son appeles
    for (int i = 0; i < n; i++){
        std::cout << "Enter the numerator and the denominator of the fraction " << i << std::endl;
        int num, den;
        std::cin >> num >> den;
        tf[i] = Fraction(num, den);
    }
    //afficahge des fractions
    for (int i = 0; i < n; i++){
        std::cout << tf[i] << std::endl;
    }

    delete[] tf;

    return EXIT_SUCCESS;
}