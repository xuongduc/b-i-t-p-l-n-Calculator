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
    long long t;
    long long b;
    bool c;
    if (this -> sign == other.sign){
        t = this-> num + other.num;
        if (this-> pre > other.pre){
            b = this-> dec + other.dec *(this -> pre / other.pre);
            if (b > this -> pre){
                b -= this -> pre;
                ++t;
                
            }
            return {t, b, this-> pre, this -> sign};
        }
    b = other.dec + this -> dec * (other.pre / this-> pre);
    if (b > other.pre){
        b -= other.pre;
        ++t;
    }
    return {t, b, other.pre, this -> sign};
    }
    t = abs(this -> num - other.num);
    if (this -> num > other.num){
        c = this-> sign;
    }else if (other.num > this-> num){
        c = other.sign;
    }else{
        if (this-> pre > other.pre){
            if (this -> dec > other.dec *( this -> pre / other.pre)){
                c = this -> sign;
            }else{
                c = other.sign;
            }
        }else{
            if (other.dec > this -> dec *(other.pre / this -> pre)){
                c = other.sign;
            }else{
                c = this-> sign;
            }
        }
    }
    b = this -> dec / this -> pre - other.dec / other.pre;
}
