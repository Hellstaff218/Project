#pragma once

struct Fraction
{
    int _numerator;   //< числитель
    int _denominator; //< знаменатель

    Fraction();
    Fraction(int numerator, int denominator);
};

int fracReduction(Fraction &frac);
