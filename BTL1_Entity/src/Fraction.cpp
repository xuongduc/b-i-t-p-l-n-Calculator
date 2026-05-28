#include "../include/Fraction.h"

Fraction::Fraction(long long num, long long den, bool sign){

    if(den == 0){
        this -> num = 0; this -> den = 0; this -> sign = 0;
        cout << "Loi";
    }else{
        this -> num = num;
        this -> den = den;
        this -> sign = sign;
    }
}
Fraction::Fraction(string input){
    int i;
    int c;
    if (input[0] == '-'){
        this -> sign = 1;
        i = 1;
    }else{
        this -> sign = 0;
        i = 0;
    }
    while(input[i] != '/'){
        c = (input[i] - '0');
        this -> num = num * 10 + c;
        i += 1;
        }
        i += 1;
    while(input[i] != '/0'){
        c = (input[i] - '0');
         this -> den = den * 10 + c;
        i += 1;
        }
    }
long long Uoc(long long a, long long b){
    int t = 0;
    if (a > b){
        for (int i = b; i >= 2; --i){
            if (a % i ==0 && b % i == 0){
                t = i;
                break;
            }
        }
    }else{
        for (int i = a; i >= 2; --i){
            if (a % i ==0 && b % i == 0){
                t = i;
                break;
            }
        }
    }
    return t;
}
void Fraction::simplify(){
    long long uoc = Uoc(this -> num, this -> den);
    if (uoc != 0){
        this -> num /= uoc;
        this -> den /= uoc;
    }
}
bool Fraction::getsign(){
    return this -> sign;
}
string intToString(long long a){
    string t;
    while(a > 0){
        t += a%10 + '0';
        a /= 10;
    }
    reverse(t.begin(), t.end());
    return t;
}
string Fraction::toString(){
    string n;
    if (this -> sign){
        n += '-';
    }
    string t = intToString(num);
    string m = intToString(den);
    n += t + '/'+ m;
    return n;
}
Fraction Fraction::operator+(Fraction other){
    long long i;
    long long t; 
    long long dau;
    if (this -> den > other.den){
        i = this -> den;
        while(i % other.den == 0 && i % this -> den == 0){
            ++i;
        }
    }else{
         i = other.den;
        while(i % other.den == 0 && i % this -> den == 0){
            ++i;
        }
    }
    this -> num = (i / this -> den) * this -> num;
    other.num = (i / other.den) * other.den;
    Fraction kq;

    if (this -> sign == other.sign){
       t = this -> num + other.num;
       dau = other.sign;
    }else{
        if (this -> num > other.num){
            t = this -> num - other.num;
            dau = this -> sign;
        }else{
            t =  other.num - this -> num;
            dau = other.sign;
        }
    }
    return Fraction (t, i, dau);
} 
Fraction Fraction::operator-(Fraction other){
    other.sign = !other.sign;
    return *this + other;
}
Fraction Fraction::operator*(Fraction other){
    long long i = this -> num * other.num;
    long long t = this -> den * other.den;
    long long dau = !(this -> sign && other.sign);
    return Fraction (i,t,dau);
}
Fraction Fraction::operator/(Fraction other){
    long long i = this -> num * other.den;
    long long t = this -> den * other.num;
    long long dau = !(this -> sign && other.sign);
    return Fraction (i, t, dau);
}
bool Fraction::operator==(Fraction other){
    this -> simplify();
    other.simplify();
    if (this -> num == other.num && this -> den == other.den && this -> sign == other.sign){
        return 1;
    }
    return 0;
}
bool Fraction::operator=(Fraction other){
    this -> num = other.num;
    this -> den = other.den;
    this -> sign = other.sign;
    return 1;
}
bool Fraction::operator>(Fraction other){
    Fraction kq = *this - other;
    return !kq.getsign();
}
bool Fraction::operator<(Fraction other){
    return !(*this > other);
}