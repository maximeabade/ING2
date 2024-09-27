/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 14/02/2024                                 /////
/////NAME: Fraction.HPP                                             /////
/////INPUTS:int, fractions                                          /////
/////OUTPUTS: fractions, void                                       /////
/////BRIEF: On définit les fonctions nécessaires à la surcharge     /////                                                               
/////       et l'utilisation des opérations sur les fractions       /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#ifndef __FRACTION_HPP__
#define __FRACTION_HPP__

class Fraction
{
  private:
    int numerateur;
    int denominateur;
  
  protected:

  public:
    // Constructeur
    Fraction ();
    Fraction (int n);
    Fraction (int n,int d);
    Fraction operator * (const Fraction& f);
    // Destructeur
    ~Fraction();
    // C’est une fonction AMIE, pas une methode membre
    friend std::ostream&operator << (std::ostream&out,const Fraction &f);
};

#endif