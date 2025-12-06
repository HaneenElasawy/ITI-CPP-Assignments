#include "complex.h"
#include <stdexcept>   //   runtime_error & out_of_range

using namespace std;

// ========= Constructors =========
Complex::Complex() : real(0.0), imag(0.0) {}

Complex::Complex(double r) : real(r), imag(0.0) {}

Complex::Complex(double r, double i) : real(r), imag(i) {}

// ========= Getters =========
double Complex::getReal() const { return real; }
double Complex::getImag() const { return imag; }

// ========= Setters =========
void Complex::setReal(double r) { real = r; }
void Complex::setImag(double i) { imag = i; }

// ========= Arithmetic =========
Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    double r = real * other.real - imag * other.imag;
    double i = real * other.imag + imag * other.real;
    return Complex(r, i);
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.real * other.real + other.imag * other.imag;

    if (denom == 0.0)
        throw std::runtime_error("Division by zero complex number");

    double r = (real * other.real + imag * other.imag) / denom;
    double i = (imag * other.real - real * other.imag) / denom;

    return Complex(r, i);
}

// ========= Compound assignment =========
Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    imag -= other.imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double r = real * other.real - imag * other.imag;
    double i = real * other.imag + imag * other.real;
    real = r;
    imag = i;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double denom = other.real * other.real + other.imag * other.imag;

    if (denom == 0.0)
        throw std::runtime_error("Division by zero complex number");

    double r = (real * other.real + imag * other.imag) / denom;
    double i = (imag * other.real - real * other.imag) / denom;

    real = r;
    imag = i;
    return *this;
}

// ========= Unary operators =========
Complex Complex::operator+() const {
    return *this;
}

Complex Complex::operator-() const {
    return Complex(-real, -imag);
}

// ========= Increment / Decrement =========
Complex& Complex::operator++() {
    real += 1;
    return *this;
}

Complex Complex::operator++(int) {
    Complex temp(*this);
    real += 1;
    return temp;
}

Complex& Complex::operator--() {
    real -= 1;
    return *this;
}

Complex Complex::operator--(int) {
    Complex temp(*this);
    real -= 1;
    return temp;
}

// ========= Comparison =========
bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

bool Complex::operator<(const Complex& other) const {
    return real < other.real;
}

bool Complex::operator<=(const Complex& other) const {
    return real <= other.real;
}

bool Complex::operator>(const Complex& other) const {
    return real > other.real;
}

bool Complex::operator>=(const Complex& other) const {
    return real >= other.real;
}

// ========= I/O =========
ostream& operator<<(ostream& os, const Complex& c) {
    os << "(" << c.real
       << (c.imag >= 0 ? " + " : " - ")
       << std::fabs(c.imag) << "i)";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    is >> c.real >> c.imag;
    return is;
}

// ========= Complex op double =========
Complex operator+(const Complex& c, double d) {
    return Complex(c.real + d, c.imag);
}

Complex operator+(double d, const Complex& c) {
    return c + d;
}

Complex operator-(const Complex& c, double d) {
    return Complex(c.real - d, c.imag);
}

Complex operator-(double d, const Complex& c) {
    return Complex(d - c.real, -c.imag);
}

Complex operator*(const Complex& c, double d) {
    return Complex(c.real * d, c.imag * d);
}

Complex operator*(double d, const Complex& c) {
    return c * d;
}

Complex operator/(const Complex& c, double d) {
    if (d == 0.0)
        throw std::runtime_error("Division by zero scalar");
    return Complex(c.real / d, c.imag / d);
}

// ========= Casting to double (magnitude) =========
Complex::operator double() const {
    return std::sqrt(real * real + imag * imag);
}

// ========= Index access =========
double& Complex::operator[](int index) {
    if (index == 0) {
        return real;
    } else if (index == 1) {
        return imag;
    } else {
        throw std::out_of_range("Complex index must be 0 (real) or 1 (imag)");
    }
}


