#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <sstream>

using namespace std;

class Complex {
private:
    double real;
    double img;
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), img(i) {}
    double getReal() const { return real; }
    double getImg() const { return img; }
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    bool operator==(const Complex& other) const;
    friend ostream& operator<<(ostream& os, const Complex& c);
    string to_string();
};

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, img + other.img);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, img - other.img);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - img * other.img, real * other.img + img * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.img * other.img;
    if (denominator == 0) throw runtime_error("Division by zero");
    return Complex((real * other.real + img * other.img) / denominator,
                   (img * other.real - real * other.img) / denominator);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && img == other.img;
}

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real << " + " << c.img << "i";
    return os;
}

string Complex::to_string(){
    ostringstream oss;
    oss << this->getReal() << " + " << this->getImg() << "i";
    return oss.str();
}

#endif //Complex_HPP