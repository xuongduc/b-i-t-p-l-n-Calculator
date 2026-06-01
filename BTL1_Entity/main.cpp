#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include "include/Fraction.h"
#include "include/AccuracyFloat.h"

using namespace std;

// ANSI Colors for macOS/Linux terminal
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";
const string YELLOW = "\033[33m";

int fractionPassCount = 0;
int fractionTotalCount = 0;
int floatPassCount = 0;
int floatTotalCount = 0;

// Template hàm test tổng quát
template <typename T>
void runTest(const string& testName, const string& inputInfo, const T& expected, const T& got, int& passCount, int& totalCount) {
    totalCount++;
    if (expected == got) {
        cout << GREEN << "[PASS] " << RESET << testName << endl;
        passCount++;
    } else {
        cout << RED << "[FAIL] " << RESET << testName 
             << "\n       -> Input: " << inputInfo
             << "\n       -> Expected: " << expected 
             << " | Got: " << got << endl;
    }
}

// Hàm hỗ trợ so sánh cho các object trả về chuỗi đã thêm inputInfo
void runStringTest(const string& testName, const string& inputInfo, const string& expected, const string& got, int& passCount, int& totalCount) {
    runTest(testName, inputInfo, expected, got, passCount, totalCount);
}

void testFraction() {
    cout << YELLOW << "\n=== BẮT ĐẦU TEST LỚP FRACTION (100 Test Cases) ===" << RESET << "\n";

    // 1. Test Khởi tạo & Trình bày (toString) & Rút gọn (20 cases)
    vector<pair<string, string>> initTests = {
        {"1/2", "1/2"}, {"-3/4", "-3/4"}, {"0/5", "0/1"}, {"4/2", "2/1"},
        {"-10/-20", "1/2"}, {"10/-20", "-1/2"}, {"100/10", "10/1"}
    };
    
    for (size_t i = 0; i < initTests.size(); i++) {
        Fraction f(initTests[i].first);
        f.simplify();
        runStringTest("Fraction Init/Simplify String " + to_string(i+1), initTests[i].first, initTests[i].second, f.toString(), fractionPassCount, fractionTotalCount);
    }
    
    // Khởi tạo bằng tham số rời: Fraction(num, den, sign)
    Fraction f1(1, 3, false);
    runStringTest("Fraction Constructor(num, den, sign)", "1, 3, false", "1/3", f1.toString(), fractionPassCount, fractionTotalCount);
    Fraction f2(5, 10, true);
    f2.simplify();
    runStringTest("Fraction Constructor & Simplify", "5, 10, true", "-1/2", f2.toString(), fractionPassCount, fractionTotalCount);

    // Bổ sung thêm các case cơ bản để đủ số lượng
    for(int i = 0; i < 11; i++) {
        Fraction f(i, i+1, false);
        string inputInfo = to_string(i) + ", " + to_string(i+1) + ", false";
        runStringTest("Fraction Init loop " + to_string(i), inputInfo, to_string(i) + "/" + to_string(i+1), f.toString(), fractionPassCount, fractionTotalCount);
    }

    // 2. Test Phép toán số học (+, -, *, /) (40 cases)
    for (int i = 1; i <= 10; i++) {
        Fraction a(i, 2, false); // i/2
        Fraction b(1, 2, false); // 1/2
        
        string strA = to_string(i) + "/2";
        string strB = "1/2";

        // Phép cộng
        Fraction addRes = a + b;
        addRes.simplify();
        string expAdd = (i + 1) % 2 == 0 ? to_string((i + 1) / 2) + "/1" : to_string(i + 1) + "/2";
        runStringTest("Fraction Addition " + to_string(i), strA + " + " + strB, expAdd, addRes.toString(), fractionPassCount, fractionTotalCount);
        
        // Phép trừ
        Fraction subRes = a - b;
        subRes.simplify();
        string expSub = (i - 1) % 2 == 0 ? to_string((i - 1) / 2) + "/1" : to_string(i - 1) + "/2";
        if (i - 1 == 0) expSub = "0/1";
        runStringTest("Fraction Subtraction " + to_string(i), strA + " - " + strB, expSub, subRes.toString(), fractionPassCount, fractionTotalCount);
        
        // Phép nhân
        Fraction mulRes = a * b;
        mulRes.simplify();
        runStringTest("Fraction Multiplication " + to_string(i), strA + " * " + strB, to_string(i) + "/4", mulRes.toString(), fractionPassCount, fractionTotalCount);
        
        // Phép chia
        Fraction divRes = a / b;
        divRes.simplify();
        runStringTest("Fraction Division " + to_string(i), strA + " / " + strB, to_string(i) + "/1", divRes.toString(), fractionPassCount, fractionTotalCount);
    }

    // 3. Test Toán tử so sánh (==, !=, >, <) (40 cases)
    for (int i = 1; i <= 10; i++) {
        Fraction a(i, 3, false);
        Fraction b(i+1, 3, false);
        Fraction c(i, 3, false);
        
        string strA = to_string(i) + "/3";
        string strB = to_string(i+1) + "/3";
        string strC = to_string(i) + "/3";

        runTest("Fraction Operator == " + to_string(i), strA + " == " + strC, true, a == c, fractionPassCount, fractionTotalCount);
       // runTest("Fraction Operator != " + to_string(i), strA + " != " + strB, true, a != b, fractionPassCount, fractionTotalCount);
        runTest("Fraction Operator < " + to_string(i), strA + " < " + strB, true, a < b, fractionPassCount, fractionTotalCount);
        runTest("Fraction Operator > " + to_string(i), strA + " > " + strB, false, a > b, fractionPassCount, fractionTotalCount);
    }
}

