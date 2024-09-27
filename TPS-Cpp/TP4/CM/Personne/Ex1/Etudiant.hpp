#include "Personne.hpp"

class Etudiant : public Personne {
public:
    Etudiant(const std::string& nom, int matricule) : Personne(nom), matricule(matricule) {}

    void Afficher() const override {
        Personne::Afficher();
        std::cout << "Matricule: " << matricule << std::endl;
    }

private:
    int matricule;
};