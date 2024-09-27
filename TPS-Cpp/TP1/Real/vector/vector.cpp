/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 26/01/2024                                 /////
/////NAME: VECTOR.CPP                                               /////
/////INPUTS: int s, int i                                           /////
/////OUTPUTS: CREATION OF A VECTOR                                  /////
/////BRIEF: On définit les fonctions nécessaires à la création      /////                                                               
/////       et l'utilisation de vecteurs                            /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#include "vector.hpp"
#include <math.h>
#include <time.h>
#include <cstdlib>

Vector::Vector(unsigned int s){
    sz = s;
    elements = new double[s];
    srand(time(NULL));
    for (unsigned int j=0; j<s; ++j){
        elements[j] = rand() % 100;
    }

}

unsigned int Vector::size() const {
    return sz;
}

double& Vector::operator[](unsigned int i){
    if (i<sz){
        return elements[i];
    }
    else{
        return elements[0];
    }
    // (i<sz) ? (return elements[i]) : (return elements[0]);
}