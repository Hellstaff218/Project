#include "fraction.h"
#include <cstdlib> 



Fraction::Fraction() : _numerator(0), _denominator(1) {}

Fraction::Fraction(int numerator, int denominator) : _numerator(numerator), _denominator(denominator) {
    if (_denominator < 0) {
        _numerator = -_numerator;
        _denominator = -_denominator; 
    }
}



static int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}



int fracReduction(Fraction& frac) {
   
    

  
    if (frac._denominator == 0) {
        return -1;
    }

    
    if (frac._denominator < 0) {
        frac._numerator = -frac._numerator;
        frac._denominator = -frac._denominator;
    }

   
    int divisor = gcd(frac._numerator, frac._denominator);
    frac._numerator /= divisor;
    frac._denominator /= divisor;

    return 0;
}



static Fraction reduce(Fraction frac) {
    if (frac._numerator == 0) {
        frac._denominator = 1;
        return frac;
    }

    if (frac._denominator < 0) {
        frac._numerator = -frac._numerator;
        frac._denominator = -frac._denominator;
    }

    int divisor = gcd(frac._numerator, frac._denominator);
    frac._numerator /= divisor;
    frac._denominator /= divisor;

    return frac;
}



Fraction sum(const Fraction& fr1, const Fraction& fr2) {
    int num = fr1._numerator * fr2._denominator + fr2._numerator * fr1._denominator;
    int den = fr1._denominator * fr2._denominator;
    return reduce(Fraction(num, den));
}

Fraction sub(const Fraction& fr1, const Fraction& fr2) {
    int num = fr1._numerator * fr2._denominator - fr2._numerator * fr1._denominator;
    int den = fr1._denominator * fr2._denominator;
    return reduce(Fraction(num, den));
}

Fraction mul(const Fraction& fr1, const Fraction& fr2) {
    int num = fr1._numerator * fr2._numerator;
    int den = fr1._denominator * fr2._denominator;
    return reduce(Fraction(num, den));
}

Fraction div(const Fraction& fr1, const Fraction& fr2) {
    int num = fr1._numerator * fr2._denominator;
    int den = fr1._denominator * fr2._numerator;
    return reduce(Fraction(num, den));
}



std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac._numerator << " / " << frac._denominator;
    return os;
}