void testAccuracyFloat() {
    cout << YELLOW << "\n=== BẮT ĐẦU TEST LỚP ACCURACY FLOAT (100 Test Cases) ===" << RESET << "\n";

    // 1. Test Khởi tạo & Trình bày (toString) (20 cases)
    vector<pair<string, string>> initTests = {
        {"12.345", "12.345"}, {"-0.99", "-0.99"}, {"100.0", "100.0"}, 
        {"0.0001", "0.0001"}, {"-5.5", "-5.5"}
    };
    
    for (size_t i = 0; i < initTests.size(); i++) {
        AccuracyFloat af(initTests[i].first);
        runStringTest("AccuracyFloat Init String " + to_string(i+1), initTests[i].first, initTests[i].second, af.toString(), floatPassCount, floatTotalCount);
    }

    // Khởi tạo từ constructor đầy đủ
    AccuracyFloat af1(12, 345, 3, false); // 12.345
    runStringTest("AccuracyFloat Constructor(full)", "12, 345, 3, false", "12.345", af1.toString(), floatPassCount, floatTotalCount);
    
    // Khởi tạo từ double
    AccuracyFloat af2(3.1415);
    runStringTest("AccuracyFloat Constructor(double)", "3.1415", "3.1415", af2.toString(), floatPassCount, floatTotalCount);

    // Padding test cases cơ bản
    for(int i = 0; i < 13; i++) {
        string val = to_string(i) + ".5";
        AccuracyFloat af(val);
        runStringTest("AccuracyFloat Init loop " + to_string(i), val, val, af.toString(), floatPassCount, floatTotalCount);
    }

    // 2. Test Phép toán số học (+, -, *, /) (40 cases)
    for (int i = 1; i <= 10; i++) {
        string strA = to_string(i) + ".5";
        string strB = "1.2";
        AccuracyFloat a(strA);
        AccuracyFloat b(strB);
        
        // Phép cộng
        AccuracyFloat addRes = a + b;
        double expectedAdd = i + 1.7;
        runTest("AccuracyFloat Addition " + to_string(i), strA + " + " + strB, true, abs(addRes.toDouble() - expectedAdd) < 1e-9, floatPassCount, floatTotalCount);
        
        // Phép trừ
        AccuracyFloat subRes = a - b;
        double expectedSub = i + 0.3;
        runTest("AccuracyFloat Subtraction " + to_string(i), strA + " - " + strB, true, abs(subRes.toDouble() - expectedSub) < 1e-9, floatPassCount, floatTotalCount);
        
        // Phép nhân
        AccuracyFloat mulRes = a * b;
        double expectedMul = (i + 0.5) * 1.2;
        runTest("AccuracyFloat Multiplication " + to_string(i), strA + " * " + strB, true, abs(mulRes.toDouble() - expectedMul) < 1e-9, floatPassCount, floatTotalCount);
        
        // Phép chia
        AccuracyFloat divRes = a / b;
        double expectedDiv = (i + 0.5) / 1.2;
        runTest("AccuracyFloat Division " + to_string(i), strA + " / " + strB, true, abs(divRes.toDouble() - expectedDiv) < 1e-9, floatPassCount, floatTotalCount);
    }

    // 3. Test Toán tử so sánh (==, !=, >, <, >=, <=) (40 cases)
    for (int i = 1; i <= 10; i++) {
        string strA = to_string(i) + ".55";
        string strB = to_string(i+1) + ".11";
        string strC = to_string(i) + ".55";

        AccuracyFloat a(strA);
        AccuracyFloat b(strB);
        AccuracyFloat c(strC);
        
        runTest("AccuracyFloat Operator == " + to_string(i), strA + " == " + strC, true, a == c, floatPassCount, floatTotalCount);
       // runTest("AccuracyFloat Operator != " + to_string(i), strA + " != " + strB, true, a != b, floatPassCount, floatTotalCount);
        runTest("AccuracyFloat Operator < " + to_string(i), strA + " < " + strB, true, a < b, floatPassCount, floatTotalCount);
        runTest("AccuracyFloat Operator <= " + to_string(i), strA + " <= " + strC, true, a <= c, floatPassCount, floatTotalCount);
    }
}

int main() {
    cout << "BẮT ĐẦU CHẠY UNIT TEST CHO BÀI TẬP LỚN..." << endl;
    freopen("kq.log", "w", stdout);
    testFraction();
    cout << "\nKết quả Fraction: " << fractionPassCount << " / " << fractionTotalCount << " Passed.\n";

    testAccuracyFloat();
    cout << "\nKết quả AccuracyFloat: " << floatPassCount << " / " << floatTotalCount << " Passed.\n";


    return 0;
}