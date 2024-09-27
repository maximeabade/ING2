#include "Time.hpp"
using namespace std;
#include <stdexcept>

int main() {
    Time t1(23, 59, 59);
    t1.print();
    cout << endl;

    ++t1;
    t1.print();
    cout << endl;

    --t1; 
    t1.print();
    cout << endl;

    Time t2(23, 59, 59);
    t2.print();
    cout << endl;

    cout << (t1 == t2) << endl; // 1 if true, otherwise 0
    t1.print();
    t2.print();
    cout << (t1 != t2) << endl;
    cout << (t1 < t2) << endl;
    cout << (t1 <= t2) << endl;
    cout << (t1 > t2) << endl;
    cout << (t1 >= t2) << endl;

    return 0;
}
