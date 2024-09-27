#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

class Vector {
  private:
    double* elements;
    unsigned int sz;
  protected:
  public:
    Vector(unsigned int s);
    unsigned int size() const
    double& operator[](unsigned int i);
};

#endif

