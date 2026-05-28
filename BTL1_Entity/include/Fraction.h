#ifndef FRACTION_H
#define FRACTION_H

#include <string>

// Forward declaration để tránh circular dependency
class AccuracyFloat;

class Fraction {
private:
    long long numerator;
    long long denominator;
    bool isNegative;

public:
    // Các hàm khởi tạo
    Fraction(long long num, long long den, bool sign);
    Fraction(std::string input);

    // Các phương thức quan trọng
    void simplify();
    std::string toString();
    AccuracyFloat toAccuracyFloat();

    // Nạp chồng toán tử số học
    Fraction operator+(Fraction other);
    Fraction operator-(Fraction other);
    Fraction operator*(Fraction other);
    Fraction operator/(Fraction other);

    // Nạp chồng toán tử so sánh
    bool operator==(Fraction other);
    bool operator!=(Fraction other);
    bool operator>(Fraction other);
    bool operator<(Fraction other);
};

#endif