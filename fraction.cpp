#include "fraction.h"

static int gcd(int a, int b)
{
    if (a < 0)
    {
        a = -a;
    }
    if (b < 0)
    {
        b = -b;
    }

    while (b != 0)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

Fraction::Fraction()
{
    _numerator = 0;
    _denominator = 1;
}

Fraction::Fraction(int numerator, int denominator)
{
    _numerator = numerator;
    _denominator = denominator;
    fracReduction(*this);
}

int fracReduction(Fraction &frac)
{
    if (frac._denominator == 0)
    {
        return -1;
    }

    if (frac._numerator == 0)
    {
        frac._denominator = 1;
        return -1;
    }

    int divisor = gcd(frac._numerator, frac._denominator);

    if (divisor != 0)
    {
        frac._numerator /= divisor;
        frac._denominator /= divisor;
    }

    if (frac._denominator < 0)
    {
        frac._numerator = -frac._numerator;
        frac._denominator = -frac._denominator;
    }

    return 0;
}

Fraction sum(const Fraction &fr1, const Fraction &fr2)
{
    Fraction result(fr1._numerator * fr2._denominator + fr2._numerator * fr1._denominator,
                    fr1._denominator * fr2._denominator);
    return result;
}

Fraction sub(const Fraction &fr1, const Fraction &fr2)
{
    Fraction result(fr1._numerator * fr2._denominator - fr2._numerator * fr1._denominator,
                    fr1._denominator * fr2._denominator);
    return result;
}

Fraction div(const Fraction &fr1, const Fraction &fr2)
{
    Fraction result(fr1._numerator * fr2._denominator,
                    fr1._denominator * fr2._numerator);
    return result;
}

Fraction mul(const Fraction &fr1, const Fraction &fr2)
{
    Fraction result(fr1._numerator * fr2._numerator,
                    fr1._denominator * fr2._denominator);
    return result;
}

std::ostream &operator<<(std::ostream &out, const Fraction &frac)
{
    out << std::dec << frac._numerator << " / " << frac._denominator;
    return out;
}d::ostream& os, const Fraction& frac) {
    os << frac._numerator << " / " << frac._denominator;
    return os;
}
