#include "Ampoule.hpp"


//Constructeur ==> required : intensité
Ampoule::Ampoule(float intensity) {
    setIntensity(intensity);
    if (intensity == 0.5) {
        price = 5;
        representation = 'O';
    } else {
        price = 0.5;
        representation = 'o';
    }
}

//Getter pour le prix
double Ampoule::getPrice() const {
    return price;
}

//Getter pour la representation
char Ampoule::getRepresentation() const {
    return representation;
}
