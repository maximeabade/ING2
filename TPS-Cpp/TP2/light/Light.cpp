/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 14/02/2024                                 /////
/////NAME: LIGHT.CPP                                                /////
/////INPUTS: EXIT_SUCCESS                                           /////
/////OUTPUTS: CREATION OF LIGHTS                                    /////
/////BRIEF: On définit les fonctions nécessaires à la création      /////                                                               
/////       et l'utilisation des LIGHTS                             /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
using namespace std;
#include "Light.hpp"


#include <iostream>


//creeons une lampe par defaut
Light::Light() {
    status = false;
}
