#include <iostream>
#include "Light.hpp"
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 13/02/2024                                     /////
/////DATE OF LAST MODIF: 14/02/2024                                 /////
/////NAME: MAIN                                                     /////
/////INPUTS: VOID                                                   /////
/////OUTPUTS: EXIT SUCCESS                                          /////
/////BRIEF: fonction main qui fait une  guirlande avec une ligne de /////
///// . et de 0 en fonction de isOn()                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


int main() {
    Light light;


    light.toggle();


    //Tableau de lights pour faire une guirlande : 
    Light guirlande[10];
    for (int i = 0; i < 10; i++) {
        if(i%2==0){guirlande[i].toggle();}
    }
    //afichage de la guirlande
    for (int i = 0; i < 10; i++) {
        //cout << guirlande[i].isOn() << endl;
        //on veut afficher tous les . sur la meme ligne et tous les 0 en dessous
        if(guirlande[i].isOn()){cout << ".";}
        if(i==9){cout << endl;}    
    }
    for (int i = 0; i < 10; i++) {
        if(!guirlande[i].isOn()){cout << "O";}
        if(i==9){cout << endl;}
    }

    return EXIT_SUCCESS;
}