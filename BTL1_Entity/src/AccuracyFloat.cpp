#include "../include/Fraction.h"
#include "../include/AccuracyFloat.h" 
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>

// ---------------- 1. Các hàm khởi tạo ----------------

AccuracyFloat::AccuracyFloat(int intPart, long long decPart, long long precPart, bool isNeg) {
    integerPart = std::abs(intPart);
    decimalPart = std::abs(decPart);
    precisePart = std::abs(precPart);
    isNegative = isNeg;
}

AccuracyFloat::AccuracyFloat(std::string input) {
    if (input.empty()) {
        integerPart = 0; decimalPart = 0; precisePart = 0; isNegative = false;
        return;
    }

    // Xử lý dấu
    isNegative = (input[0] == '-');
    if (input[0] == '-' || input[0] == '+') {
        input = input.substr(1);
    }

    size_t dotPos = input.find('.');
    if (dotPos == std::string::npos) {
        // Nếu không có dấu phẩy thập phân
        integerPart = std::stoll(input.empty() ? "0" : input);
        decimalPart = 0;
        precisePart = 0;
    } else {
        // Tách phần nguyên
        std::string intStr = input.substr(0, dotPos);
        integerPart = intStr.empty() ? 0 : std::stoll(intStr);

        // Tách phần thập phân
        std::string decStr = input.substr(dotPos + 1);
        if (decStr.empty()) {
            decimalPart = 0;
            precisePart = 0;
        } else {
            precisePart = decStr.length();
            decimalPart = std::stoll(decStr);
        }
    }
}

AccuracyFloat::AccuracyFloat(double input) {
    // Chuyển double thành string với độ chính xác cao nhất để tái sử dụng logic constructor string
    std::ostringstream out;
    out << std::fixed << std::setprecision(12) << input;
    std::string strVal = out.str();
    
    // Cắt bỏ các số 0 thừa ở cuối phần thập phân
    strVal.erase(strVal.find_last_not_of('0') + 1, std::string::npos);
    if (strVal.back() == '.') {
        strVal.pop_back();
    }
    
    *this = AccuracyFloat(strVal);
}

// ---------------- 2. Các phương thức chuyển đổi ----------------

std::string AccuracyFloat::toString() const {
    std::string res = isNegative ? "-" : "";
    res += std::to_string(integerPart);
    
    if (precisePart > 0) {
        res += ".";
        std::string decStr = std::to_string(decimalPart);
        // Bù thêm các số 0 ở trước nếu cần (vd: decimalPart = 5, precisePart = 3 -> "005")
        if (decStr.length() < precisePart) {
            res += std::string(precisePart - decStr.length(), '0');
        }
        res += decStr;
    }
    return res;
}

double AccuracyFloat::toDouble() const {
    return std::stod(this->toString());
}

// ---------------- 3. Nạp chồng toán tử số học ----------------
// Sử dụng long double trung gian để tính toán và format lại 
// nhằm đảm bảo độ chính xác cao nhất (cao hơn double thông thường).

AccuracyFloat AccuracyFloat::operator+(const AccuracyFloat& other) const {
    long double valA = std::stold(this->toString());
    long double valB = std::stold(other.toString());
    
    std::ostringstream out;
    long long maxPrec = std::max(this->precisePart, other.precisePart);
    out << std::fixed << std::setprecision(maxPrec) << (valA + valB);
    
    return AccuracyFloat(out.str());
}

AccuracyFloat AccuracyFloat::operator-(const AccuracyFloat& other) const {
    long double valA = std::stold(this->toString());
    long double valB = std::stold(other.toString());
    
    std::ostringstream out;
    long long maxPrec = std::max(this->precisePart, other.precisePart);
    out << std::fixed << std::setprecision(maxPrec) << (valA - valB);
    
    return AccuracyFloat(out.str());
}

AccuracyFloat AccuracyFloat::operator*(const AccuracyFloat& other) const {
    long double valA = std::stold(this->toString());
    long double valB = std::stold(other.toString());
    
    std::ostringstream out;
    long long totalPrec = this->precisePart + other.precisePart;
    out << std::fixed << std::setprecision(totalPrec) << (valA * valB);
    
    return AccuracyFloat(out.str());
}

AccuracyFloat AccuracyFloat::operator/(const AccuracyFloat& other) const {
    if (other.integerPart == 0 && other.decimalPart == 0) {
        throw std::domain_error("Lỗi chia cho 0");
    }
    
    long double valA = std::stold(this->toString());
    long double valB = std::stold(other.toString());
    
    std::ostringstream out;
    // Phép chia có thể ra số thập phân vô hạn, set cứng giới hạn 12 số sau dấu phẩy
    out << std::fixed << std::setprecision(12) << (valA / valB);
    
    std::string resultStr = out.str();
    // Dọn dẹp số 0 thừa
    resultStr.erase(resultStr.find_last_not_of('0') + 1, std::string::npos);
    if (resultStr.back() == '.') resultStr.pop_back();
    
    return AccuracyFloat(resultStr);
}

// ---------------- 4. Nạp chồng toán tử so sánh ----------------

bool AccuracyFloat::operator==(const AccuracyFloat& other) const {
    // Nếu cả hai đều bằng 0 (kể cả 0.0 và -0.0)
    if (this->integerPart == 0 && this->decimalPart == 0 &&
        other.integerPart == 0 && other.decimalPart == 0) return true;
        
    // Dùng toDouble so sánh biên (có thể dùng string parsing nếu muốn khắt khe tuyệt đối)
    return std::abs(this->toDouble() - other.toDouble()) < 1e-12;
}

bool AccuracyFloat::operator!=(const AccuracyFloat& other) const {
    return !(*this == other);
}

bool AccuracyFloat::operator<(const AccuracyFloat& other) const {
    return this->toDouble() < other.toDouble();
}

bool AccuracyFloat::operator>(const AccuracyFloat& other) const {
    return this->toDouble() > other.toDouble();
}

bool AccuracyFloat::operator>=(const AccuracyFloat& other) const {
    return !(*this < other);
}

bool AccuracyFloat::operator<=(const AccuracyFloat& other) const {
    return !(*this > other);
}