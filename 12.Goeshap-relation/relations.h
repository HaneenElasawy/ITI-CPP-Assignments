#ifndef RELATIONS_H
#define RELATIONS_H

#include <iostream>

class GeoShape {
private:
    float dim1; 
    float dim2; 

public:
    GeoShape(float d1 = 0, float d2 = 0);
    
    void setDim1(float d1);
    void setDim2(float d2);
    
    float getDim1() const;
    float getDim2() const;

    //(Pure Virtual Function)
    virtual float calculateArea() = 0; 
    
    // Virtual destructor
    virtual ~GeoShape() = default;
};

// class Triangle
class Triangle : public GeoShape {
public:
    // Constructor
    Triangle(float base, float height);
    
    float calculateArea() override;
};

// class Rect
class Rect : public GeoShape {
public:
    // Constructor
    Rect(float length, float width);
    
    float calculateArea() override;
};

//class Square
class Square : private Rect {
public:
    // Constructor
    Square(float side);

    // Provide setter and getter functions for the square's side length.
    void setSide(float side);
    float getSide() const;

    float calculateArea() override;
};

//class Circle that privately inherits from GeoShape
class Circle : private GeoShape {
private:
    const float PI = 3.14159f;
public:
    // Constructor
    Circle(float radius);
    
    // Provide setter and getter functions for the circle's radius.
    void setRadius(float radius);
    float getRadius() const;

    float calculateArea() override;
};

#endif