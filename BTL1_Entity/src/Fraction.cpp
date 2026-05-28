#include "../include/Fraction.h"
#include "../include/AccuracyFloat.h" // Cần thiết để compiler biết kiểu trả về của toAccuracyFloat()
#include <iostream>
#include <cmath>
#include <stdexcept>

// ---------------- Hàm hỗ trợ (Helper) ----------------
static long long getGCD(long long a, long long b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b > 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Chuyển phân số về một số nguyên có dấu để dễ tính toán (tử số có dấu)
static long long getSignedNum(long long num, bool isNeg) {
    return isNeg ? -num : num;
}

// ---------------- 1. Các hàm khởi tạo ----------------

Fraction::Fraction(long long num, long long den, bool sign) {
    if (den == 0) {
        throw std::invalid_argument("Mẫu số không được bằng 0");
    }
    numerator = std::abs(num);
    denominator = std::abs(den);
    isNegative = sign;
    
    // Chuẩn hóa dấu nếu tham số num hoặc den truyền vào bị âm
    if (num < 0) isNegative = !isNegative;
    if (den < 0) isNegative = !isNegative;
    
    simplify();
}

Fraction::Fraction(std::string input) {
    size_t slashPos = input.find('/');
    if (slashPos != std::string::npos) {
        long long numVal = std::stoll(input.substr(0, slashPos));
        long long denVal = std::stoll(input.substr(slashPos + 1));
        
        if (denVal == 0) {
            throw std::invalid_argument("Mẫu số không được bằng 0");
        }
        
        numerator = std::abs(numVal);
        denominator = std::abs(denVal);
        // XOR để xác định dấu: tử và mẫu khác dấu -> âm (true), cùng dấu -> dương (false)
        isNegative = (numVal < 0) ^ (denVal < 0); 
    } else {
        // Trường hợp chuỗi chỉ là số nguyên (ví dụ: "-5")
        long long numVal = std::stoll(input);
        numerator = std::abs(numVal);
        denominator = 1;
        isNegative = (numVal < 0);
    }
    simplify();
}

// ---------------- 2. Các phương thức quan trọng ----------------

void Fraction::simplify() {
    if (numerator == 0) {
        denominator = 1;
        isNegative = false; // Chuẩn hóa số 0 (không có -0/1)
        return;
    }
    long long gcd = getGCD(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

std::string Fraction::toString() {
    std::string res = "";
    if (isNegative && numerator != 0) {
        res += "-";
    }
    res += std::to_string(numerator) + "/" + std::to_string(denominator);
    return res;
}

AccuracyFloat Fraction::toAccuracyFloat() {
    // Ép kiểu double để thực hiện phép chia lấy số thực
    double val = (isNegative ? -1.0 : 1.0) * numerator / (double)denominator;
    // Khởi tạo đối tượng AccuracyFloat từ double (giả định AccuracyFloat có constructor này)
    return AccuracyFloat(val); 
}

// ---------------- 3. Nạp chồng toán tử số học ----------------

Fraction Fraction::operator+(Fraction other) {
    long long numA = getSignedNum(this->numerator, this->isNegative);
    long long numB = getSignedNum(other.numerator, other.isNegative);
    
    long long resNum = numA * other.denominator + numB * this->denominator;
    long long resDen = this->denominator * other.denominator;
    
    return Fraction(std::abs(resNum), resDen, resNum < 0);
}

Fraction Fraction::operator-(Fraction other) {
    long long numA = getSignedNum(this->numerator, this->isNegative);
    long long numB = getSignedNum(other.numerator, other.isNegative);
    
    long long resNum = numA * other.denominator - numB * this->denominator;
    long long resDen = this->denominator * other.denominator;
    
    return Fraction(std::abs(resNum), resDen, resNum < 0);
}

Fraction Fraction::operator*(Fraction other) {
    long long resNum = this->numerator * other.numerator;
    long long resDen = this->denominator * other.denominator;
    bool resSign = this->isNegative ^ other.isNegative;
    
    return Fraction(resNum, resDen, resSign);
}

Fraction Fraction::operator/(Fraction other) {
    if (other.numerator == 0) {
        throw std::domain_error("Lỗi chia cho 0");
    }
    
    long long resNum = this->numerator * other.denominator;
    long long resDen = this->denominator * other.numerator;
    bool resSign = this->isNegative ^ other.isNegative;
    
    return Fraction(resNum, resDen, resSign);
}

// ---------------- 4. Nạp chồng toán tử so sánh ----------------

bool Fraction::operator==(Fraction other) {
    // Chỉ cần so sánh trực tiếp vì mọi phân số đã được simplify() khi khởi tạo hoặc tính toán
    return (this->numerator == other.numerator) && 
           (this->denominator == other.denominator) && 
           (this->isNegative == other.isNegative);
}

bool Fraction::operator!=(Fraction other) {
    return !(*this == other);
}

bool Fraction::operator<(Fraction other) {
    long long numA = getSignedNum(this->numerator, this->isNegative);
    long long numB = getSignedNum(other.numerator, other.isNegative);
    
    return numA * other.denominator < numB * this->denominator;
}

bool Fraction::operator>(Fraction other) {
    long long numA = getSignedNum(this->numerator, this->isNegative);
    long long numB = getSignedNum(other.numerator, other.isNegative);
    
    return numA * other.denominator > numB * this->denominator;
}