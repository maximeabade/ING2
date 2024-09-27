#ifndef AMPOULE_HPP
#define AMPOULE_HPP

#include "Electrique.hpp"

class Ampoule : public Electrique {
public:
    Ampoule(float intensite = 0);

    float puissance() const override;

    void afficher() const;  // Supprimer le mot-clé override
    float getIntensite() const;
    void setIntensite(float intensite);
};

#endif // AMPOULE_HPP