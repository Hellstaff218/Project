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
}

int fracReduction(Fraction &frac)
{
    if (frac._denominator == 0)
    {
        return -1;
    }

    if (frac._numerator == 0)
    {
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
