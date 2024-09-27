/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 14/02/2024                                 /////
/////NAME: DISK.CPP                                                 /////
/////INPUTS: diameter(int)                                          /////
/////OUTPUTS: VOID / INT                                            /////
/////BRIEF:Functions on disks to make it work properly              /////                                                               
/////                                                               /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#include "Disk.hpp"

Disk::Disk(int diameter) : size(diameter) {}

int Disk::getSize() const {
    return size;
}