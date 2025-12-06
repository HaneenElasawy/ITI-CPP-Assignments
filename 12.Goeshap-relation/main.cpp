#include <iostream>
#include "relations.h" 
using namespace std;
void printArea(GeoShape* shape) {
    cout << " = " << shape->calculateArea() << endl;
}

int main() {
    cout << "---  Shapes Inheritance ---\n\n";

    Triangle tri(10, 5); 
    printArea(&tri);
    
    Rect rect(8, 4); 
    printArea(&rect);

    cout << "------------------------------------------\n";

    Square sq(6); 
    cout << "Square Area (Side=" << sq.getSide() << "): ";
    cout << sq.calculateArea() << endl; 
    
    sq.setSide(7.5);
    cout << "New Square Area (Side=" << sq.getSide() << "): ";
    cout << sq.calculateArea() << endl;

    cout << "------------------------------------------\n";

    Circle circ(3); 
    cout << "Circle Area (Radius=" << circ.getRadius() << "): ";
    cout << circ.calculateArea() << endl; 

    circ.setRadius(5);
    cout << "New Circle Area (Radius=" << circ.getRadius() << "): ";
    cout << circ.calculateArea() << endl;

    
    return 0;
}