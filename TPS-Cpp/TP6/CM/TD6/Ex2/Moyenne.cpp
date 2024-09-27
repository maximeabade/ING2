#include <iostream>
#include <string>

// Déclaration de la classe Moyenne (non utilisée dans cet exemple)
class Moyenne {
    public:
        // Déclarations de membres ou de méthodes si nécessaire
};

// Fonction template pour calculer la moyenne
template<typename T1, typename T2>
T2 calculerMoyenne(T1 tableau[], int taille) {
    T2 somme = 0;
    for (int i = 0; i < taille; i++) {
        somme += tableau[i];
    }
    return somme / taille;
}

int main() {
    int tableau[] = {1, 2, 3, 4, 5};
    // Appel correct de la fonction calculerMoyenne avec les types de données appropriés
    double moyenne = calculerMoyenne<int, double>(tableau, 5);
    std::cout << "Moyenne: " << moyenne << std::endl;
    return 0;
}
