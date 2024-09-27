/**
 * @file Light.cpp
 * @author ABADE Maxime <maximeabade@gmail.com>
 * @brief 
 * @version 0.1
 * @date 2024-02-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Light.hpp"

/**
 * @brief Default constructor for the Light class
 */
Light::Light() : state(false) {}

/**
 * @brief Destructor for the Light class
 */
Light::~Light() {}

/**
 * @brief Turn the light on
 * 
 */
void Light::on() {
    state = true;
}

/**
 * @brief Turn the light off
 * 
 */
void Light::off() {
    state = false;
}

/**
 * @brief Toggles the state of the light
 */
void Light::toggle() {
    state = !state;
}

/**
 * @brief Checks if the light is on
 * @return true if the light is on, false otherwise
 */
bool Light::IsOn() {
    return state;
}

/**
 * @brief Overloaded stream insertion operator for the Light class
 * @param out The output stream
 * @param l The Light object to be inserted into the stream
 * @return The output stream
 */
std::ostream& operator << (std::ostream& out, const Light& l) {
    out << (l.state ? "o" : ".");
    return out;
}