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
    Fraction operator * (int n);
    //friend to overload the operator * for the case of int * Fraction
    friend Fraction operator * (int n, const Fraction& f);
    // Destructeur
    ~Fraction();
    // C’est une fonction AMIE, pas une methode membre
    friend std::ostream&operator << (std::ostream&out,const Fraction &f);
};

#endif