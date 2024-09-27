#include <iostream>
#include "Time.hpp"
#include <iomanip> // For std::setfill and std::setw
using namespace std;

Time::~Time() {} // Empty destructor is allowed

Time::Time() {
  hour = 0;
  minute = 0;
  second = 0;
}

Time::Time(int h, int m, int s) {
  if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
    throw std::invalid_argument("Invalid time values"); // Handle invalid input
  }
  hour = h;
  minute = m;
  second = s;
}

void Time::set(int h, int m, int s) {
  if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
    throw std::invalid_argument("Invalid time values"); // Handle invalid input
  }
  hour = h;
  minute = m;
  second = s;
}

void Time::print() const {
  std::cout << std::setfill('0') << std::setw(2) << hour << ":";
  std::cout << std::setfill('0') << std::setw(2) << minute << ":";
  std::cout << std::setfill('0') << std::setw(2) << second << std::endl;
}

Time& Time::operator++() {
  second++;
  if (second == 60) {
    second = 0;
    minute++;
    if (minute == 60) {
      minute = 0;
      hour++;
      if (hour == 24) {
        hour = 0;
      }
    }
  }
  return *this;
}

Time& Time::operator--(void) { // Use void for post-decrement
  if (second == 0) {
    second = 59;
    if (minute == 0) {
      minute = 59;
      if (hour == 0) {
        hour = 23;
      } else {
        hour--;
      }
    } else {
      minute--;
    }
  } else {
    second--;
  }
  return *this;
}

bool Time::equals(const Time& other) const {
  return hour == other.hour && minute == other.minute && second == other.second;
}

bool Time::operator==(const Time& other) const {
  return equals(other);
}

bool Time::operator!=(const Time& other) const {
  return !equals(other);
}

bool Time::operator<(const Time& other) const {
  if (hour < other.hour) {
    return true;
  } else if (hour > other.hour) {
    return false;
  } else if (minute < other.minute) {
    return true;
  } else if (minute > other.minute) {
    return false;
  } else {
    return second < other.second; // Compare seconds last
  }
}

bool Time::operator<=(const Time& other) const {
  return *this < other || *this == other;
}

bool Time::operator>(const Time& other) const {
  return !(*this <= other);
}

bool Time::operator>=(const Time& other) const {
  return !(*this < other);
}
