#ifndef ELECTRIQUE_HPP
#define ELECTRIQUE_HPP

#include <iostream>
using namespace std;

class Electrique {
    public:
        float intensity;
        float getIntensity() const;
        void setIntensity(float intensity);
};


#endif // ELECTRIQUE_HPP