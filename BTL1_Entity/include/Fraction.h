#ifndef FRACTION_H
#define FRACTION_H

#include <string>
#include <bits/stdc++.h>

using namespace std;
class Fraction {
private:
    long long num = 0;
    long long den = 1;
    bool sign = 0;

public:
    Fraction(long long num, long long den, bool sign);
    Fraction(string input);

    void simplify();
    string toString();
    Fraction operator+(Fraction other);
    Fraction operator-(Fraction other);
    Fraction operator*(Fraction other);
    Fraction operator/(Fraction other);
    bool operator==(Fraction other);
    bool operator=(Fraction other);
    bool operator!=(Fraction other);
    bool operator>(Fraction other);
    bool operator<(Fraction other);
    bool getsign();
};

#endif
