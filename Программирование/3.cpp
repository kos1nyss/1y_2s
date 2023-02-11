#include <iostream>


class Complex {
private:
    double a, b;

public:
    Complex(double a, double b) {
        this->a = a;
        this->b = b;
    }

    Complex(const Complex& other) {
        a = other.a;
        b = other.b;
    }

    Complex& operator = (const Complex& other) {
        a = other.a;
        b = other.b;
        return *this;
    }

    Complex& operator += (const Complex& other) {
        a += other.a;
        b += other.b;
        return *this;
    }

    Complex& operator + (const Complex& other) {
        Complex new_complex = Complex(a + other.a , b + other.b);
        return new_complex;
    }

    Complex& operator *= (const Complex& other) {
        int new_a, new_b;

        new_a = a * other.a - b * other.b;
        new_b = a * other.b + other.a * b;
        a = new_a;
        b = new_b;

        return *this;
}

    Complex& operator * (const Complex& other) {
        Complex new_complex = Complex(a * other.a - b * other.b, a * other.b + other.a * b);
        return new_complex;
    }

    Complex& operator ++ () {
        ++a;
        return *this;
    }

    Complex& operator ++ (int _) {
        Complex copy(*this);
        a++;
        return copy;
    }

friend std::ostream& operator << (std::ostream& os, const Complex& c);
friend std::istream& operator >> (std::istream& in, Complex& c);
};


std::ostream& operator << (std::ostream& os, const Complex& c) {
    os << c.a << " + " << c.b << 'i';
    return os;
}

std::istream& operator >> (std::istream& in, Complex& c) {
    in >> c.a;
    in >> c.b;
    return in;
}
