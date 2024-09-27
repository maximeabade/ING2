#include <iostream>

template<typename T>
class Vector {
private:
    T* elem;
    unsigned int sz;
public:
    Vector(unsigned int s);
    ~Vector() { delete[] elem; }
    T& operator[](unsigned int i);
    const T& operator[](unsigned int i) const;
    unsigned int size() const { return sz; }
};

// Définition du constructeur
template<typename T>
Vector<T>::Vector(unsigned int s) {
    elem = new T[s];
    sz = s;
}

template<typename T>
T& Vector<T>::operator[](unsigned int i) {
    if (i >= sz) throw std::out_of_range("Vector::operator[]");
    return elem[i];
}

template<typename T>
const T& Vector<T>::operator[](unsigned int i) const {
    if (i >= sz) throw std::out_of_range("Vector::operator[]");
    return elem[i];
}

int main() {
    Vector<int> v(5);
    v[0] = 10;
    v[1] = 20;
    v[2] = 30;
    v[3] = 40;
    v[4] = 50;
    std::cout << v[0] << " "<< v[1]<<" "<< v[2]<<" "<< v[3]<<" "<< v[4] << std::endl;
    return 0;
}
