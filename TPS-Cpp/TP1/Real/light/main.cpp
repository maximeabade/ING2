#include <iostream>
#include "Light.hpp"

int main() {
    Light light;

    cout << "La lumière est-elle allumée ? " << light.isOn() << endl;

    light.toggle();

    cout << "La lumière est-elle allumée ? " << light.isOn() << endl;

    //Tableau de lights pour faire une guirlande : 
    Light guirlande[10];
    for (int i = 0; i < 10; i++) {
        if(i%2==0){guirlande[i].toggle();}
    }
    //afichage de la guirlande
    for (int i = 0; i < 10; i++) {
        cout << guirlande[i].isOn() << endl;
    }
    return 0;
}