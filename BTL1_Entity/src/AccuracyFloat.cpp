#include "../include/AccuracyFloat.h"

AccuracyFloat::AccuracyFloat(long long num, long long dec, long long pre, bool sign){
    this -> num = num;
    this -> dec = dec;
    this -> pre = pre;
    this -> sign = sign;
}
AccuracyFloat::AccuracyFloat(string input){
    int i;
    if(input[0] == '-'){
        this -> sign = 1;
        i = 1;
        
    }else{
        this -> sign = 0;
        i = 0;
    }
    this -> num = input[i++] - '0';
        while(input[i] != '.'){
            this -> num = this -> num * 10 + (long long)(input[i] - '0');
            ++i;
        }
        i += 1;
        this -> dec = input[i];
        while (input[i] != '/0'){
            this -> dec = this -> dec * 10 + (long long)(input[i] - '0');
            this -> pre *= 10;
            ++i;
        }
}
AccuracyFloat::AccuracyFloat(double input){
    this -> num = (input * 10) / 10;
    long t = (input * 10) /10;
    for (int i = 0; i <6; ++i){
        input *= 10;
        t *= 10;
    }
    this -> pre = 1000000;
    t = input - t;
    while (t % 10 != 0){
        t /= 10;
        this -> pre /= 10;
    }
    this -> dec = t;
    if (input <0){
        sign = 1;
    }else {
        sign = 0;
    }
}
string AccuracyFloat::toString(){
    string t = "";
    if (sign == 1){
        t += '-';
    }
    while (num != 0){
        t += (num % 10) + '0';
        num /= 10;
    }
    reverse(t.begin(), t.end());
    t += '.';
    long long c = dec + pre;
    string m = "";
    while (c != 1){
        m += (c % 10) + '0';
        c /= 10;
    }
    reverse(m.begin(), m.end());
    t += m;
    return t;
}
double AccuracyFloat::toDouble(){
    double tuT = num;
    dec /= pre;
    tuT += dec;
    if (sign == 1){
        tuT *= -1;
    }
    return tuT;
}
AccuracyFloat AccuracyFloat::operator+(AccuracyFloat other){
    double a = stold((this -> toString()));
    double b = stold((other.toString()));
    a += b;
    long long c = max(this -> pre, other.pre);
    int m = 0;
    while (c > 0){
        ++m;
        c / 10;
    }
    ostringstream t;
    t << fixed << setprecision(m) << a;
    return AccuracyFloat(t.str());
}
AccuracyFloat AccuracyFloat::operator-(AccuracyFloat other){
    double a = stold((this -> toString()));
    double b = stold((other.toString()));
    a -= b;
    long long c = max(this-> pre, other.pre);
    int m = 0;
    while (c >0){
        ++m;
        c / 10;
    }
    ostringstream t;
    t << fixed << setprecision(m) << a;
    return AccuracyFloat(t.str());
}
AccuracyFloat AccuracyFloat::operator*(AccuracyFloat other){
    double a = stold((this-> toString()));
    double b = stold((other.toString()));
    a *= b;
    long long c = max(this-> pre, other.pre);
    int m = 0;
    while (c > 0){
        ++m;
        c / 10;
    }
    ostringstream t;
    t << fixed << setprecision(m) << a;
    return AccuracyFloat(t.str());
}
AccuracyFloat AccuracyFloat::operator/(AccuracyFloat other){
    double a = stold((this-> toString()));
    double b = stold((other.toString()));
    a /= b;
    long long c = max(this-> pre, other.pre);
    int m = 0;
    while(c > 0){
        ++m;
        c / 10;
    }
    ostringstream t;
    t << fixed << setprecision(m) << a;
    return AccuracyFloat(t.str());
}
bool AccuracyFloat::operator==(AccuracyFloat other){
    if(this-> sign == other.sign && this -> num == other.num && this -> dec == other.dec && this -> pre == other.pre){
        return 1;
    }
    return 0;
}
bool AccuracyFloat::operator=(AccuracyFloat other){
    this -> num = other.num;
    this -> pre = other.pre;
    this -> dec = other.dec;
    this -> sign = other.sign;
    return 1;
}
bool AccuracyFloat::operator>(AccuracyFloat other){
    if (this -> sign != other.sign){
        return (!(this-> sign));
    }else{
        if (this -> sign){
            if (this-> num < other.num || (double)(this -> dec) / this -> pre < (double)(other.dec) / other.pre){
                return 1;
            }
        }else{
            if (this-> num > other.num || (double)(this -> dec) / this -> pre > (double)(other.dec) / other.pre){
                return 1;
            }
        }
    }
    return 0;
}
bool AccuracyFloat::operator<(AccuracyFloat other){
    return !(*this > other);
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
