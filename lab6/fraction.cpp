#include "fraction.h"
#include <cstdlib>
#include <iostream>

Fraction::Fraction(Fraction const &fraction) {
    numerator = fraction.numerator;
    denominator = fraction.denominator;
}

Fraction::Fraction(int a, int b) {
    numerator = a;
    denominator = b;
    integer = 0;
}

Fraction::Fraction(int a, int b, bool simplify) {
    numerator = a;
    denominator = b;
    integer = 0;
    if (simplify)
        ConvertToSimple();
}

Fraction::Fraction() {
    std::cout << "I'm a simple program. I see no number, I do exit."
              << std::endl;
    std::exit(1);
}

void Fraction::Print() {
  if (integer !=0 ){
    std::cout << integer ;
  }
  if (numerator != 0 ) {
    std::cout << numerator << ((integer != 0) ? " + " : "") << "/" << denominator << std::endl;
  }
}

int Fraction::GCD(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    return a + b;
}

int Fraction::LCM(int a, int b) { return std::abs(a * b) / GCD(a, b); }

void Fraction::ConvertToSimple() {
    int gcd = GCD(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;

    integer = numerator / denominator;
    numerator = numerator - (integer * denominator);
    if (numerator == 0) {
      denominator = 0;
    }
}

void Fraction::ConvertToIrregural() {
    numerator = (integer * denominator) + numerator;
    integer = 0;
}

int Fraction::GetDenominator() { return denominator; }

int Fraction::GetNumerator() { return numerator; }

void Fraction::SetNumerator(int number) { numerator = number; }

void Fraction::SetDenominator(int number) { denominator = number; }

void Fraction::DumbDivide(Fraction const &number) {
    ConvertToIrregural();
    numerator = numerator * number.denominator;
    denominator = denominator * number.numerator;
};

void Fraction::Divide(Fraction const &number) { DumbDivide(number); }

void Fraction::Divide(Fraction const &number, bool simplify) {
    DumbDivide(number);
    if (simplify)
        ConvertToSimple();
};
void Fraction::DumbMultiply(Fraction const &number) {
    ConvertToIrregural();
    numerator = number.numerator * numerator;
    denominator = number.denominator * denominator;
};

void Fraction::Multiply(Fraction const &number) { DumbMultiply(number); }

void Fraction::Multiply(Fraction const &number, bool simplify) {
    DumbMultiply(number);
    if (simplify)
        ConvertToSimple();
};

void Fraction::DumbAdd(Fraction const &number) {
    int lcm = LCM(denominator, number.denominator);
    int FirstMultiple = lcm / denominator;
    int SecondMultiple = lcm / number.denominator;
    numerator = numerator * FirstMultiple;
    denominator = denominator * FirstMultiple;
    int secondNumerator = number.numerator * SecondMultiple;
    numerator = numerator + secondNumerator;
};

void Fraction::Add(Fraction const &number) { DumbAdd(number); }

void Fraction::Add(Fraction const &number, bool simplify) {
    DumbAdd(number);
    if (simplify)
        ConvertToSimple();
};
