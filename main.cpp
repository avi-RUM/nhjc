//main.cpp

#include "BigInteger.h"
#include <iostream>
using namespace std;

void main()
{
    BigInteger BigNum1, BigNum2, BigNum3;
    int c;
    cout << "选择你要进行的操作:" << endl;
    cout << "1.大整数加法运算" << endl;
    cout << "2.大整数乘法运算" << endl;
    cout << "选择你需要进行的运算:" << endl;
    cin >> c;
    switch (c)
    {
    case 1:
    {
        cout << "A:" << endl;
        BigNum1.GetNumber();
        cout << "B:" << endl;
        BigNum2.GetNumber();
        BigNum3 = BigNum1 + BigNum2;
        cout << "相加的结果是:" << endl;
        BigNum3.disp();
    }break;
    case 2:
    {
        cout << "A:" << endl;
        BigNum1.GetNumber();
        cout << "B:" << endl;
        BigNum2.GetNumber();
        BigNum3 = BigNum1 * BigNum2;
        cout << "相乘的结果是:" << endl;
        BigNum3.disp();
    }break;
    default:break;
    }
}