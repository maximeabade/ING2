/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 26/01/2024                                 /////
/////NAME: SUM_SQRT -> double                                       /////
/////INPUTS: VECTOR V                                               /////
/////OUTPUTS: NULL                                                  /////
/////BRIEF: la fonction effectue la norme euclidienne du vecteur    /////                                                               
/////                                                               /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


#include "vector.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace std;


double sum_sqrt(Vector & v) {
    double sum = 0;
    for (unsigned int i; i<v.size(); ++i){
        sum += sqrt(v[i]);
    }
    return sum;
}

int main() {
    const unsigned int vectorSize = 5; 
    Vector myVector(vectorSize);

    double result = sum_sqrt(myVector);

    std::cout << "Norme euclidienne " << result << std::endl;

    return 0;
}