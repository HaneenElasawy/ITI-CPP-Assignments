#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath> 

class Complex {
private:
    double real;
    double imag;

public:
    // ========= Constructors =========
    Complex();                           // Default constructor
    Complex(double r);                   
    Complex(double r, double i);         

    // ========= Getters / Setters =========
    
    double getReal() const;
    double getImag() const;

    void setReal(double r);
    void setImag(double i);

    // ========= (Complex & Complex) =========
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // ========= Compound assignment =========
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    // ========= Unary operators =========
    Complex operator+() const;      
    Complex operator-() const;      

    // ========= Increment / Decrement =========
    Complex& operator++();          
    Complex  operator++(int);       
    Complex& operator--();         
    Complex  operator--(int);       

    // ========= Comparison =========
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    bool operator<(const Complex& other) const;
    bool operator<=(const Complex& other) const;
    bool operator>(const Complex& other) const;
    bool operator>=(const Complex& other) const;
    
    // ========= Friends for I/O =========
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);

    // ========= Friends for (Complex op double) =========
    friend Complex operator+(const Complex& c, double d); 
    friend Complex operator+(double d, const Complex& c);

    friend Complex operator-(const Complex& c, double d);
    friend Complex operator-(double d, const Complex& c);

    friend Complex operator*(const Complex& c, double d);
    friend Complex operator*(double d, const Complex& c);

    friend Complex operator/(const Complex& c, double d);

       //=========Casting=======
    explicit operator double() const;
    //========Index access=======
    double& operator[](int index);
    const double& operator[](int index) const;
};

#endif 
