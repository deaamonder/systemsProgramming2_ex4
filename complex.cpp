#include <iostream>

using namespace std;

class Complex{
    private:
        double real;
        double image;

    public:
        //constructor
        Complex(double r, double i){
            this->image = i;
            this->real = r;
        } 

        //operators
        bool operator==(Complex other) const{
            return (this->image==other.image) && (this->real==other.real);
        }

        Complex operator+(const Complex& other) const {
            return Complex(this->real + other.real, this->image + other.image);
        }

        Complex operator-(const Complex& other) const {
            return Complex(this->real - other.real, this->image - other.image);
        }

        Complex operator*(const Complex& other) const {
            return Complex(
                this->real * other.real - this->image * other.image,
                this->real * other.image + this->image * other.real
            );
        }

        Complex operator/(const Complex& other) const {
            double denominator = other.real * other.real + other.image * other.image;
            return Complex(
                (this->real * other.real + this->image * other.image) / denominator,
                (this->image * other.real - this->real * other.image) / denominator
            );
        }

        friend ostream& operator<<(ostream& os, const Complex& c) {
            os << c.real << " + " << c.image << "i";
            return os;
        }
        
};