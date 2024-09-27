#include <iostream>
#include <string>

class Personne {
public:
    Personne(const std::string& nom) : nom(nom) {}

    virtual void Afficher() const {
        std::cout << "Nom: " << nom << std::endl;
    }

protected:
    std::string nom;
};