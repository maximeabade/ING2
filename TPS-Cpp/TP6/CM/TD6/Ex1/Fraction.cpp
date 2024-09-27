#include <iostream>
#include <string>

// Forward declaration of Fraction class
class Fraction;

// Function template for operator< overload
template<typename T>
bool operator<(const T& a, const T& b) {
    return a.numerateur * b.denominateur < b.numerateur * a.denominateur;
}

// Fraction class declaration
class Fraction {
    public:
    int numerateur;
    int denominateur;


    // Default constructor
    Fraction() : Fraction(0, 1) {}

    // Constructor with one parameter
    Fraction(int n) : numerateur(n), denominateur(1) {}

    // Constructor with two parameters
    Fraction(int n, int d) : numerateur(n), denominateur(d) {}

    // Less than operator overload
    bool operator<(const Fraction& f) const {
        return ::operator<(*this, f);
    }

    // Destructor
    ~Fraction() {}
};

// Test program
int main() {
    Fraction f1(1, 2);
    Fraction f2(1, 3);

    //print de la fraction 
    std::cout << "f1: " << f1.numerateur << "/" << f1.denominateur << std::endl;
    std::cout << "f2: " << f2.numerateur << "/" << f2.denominateur << std::endl;

    std::cout << "f1 < f2: " << (f1 < f2) << std::endl;

    return 0;
}
