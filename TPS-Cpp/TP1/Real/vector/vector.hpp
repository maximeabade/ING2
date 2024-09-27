/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 26/01/2024                                 /////
/////NAME: VECTOR.HPP                                               /////
/////INPUTS: NULL                                                   /////
/////OUTPUTS: NULL                                                  /////
/////BRIEF: definition des methodes de Vector                       /////                                                               
/////                                                               /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#ifndef __VECTOR_HPP_
#define __VECTOR_HPP_
class Vector{
    private : 
        double* elements;
        unsigned int sz;
    public: 
        Vector(unsigned int s);
        unsigned int size() const;
        double& operator[](unsigned int i);
};

#endif