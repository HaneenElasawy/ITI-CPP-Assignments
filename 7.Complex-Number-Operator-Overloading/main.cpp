#include <iostream>
#include "complex.h"
using namespace std;

int main() {
    Complex a(3, 4);
    Complex b(1, -2);

    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n\n";

    cout << "a + b = " << (a + b) << "\n";
    cout << "a - b = " << (a - b) << "\n";
    cout << "a * b = " << (a * b) << "\n";
    cout << "a / b = " << (a / b) << "\n\n";

    cout << "a += b: ";
    a += b;
    cout << a << "\n";

    cout << "++a = " << ++a << "\n";
    cout << "a++ = " << a++ << " (before)\n";
    cout << "Now a = " << a << "\n\n";

    Complex x = a + 5;
    Complex y = 5 * a;

    cout << "a + 5 = " << x << "\n";
    cout << "5 * a = " << y << "\n";

    if (x > y)
       cout << "x is larger (by real part)\n";
    else
       cout << "y is larger or equal (by real part)\n";

    return 0;
}
