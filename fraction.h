#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
 
struct Fraction {
    int _numerator;
    int _denominator;

    // Конструкторы
    Fraction();                           // по умолчанию
    Fraction(int numerator, int denominator);           // с параметрами
};

// Сокращение дроби (из первой задачи)
int fracReduction(Fraction& frac);

// Арифметические операции (из второй задачи)
Fraction sum(const Fraction& fr1, const Fraction& fr2);  // сложение
Fraction sub(const Fraction& fr1, const Fraction& fr2);  // вычитание
Fraction mul(const Fraction& fr1, const Fraction& fr2);  // умножение
Fraction div(const Fraction& fr1, const Fraction& fr2);  // деление

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Fraction& frac);

#endif // FRACTION_H