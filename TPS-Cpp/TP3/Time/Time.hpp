#ifndef __TIME_HPP__
#define __TIME_HPP__

#include <iostream>
#include <stdexcept> // For std::invalid_argument

using namespace std; // Add this outside the class

class Time {
private:
  unsigned int hour;
  unsigned int minute;
  unsigned int second;

public:
  Time();
  ~Time();
  Time(int h, int m, int s);
  void set(int h, int m, int s);

  Time& operator++();

  Time& operator--();

  void print() const;
  bool equals(const Time& other) const;

  // Comparison operators
  bool operator==(const Time& other) const; // Implement these
  bool operator!=(const Time& other) const; // Implement these
  bool operator<(const Time& other) const; // Implement these
  bool operator<=(const Time& other) const; // Implement these
  bool operator>(const Time& other) const; // Implement these
  bool operator>=(const Time& other) const; // Implement these
};

#endif
