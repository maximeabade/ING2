/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 14/02/2024                                 /////
/////NAME: LIGHT.CPP                                                /////
/////INPUTS: diameter(int)                                          /////
/////OUTPUTS: void/int                                              /////
/////BRIEF: On définit les fonctions nécessaires à la création      /////                                                               
/////       et l'utilisation des disks                              /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#ifndef __DISK_HPP__
#define __DISK_HPP__

#include <iostream>

class Disk {
public:
    Disk(int diameter);
    ~Disk() = default;
    int getSize() const;

private:
    int size;
};

#endif