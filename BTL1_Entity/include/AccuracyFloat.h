#ifndef ACCURACY_FLOAT_H
#define ACCURACY_FLOAT_H

#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class AccuracyFloat {
private:
    long long num = 0;
    long long dec = 0;
    long long pre = 10;
    bool sign;
public:
    AccuracyFloat(long long num, long long dec, long long pre, bool sign);
    AccuracyFloat(double input);
    AccuracyFloat(string input);
    string toString();
    double toDouble();
    AccuracyFloat operator+(AccuracyFloat other);
    AccuracyFloat operator-(AccuracyFloat other);
    AccuracyFloat operator*(AccuracyFloat other);
    AccuracyFloat operator/(AccuracyFloat other);
    bool operator==(AccuracyFloat other);
    bool operator=(AccuracyFloat other);
    bool operator>(AccuracyFloat other);
    bool operator<(AccuracyFloat other);
    bool operator>=(AccuracyFloat other);
    bool operator<=(AccuracyFloat other);
};

#endif
