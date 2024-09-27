#include "Personne.hpp"

class Etudiant : public Personne {
  private:
        int matricule;
        std::string specialite;

    public:
        Etudiant();
        Etudiant(const std::string& nom, const std::string& id, const std::string& genitals, int matricule, const std::string& specialite);

        int getMatricule() const { return matricule; }
        void setMatricule(int matricule) { this->matricule = matricule; }

        const std::string& getSpecialite() const { return specialite; }
        void setSpecialite(const std::string& specialite) { this->specialite = specialite; }

        void afficher() const;
};

// Constructeurs

Etudiant::Etudiant() {}

Etudiant::Etudiant(const std::string& nom, const std::string& id, const std::string& genitals, int matricule, const std::string& specialite) :
    Personne(nom, id, genitals),
    matricule(matricule),
    specialite(specialite)
{}

// Méthode afficher

void Etudiant::afficher() const {
    Personne::afficher(); // Affichage des informations de la classe Personne
    std::cout << "Matricule: " << matricule << std::endl;
    std::cout << "Spécialité: " << specialite << std::endl;
}
