#include "../include/AccuracyFloat.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor 1: Khởi tạo bằng tham số
AccuracyFloat::AccuracyFloat(long long num, long long dec, long long pre, bool sign){
    this -> num = num;
    this -> dec = dec;
    this -> pre = pre;
    this -> sign = sign;
}

// Constructor 2: Khởi tạo từ chuỗi (Đã sửa lỗi loop khi thiếu dấu '.' và lỗi rác ASCII)
AccuracyFloat::AccuracyFloat(string input){
    this->num = 0;
    this->dec = 0;
    this->pre = 1; // Khởi tạo pre mặc định bằng 1
    this->sign = 0;
    
    if (input.empty()) return;

    int i = 0;
    if(input[0] == '-'){
        this -> sign = 1;
        i = 1;
    }

    // Đọc phần nguyên (Thêm điều kiện dừng input[i] != '\0' để tránh loop vô hạn)
    if (input[i] != '\0' && input[i] != '.') {
        this -> num = input[i++] - '0';
        while(input[i] != '\0' && input[i] != '.'){
            this -> num = this -> num * 10 + (long long)(input[i] - '0');
            ++i;
        }
    }
    
    // Đọc phần thập phân
    if (input[i] == '.'){
        i += 1;
        if (input[i] != '\0') {
            this -> dec = input[i] - '0'; // Sửa lỗi gán ký tự ASCII gốc
            this -> pre *= 10;
            ++i;
            while (input[i] != '\0'){
                this -> dec = this -> dec * 10 + (long long)(input[i] - '0');
                this -> pre *= 10;
                ++i;
            }
        }
    }
}

// Constructor 3: Khởi tạo từ số double
AccuracyFloat::AccuracyFloat(double input){
    this -> num = (input * 10) / 10;
    long t = (input * 10) /10;
    for (int i = 0; i < 6; ++i){
        input *= 10;
        t *= 10;
    }
    this -> pre = 1000000;
    t = input - t;
    while (t != 0 && t % 10 == 0){ // Sửa điều kiện bóc tách số 0 an toàn hơn
        t /= 10;
        this -> pre /= 10;
    }
    this -> dec = t;
    if (input < 0){
        sign = 1;
    } else {
        sign = 0;
    }
}

// Hàm chuyển đổi sang chuỗi (Đã sửa lỗi tự hủy biến num và lỗi loop c != 1)
string AccuracyFloat::toString(){
    string t = "";
    if (sign == 1 && (num != 0 || dec != 0)){
        t += '-';
    }

    string temp = "";
    long long temp_num = num; // Dùng biến tạm để không làm thay đổi giá trị gốc của object
    
    if (temp_num == 0) {
        temp = "0";
    } else {
        while (temp_num != 0){
            temp += (temp_num % 10) + '0';
            temp_num /= 10;
        }
        reverse(temp.begin(), temp.end());
    }
    t += temp;
    t += '.';

    long long c = dec + pre;
    temp = "";
    while (c > 1){ // Sửa c != 1 thành c > 1 để chặn đứng vòng lặp vô hạn khi c tụt về 0
        temp += (c % 10) + '0';
        c /= 10;
    }
    reverse(temp.begin(), temp.end());
    t += temp;
    return t;
}

// Hàm chuyển đổi sang số double (Đã sửa lỗi ép kiểu chia số nguyên)
double AccuracyFloat::toDouble(){
    double tuT = num;
    tuT += (double)dec / pre; // Ép kiểu sang double để không bị mất phần thập phân
    if (sign == 1){
        tuT *= -1;
    }
    return tuT;
}

// Toán tử cộng
AccuracyFloat AccuracyFloat::operator+(AccuracyFloat other){
    double a = stold((this -> toString()));
    double b = stold((other.toString()));
    a += b;
    long long c = max(this -> pre, other.pre);
    int m = 0;
    while (c > 0){
        ++m;
        c /= 10;
    }
    ostringstream t;
    t << fixed << setprecision(m) << a;
    return AccuracyFloat(t.str());
}

// Toán tử trừ
AccuracyFloat AccuracyFloat::operator-(AccuracyFloat other){
    double a = stold((this -> toString()));
    double b = stold((other.toString()));
    a -= b;
    long long c = max(this-> pre, other.pre);
    int m = 0;
    while (c > 0){
        ++m;
        c /= 10;
    }
    ostringstream t;
    t << fixed << setprecision(m) << a;
    return AccuracyFloat(t.str());
}

// Toán tử nhân
AccuracyFloat AccuracyFloat::operator*(AccuracyFloat other){
    double a = stold((this-> toString()));
    double b = stold((other.toString()));
    a *= b;
    long long c = max(this-> pre, other.pre);
    int m = 0;
    while (c > 0){
        ++m;
        c /= 10;
    }
    ostringstream t;
    t << fixed << setprecision(m) << a;
    return AccuracyFloat(t.str());
}

// Toán tử chia
AccuracyFloat AccuracyFloat::operator/(AccuracyFloat other){
    double a = stold((this-> toString()));
    double b = stold((other.toString()));
    a /= b;
    long long c = max(this-> pre, other.pre);
    int m = 0;
    while(c > 0){
        ++m;
        c /= 10;
    }
    ostringstream t;
    t << fixed << setprecision(m) << a;
    return AccuracyFloat(t.str());
}

// Toán tử so sánh bằng
bool AccuracyFloat::operator==(AccuracyFloat other){
    if(this-> sign == other.sign && this -> num == other.num && this -> dec == other.dec && this -> pre == other.pre){
        return 1;
    }
    return 0;
}

// Toán tử gán
bool AccuracyFloat::operator=(AccuracyFloat other){
    this -> num = other.num;
    this -> pre = other.pre;
    this -> dec = other.dec;
    this -> sign = other.sign;
    return 1;
}

// Toán tử so sánh lớn hơn
bool AccuracyFloat::operator>(AccuracyFloat other){
    if (this -> sign != other.sign){
        return (!(this-> sign));
    } else {
        if (this -> sign){
            if (this-> num < other.num || (double)(this -> dec) / this -> pre < (double)(other.dec) / other.pre){
                return 1;
            }
        } else {
            if (this-> num > other.num || (double)(this -> dec) / this -> pre > (double)(other.dec) / other.pre){
                return 1;
            }
        }
    }
    return 0;
}

// Các toán tử so sánh còn lại kế thừa từ toán tử chuẩn
bool AccuracyFloat::operator<(AccuracyFloat other){
    return !(*this > other) && !(*this == other);
}

bool AccuracyFloat::operator>=(AccuracyFloat other){
    return *this > other || *this == other;
}

bool AccuracyFloat::operator<=(AccuracyFloat other){
    return *this < other || *this == other;
}

bool AccuracyFloat::operator!=(AccuracyFloat other){
    return !(*this == other);
}