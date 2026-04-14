#ifndef _fraction_h_
#define _fraction_h_

#include <iostream>
#include <cstdlib>

struct Fraction {
 int _numerator;
 int _denominator;
 Fraction();
 Fraction(int numerator, int denominator);
};

int fracReduction(Fraction& frac);
std::ostream& operator<<(std::ostream& out, const Fraction& frac);
Fraction sum(const Fraction& fr1, const Fraction& fr2);
Fraction sub(const Fraction& fr1, const Fraction& fr2);
Fraction div(const Fraction& fr1, const Fraction& fr2);
Fraction mul(const Fraction& fr1, const Fraction& fr2);

#endif
