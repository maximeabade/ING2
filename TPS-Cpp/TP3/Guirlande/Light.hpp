#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <iostream> // Include the missing header file

class Light
{
    private:
        bool state;        // Indique si la lumière est allumée (true) ou éteinte (false).
    protected:
    public:
        Light ();      // Constructeur par défaut qui crée une lumière éteinte
        ~Light();      // Destructeur

        /**
         * @brief Turn the light on
         * 
         */
        void on();

        /**
         * @brief Turn the light off
         * 
         */
        void off();

        void toggle(); // Si la lumière est allumée, elle sera éteinte et vice versa.
        bool IsOn();   // Retourne true si la lumière est allumée, false sinon

        // Declare the friend function properly
        friend std::ostream& operator << (std::ostream& out, const Light& l);
};

#endif
