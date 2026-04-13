#pragma once

#include <ostream>

struct Fraction
{
    int _numerator;   //< числитель
    int _denominator; //< знаменатель

    Fraction();
    Fraction(int numerator, int denominator);
};

int fracReduction(Fraction &frac);

Fraction sum(const Fraction &fr1, const Fraction &fr2); //< сложение
Fraction sub(const Fraction &fr1, const Fraction &fr2); //< вычитание
Fraction div(const Fraction &fr1, const Fraction &fr2); //< деление
Fraction mul(const Fraction &fr1, const Fraction &fr2); //< умножение

std::ostream &operator<<(std::ostream &out, const Fraction &frac);
