#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <iterator>
#include <random>
#include <string>


int main() {
    // Conteneur séquentiel list
    std::list<int> myList = {0, 3, 1, 4, 2};

    std::cout << "list:\n";
    for (const auto& num : myList) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    myList.sort(); // Trie la liste
    std::cout << "list (sorted):\n";
    for (const auto& num : myList) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    myList.reverse(); // Inverse la liste
    std::cout << "list (reversed):\n";
    for (const auto& num : myList) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Front: " << myList.front() << ", Back: " << myList.back() << std::endl;

    // Conteneur associatif map
    std::map<std::string, std::string> myMap = {
        {"Francois Martin", "02.03.04.05.06"},
        {"Jean Martin", "01.02.03.04.05"},
        {"Louis Dupont", "03.04.05.06.07"},
        {"Louis Martin", "04.05.06.07.08"}
    };

    std::cout << "\nmap:\n";
    for (const auto& pair : myMap) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    // Iterator, auto, Algorithmes
    std::list<int> myList2 = {32, 71, 12, 45, 26, 80, 53, 33};

    std::cout << "\nIterator, auto, Algorithmes:\n";
    for (const auto& num : myList2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Mélange aléatoire de la liste
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(myList2.begin(), myList2.end(), g);

    std::cout << "After random shuffle:\n";
    for (const auto& num : myList2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;


    // Jeu de test pour Foncteur (fonction objet)
    std::list<int> myList3 = {11, 22, 33, 44, 55, 66, 77, 88};
    myList3.sort(); 

    std::cout << "\nFoncteur (Function Object):\n";
    for (const auto& num : myList3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Jeu de test pour lambda-expression & for-each
    std::list<int> myList4 = {1, 2, 3, 4, 5};

    std::cout << "\nLambda-expression & for-each:\n";
    for_each(myList4.begin(), myList4.end(), [](int num) { std::cout << num * 2 << " "; });
    std::cout << std::endl;

    return 0;
}
