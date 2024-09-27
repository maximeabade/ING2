#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Personne {
  private:
    std::string nom;
    std::string id;
    std::string genitals;

  public:
    Personne();
    Personne(const std::string& nom, const std::string& id, const std::string& genitals);

    const std::string& getNom() const { return nom; }
    void setNom(const std::string& nom) { this->nom = nom; }

    const std::string& getId() const { return id; }
    void setId(const std::string& id) { this->id = id; }

    const std::string& getGenitals() const { return genitals; }
    void setGenitals(const std::string& genitals) { this->genitals = genitals; }

    void afficher() const;


};

// Constructeurs

Personne::Personne() {}

Personne::Personne(const std::string& nom, const std::string& id, const std::string& genitals) {
  this->nom = nom;
  this->id = id;
  this->genitals = genitals;
}

// Méthode afficher

void Personne::afficher() const {
  std::cout << "Nom: " << nom << std::endl;
  std::cout << "Id: " << id << std::endl;
  std::cout << "Genitals: " << genitals << std::endl;
}