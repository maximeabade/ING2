#ifndef GUIRLANDE_HPP
#define GUIRLANDE_HPP

#include "Ampoule.hpp"
#include "Electrique.hpp"
#include <vector>

class Guirlande : public Electrique {
private:
    std::vector<Ampoule> ampoules;

public:
    Guirlande(std::vector<Ampoule> ampoules);

    float puissance() const override;

    void afficher() const;

    void allumer();
};

#endif // GUIRLANDE_HPP