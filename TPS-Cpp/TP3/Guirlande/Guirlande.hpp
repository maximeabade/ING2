/**
 * @file Guirlande.hpp
 * @brief Header file for the Guirlande class.
 * 
 * This file contains the declaration of the Guirlande class, which represents a string of lights.
 * It includes the necessary headers and defines the class members and methods.
 * 
 * @author ABADE Maxime <maximeabade@gmail.com>
 * @version 0.1
 * @date 2024-02-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <vector>
#include "Light.hpp"

/**
 * @brief The Guirlande class represents a string of lights.
 * 
 * This class manages a string of lights and provides methods to toggle the lights and output the state of the guirlande.
 */
class Guirlande {
public:
    /**
     * @brief Constructs a new Guirlande object with the specified number of lights.
     * 
     * @param numberOfLights The number of lights in the guirlande.
     */
    Guirlande(int numberOfLights);

    /**
     * @brief Copy constructor.
     * 
     * @param other The Guirlande object to be copied.
     */
    Guirlande(const Guirlande& other);

    /**
     * @brief Destructor.
     */
    ~Guirlande();

    /**
     * @brief Returns the number of lights in the guirlande.
     * 
     * @return int The number of lights in the guirlande.
     */
    int getNumberOfLights() const;

    /**
     * @brief Returns the array of lights in the guirlande.
     * 
     * @return Light* The array of lights in the guirlande.
     */
    Light* getLights() const;

    /**
     * @brief Assignment operator.
     * 
     * @param other The Guirlande object to be assigned.
     * @return Guirlande& A reference to the assigned Guirlande object.
     */
    Guirlande& operator=(const Guirlande& other);

    /**
     * @brief Multiplication operator for the Guirlande class.
     * 
     * @param n 
     * @return Guirlande& 
     */
    Guirlande& operator*=(int n);

    /**
     * @brief Turns on the guirlande but keep the same order of the lights as before.
     */
    void on();

    /**
     * @brief Turns off all the lights in the guirlande.
     */
    void off();

    /**
     * @brief Toggles the state of all the lights in the guirlande.
     */
    void toggle();

    /**
     * @brief Overloaded stream insertion operator.
     * 
     * @param out The output stream.
     * @param guirlande The Guirlande object to be output.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& out, const Guirlande& guirlande);

private:
    std::vector<bool> stateBeforeOff;
    bool stateBeforeOffSet;
    Light* lights; 
    int numberOfLights;
};

/**
 * @brief Sum operator for the Guirlande class.
 * 
 * @param g1 Guirlande
 * @param g2 Guirlande
 * @return Guirlande 
 */
Guirlande operator+(const Guirlande& g1, const Guirlande& g2);

/**
 * @brief Division operator for the Guirlande class.
 * 
 * @param g1 Guirlande
 * @param n Integer
 * @return Guirlande 
 */
Guirlande operator/(const Guirlande& g1, int n);

/**
 * @brief Multiplication operator for the Guirlande class.
 * 
 * @param g1 Guirlande
 * @param n Integer
 * @return Guirlande 
 */
Guirlande operator*(int n, const Guirlande& g1);

/**
 * @brief Subtraction operator for the Guirlande class.
 * 
 * @param g1 Guirlande
 * @param g2 Guirlande
 * @return Guirlande 
 */
Guirlande operator-(const Guirlande& g1, const Guirlande& g2);
