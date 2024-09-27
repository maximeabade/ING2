using namespace std;

#include <iostream>
#include "Guirlande.hpp"

int main(){
    // Create a guirlande with the specified number of lights
    Guirlande MaGuirlande1(1);
    Guirlande MaGuirlande2(1);

    // Toggle the guirlande
    MaGuirlande2.toggle();

    // Create a guirlande wich is the sum of the two previous ones
    Guirlande MaGuirlande = MaGuirlande1 + MaGuirlande2;
    cout << MaGuirlande << endl;

    // Toggle the guirlande
    MaGuirlande.toggle();
    cout << MaGuirlande << endl;

    // Multiply the guirlande by 5
    MaGuirlande*=5;
    cout << MaGuirlande << endl;

    // Toggle the guirlande
    MaGuirlande.toggle();
    cout << MaGuirlande << endl;

    // MaGuirlande1 is the division of MaGuirlande by 3
    MaGuirlande1=MaGuirlande/3;

    // Turn the guirlande off
    MaGuirlande1.off();
    cout << MaGuirlande1 << endl;

    // Turn the guirlande on
    MaGuirlande1.on();
    cout << MaGuirlande1 << endl;

    // MaGuirlande is the multiplication of MaGuirlande1 by 5
    MaGuirlande=5*MaGuirlande1;
    cout << MaGuirlande << endl;

    // MaGuirlande2 is the subtraction of MaGuirlande1 by MaGuirlande
    MaGuirlande2=MaGuirlande1-MaGuirlande;
    cout << MaGuirlande2 << endl;   

    return EXIT_SUCCESS;
}