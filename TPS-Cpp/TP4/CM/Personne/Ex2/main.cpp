#include <iostream>
#include "Personne.hpp"
#include "Etudiant.hpp"

int main() {
  Etudiant Alain("BERTAILS", "Alain");

  Alain.setId("0001");
  Alain.afficher();

  Alain.setId("0002");
  Alain.setNom("TERRIEUR");
  Alain.afficher();

  return EXIT_SUCCESS;
}