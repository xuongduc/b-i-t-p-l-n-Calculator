#ifndef ACCURACY_FLOAT_H
#define ACCURACY_FLOAT_H

#include <string>

class AccuracyFloat {
private:
    long long integerPart;
    long long decimalPart;
    long long precisePart;
    bool isNegative;

public:
    // Các hàm khởi tạo
    AccuracyFloat(int integerPart, long long decimalPart, long long precisePart, bool isNegative);
    AccuracyFloat(double input);
    AccuracyFloat(std::string input);

    // Các phương thức chuyển đổi
    std::string toString() const;
    double toDouble() const;

    // Nạp chồng toán tử số học
    AccuracyFloat operator+(const AccuracyFloat& other) const;
    AccuracyFloat operator-(const AccuracyFloat& other) const;
    AccuracyFloat operator*(const AccuracyFloat& other) const;
    AccuracyFloat operator/(const AccuracyFloat& other) const;

    // Nạp chồng toán tử so sánh
    bool operator==(const AccuracyFloat& other) const;
    bool operator!=(const AccuracyFloat& other) const;
    bool operator>(const AccuracyFloat& other) const;
    bool operator<(const AccuracyFloat& other) const;
    bool operator>=(const AccuracyFloat& other) const;
    bool operator<=(const AccuracyFloat& other) const;
};

#endif