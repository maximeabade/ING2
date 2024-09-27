#include <iostream>
#include "Fraction.hpp"

int main() {
    Fraction fraction;

    std::cout << "Entrez une fraction au format a/b : ";
    std::cin >> fraction;

    std::cout << "La fraction que vous avez entrée est : " << fraction << std::endl;

    return 0;
}