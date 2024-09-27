/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 26/01/2024                                 /////
/////NAME: LIGHT.HPP                                                /////
/////INPUTS: NULL                                                   /////
/////OUTPUTS: NULL                                                  /////
/////BRIEF: On définit les fonctions nécessaires à la création      /////                                                               
/////       et l'utilisation des lights                             /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////#ifndef __LIGHT_HPP_
#ifndef __LIGHT_HPP_
#define __LIGHT_HPP_

#include <iostream>
using namespace std;

class Light {
public:
    bool status;
    bool isOn() const { return status; }
    void toggle() { status = !status; }
    Light();
private:
    //no private things to have
};
#endif