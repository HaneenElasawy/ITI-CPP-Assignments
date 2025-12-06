#include "relations.h"
#include <iostream>

GeoShape::GeoShape(float d1, float d2) : dim1(d1), dim2(d2) {}

void GeoShape::setDim1(float d1) { this->dim1 = d1; }
void GeoShape::setDim2(float d2) { this->dim2 = d2; }
float GeoShape::getDim1() const { return dim1; }
float GeoShape::getDim2() const { return dim2; }

Triangle::Triangle(float base, float height) : GeoShape(base, height) {}

float Triangle::calculateArea() {
    std::cout << "Triangle Area (0.5 * " << getDim1() << " * " << getDim2() << ")";
    return 0.5f * getDim1() * getDim2();
}

Rect::Rect(float length, float width) : GeoShape(length, width) {}

float Rect::calculateArea() {
    std::cout << "Rect Area (" << getDim1() << " * " << getDim2() << ")";
    return getDim1() * getDim2();
}

Square::Square(float side) : Rect(side, side) {}

void Square::setSide(float side) {
    setDim1(side); 
    setDim2(side);
}

float Square::getSide() const {
    return getDim1(); 
}

float Square::calculateArea() {
    return Rect::calculateArea();
}

Circle::Circle(float radius) : GeoShape(radius, 0) {}

void Circle::setRadius(float radius) {
    setDim1(radius);
}

float Circle::getRadius() const {
    return getDim1();
}

float Circle::calculateArea() {
    float radius = getDim1();
    std::cout << "Circle Area (" << PI << " * " << radius << "^2)";
    return PI * radius * radius;
}