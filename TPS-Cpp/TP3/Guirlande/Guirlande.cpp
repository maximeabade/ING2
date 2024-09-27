/**
 * @file Guirlande.cpp
 * @author ABADE Maxime <maximeabade@gmail.com>
 * @brief 
 * @version 0.1
 * @date 2024-02-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Guirlande.hpp"

/**
 * @brief Construct a new Guirlande:: Guirlande object
 * 
 * @param numberOfLights 
 */
Guirlande::Guirlande(int numberOfLights) : numberOfLights(numberOfLights) {
    lights = new Light[numberOfLights];
    stateBeforeOff = std::vector<bool>(numberOfLights);
}

/**
 * @brief Construct a new Guirlande:: Guirlande object
 * 
 * @param other 
 */
Guirlande::Guirlande(const Guirlande& other) : numberOfLights(other.numberOfLights), stateBeforeOffSet(false) {
    lights = new Light[numberOfLights];
    for (int i = 0; i < numberOfLights; ++i) {
        lights[i] = other.lights[i];
    }
}

/**
 * @brief Destroy the Guirlande:: Guirlande object
 * 
 */
Guirlande::~Guirlande() {
    delete[] lights;
}

/**
 * @brief Get the Lights object
 * 
 * @return Light* 
 */
int Guirlande::getNumberOfLights() const {
    return numberOfLights;
}

/**
 * @brief Get the Lights object
 * 
 * @return Light* 
 */
Light* Guirlande::getLights() const {
    return lights;
}

/**
 * @brief Assignment operator for the Guirlande class
 * 
 * @param other 
 * @return Guirlande& 
 */
Guirlande& Guirlande::operator=(const Guirlande& other) {
    if (this != &other) {
        delete[] lights;
        numberOfLights = other.numberOfLights;
        lights = new Light[numberOfLights];
        for (int i = 0; i < numberOfLights; ++i) {
            lights[i] = other.lights[i];
        }
    }
    return *this;
}

/**
 * @brief Multiplication operator for the Guirlande class
 * 
 * @param n 
 * @return Guirlande& 
 */
Guirlande& Guirlande::operator*=(int n) {
    Guirlande result(numberOfLights * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < numberOfLights; ++j) {
            result.lights[i*numberOfLights+j] = lights[j];
        }
    }
    *this = result;
    return *this;
}

/**
 * @brief Turns on the guirlande but keep the same order of the lights as before.
 * 
 */
void Guirlande::on() {
    if (stateBeforeOffSet)
    {
        for (int i = 0; i < numberOfLights; ++i) {
            if (stateBeforeOff[i]) {
                lights[i].on();
            }
        }
    } else {
        for (int i = 0; i < numberOfLights; ++i) {
            if (i%2 == 0){
                lights[i].on();
            }
        }
    }
    
}

/**
 * @brief Turns off all the lights in the guirlande.
 * 
 */
void Guirlande::off(){
    stateBeforeOff.clear();
    for (int i = 0; i < numberOfLights; ++i)
    {
        stateBeforeOff.push_back(lights[i].IsOn());
        lights[i].off();
    }
    stateBeforeOffSet = true;
}

/**
 * @brief Toggles the state of all the lights in the guirlande
 * 
 */
void Guirlande::toggle() {
    for (int i = 0; i < numberOfLights; ++i) {
        lights[i].toggle();
    }
}

/**
 * @brief Overloaded stream insertion operator for the Guirlande class
 * 
 * @param out 
 * @param guirlande
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& out, const Guirlande& guirlande) {
    for (int i = 0; i < guirlande.numberOfLights; ++i) {
        out << guirlande.lights[i];
    }
    out << '\n';
    return out;
}

/**
 * @brief Sum operator for the Guirlande class
 * 
 * @param g1 Guirlande
 * @param g2 Guirlande
 * @return Guirlande 
 */
Guirlande operator+(const Guirlande& g1, const Guirlande& g2) {
    Guirlande result(g1.getNumberOfLights() + g2.getNumberOfLights());
    for (int i = 0; i < g1.getNumberOfLights(); ++i) {
        result.getLights()[i] = g1.getLights()[i];
    }
    for (int i = 0; i < g2.getNumberOfLights(); ++i) {
        result.getLights()[i+g1.getNumberOfLights()] = g2.getLights()[i];
    }
    return result;
}

/**
 * @brief Division operator for the Guirlande class
 * 
 * @param g1 Guirlande
 * @param n Integer
 * @return Guirlande 
 */
Guirlande operator/(const Guirlande& g1, int n) {
    Guirlande result(g1.getNumberOfLights() / n);
    for (int i = 0; i < result.getNumberOfLights(); ++i) {
        result.getLights()[i] = g1.getLights()[i];
    }
    return result;
}

/**
 * @brief Multiplication operator for the Guirlande class
 * 
 * @param g1 Guirlande
 * @param n Integer
 * @return Guirlande 
 */
Guirlande operator*(int n, const Guirlande& g1) { 
    Guirlande result(0);
    for (int i = 0; i < n; i++)
    {
        result = result + g1;
    }
    return result;
}

/**
 * @brief Subtraction operator for the Guirlande class
 * 
 * @param g1 Guirlande
 * @param g2 Guirlande
 * @return Guirlande 
 */
Guirlande operator-(const Guirlande& g1, const Guirlande& g2) {
    if (g1.getNumberOfLights() > g2.getNumberOfLights()) {
        Guirlande result(g1.getNumberOfLights()-g2.getNumberOfLights());
        for (int i = 0; i < result.getNumberOfLights(); ++i) {
            result.getLights()[i] = g1.getLights()[i];
        }
        return result;
    } else {
        Guirlande result(g2.getNumberOfLights()-g1.getNumberOfLights());
        for (int i = 0; i < result.getNumberOfLights(); ++i) {
            result.getLights()[i] = g2.getLights()[i];
        }
        return result;
    }
}