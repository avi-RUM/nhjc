//BigInteger.cpp

#include<iostream>
#include <stdio.h>
#include "BigInteger.h"

using namespace std;

BigInteger::BigInteger()        //构造函数,将每个节点置空.
{
    Head = End = TempNode = NULL;
}

BigInteger::BigInteger(const BigInteger& BigNum)     //拷贝构造
{
    Node* p;
    Head = End = TempNode = NULL;
    p = BigNum.Head;
    while (p)
    {
        AddEnd(p->Num);
        p = p->Next;
    }
}

BigInteger::~BigInteger()        //析构
{
    Node* NextNode;
    if (Head == NULL)
        return;
    TempNode = Head;
    while (TempNode)
    {
        NextNode = TempNode->Next;
        delete TempNode;
        TempNode = NextNode;
    }
    Head = NULL;
    End = NULL;
    TempNode = NULL;
}

void BigInteger::AddHead(char Num)        //在链表头插入节点的操作
{
    TempNode = new Node;
    TempNode->Num = Num;
    TempNode->Prev = NULL;
    if (!Head)
    {
        Head = End = TempNode;
        TempNode->Next = NULL;
    }
    else
    {
        TempNode->Next = Head;
        Head->Prev = TempNode;
        Head = TempNode;
    }
}

void BigInteger::AddEnd(char Num)       //在链表尾插入节点的操作
{
    TempNode = new Node;
    TempNode->Num = Num;
    TempNode->Next = NULL;
    if (!Head)
    {
        Head = End = TempNode;
        TempNode->Prev = NULL;
    }
    else
    {
        TempNode->Prev = End;
        End->Next = TempNode;
        End = TempNode;
    }
}


void BigInteger::GetNumber()            //输入部分
{
    char key,d;
    int count = 0, num = 0;
    scanf_s("%c",&d);          //一个空字符去骗回车
    while ((key = getchar()) != 10)            //判断输入的是否是回车,不是的话将内容从后到前放到链表中.
    {
        if (key >= '0' && key <= '9')
        {
            num = key - '0';
            AddEnd(num);
            num = 0;
        }
    }
}

BigInteger BigInteger::operator + (const BigInteger& BigNum2)    //重载"+"
{
    BigInteger& BigNum1 = *this, result;
    Node* temp1, * temp2;
    int TempNum, rest = 0;
    temp1 = BigNum1.End;            //将临时链表首地址放置到输入链表的尾部
    temp2 = BigNum2.End;
    while (temp1 && temp2)
    {
        TempNum = int(temp1->Num) + int(temp2->Num) + rest;         //节点内元素相加并加上进位rest
        if (TempNum > 9)                  //判断相加结果是否会产生进位.
        {
            TempNum = TempNum - 10;
            rest = 1;
        }
        else
            rest = 0;
        result.AddHead(char(TempNum));          //将结果放置到最终结果链表里
        temp1 = temp1->Prev;
        temp2 = temp2->Prev;
    }
    if (temp2)temp1 = temp2;
    while (temp1)
    {
        int(TempNum) = int(temp1->Num) + rest;           //节点内元素加上进位rest
        if (TempNum > 9)
        {
            TempNum = TempNum - 10;
            rest = 1;
        }
        else
            rest = 0;
        result.AddHead(char(TempNum));             //将结果放置到最终结果链表里
        temp1 = temp1->Prev;
    }
    if (rest)
        result.AddHead(char(rest));                //考虑最后的进位是否存在,如果存在则存入链表的首部.
    return result;
}

BigInteger BigInteger::operator * (const BigInteger& BigNum2)     //对*进行重载
{
    BigInteger& BigNum1 = *this, temp, result;
    Node* temp1, * temp2, * tempa, * tempb;
    int TempNum, rest, i = 0, rest2;
    temp1 = BigNum1.End;
    temp2 = BigNum2.End;
    while (temp2)        //由乘数的存在与否判断是否去乘被乘数的每个位
    {
        rest = 0;
        while (temp1 != NULL)
        {
            TempNum = int(temp1->Num) * int(temp2->Num) + rest;
            if (TempNum > 9)
            {
                rest = TempNum / 10;                 //进位由相乘结果与10做商求得
                TempNum = TempNum % 10;                 //由相乘结果与10求模取个位
            }
            else
                rest = 0;
            temp.AddHead(char(TempNum));        //存入临时链表
            temp1 = temp1->Prev;
        }
        if (rest != 0)temp.AddHead(char(rest));
        for (int k = i; k >= 1; k--)temp.AddEnd(char(0));       //判断应该在链表后面补几个0
        i++;            //每次乘完后计数,用来下一次的补0
        temp1 = BigNum1.End;             //把被乘数重新置到尾,用来让乘数下一次去乘每个元素
        temp2 = temp2->Prev;              //将乘数取出链表的前驱
        tempa = result.End;                  //下面进行的是将每次乘数与被乘数的相乘结果累加放到最终链表里等待输出
        if (result.Head != NULL)           
        {
            result.End = temp.Head;
            result.Head = NULL;
        }
        tempb = temp.End;
        rest2 = 0;
        while (tempa != NULL && tempb != NULL)
        {
            TempNum = int(tempa->Num) + int(tempb->Num) + rest2;
            if (TempNum > 9)
            {
                TempNum = TempNum - 10;
                rest2 = 1;
            }
            else
                rest2 = 0;
            result.AddHead(char(TempNum));
            tempa = tempa->Prev;
            tempb = tempb->Prev;
        }
        if (tempb)tempa = tempb;
        while (tempa)
        {
            int(TempNum) = int(tempa->Num) + rest2;
            if (TempNum > 9)
            {
                TempNum = TempNum - 10;
                rest2 = 1;
            }
            else
                rest2 = 0;
            result.AddHead(char(TempNum));
            tempa = tempa->Prev;
        }
        if (rest2)
            result.AddHead(char(rest2));
        if (temp.Head != NULL)
        {
            temp.End = temp.Head;
            temp.Head = NULL;
        }
        tempb = NULL;
    }
    return result;
}

BigInteger BigInteger::operator = (const BigInteger& BigNum)          //对=号进行重载
{
    if (this == &BigNum)
        return *this;
    Node* p;
    TempNode = Head = End = NULL;
    p = BigNum.Head;
    while (p)
    {
        AddEnd(p->Num);
        p = p->Next;
    }
    return *this;
}

void BigInteger::disp()                    //输出链表
{
    if (Head)
    {
        cout << int(Head->Num);
        TempNode = Head->Next;
    }
    else return;
    while (TempNode)
    {
        cout << int(TempNode->Num);
        TempNode = TempNode->Next;
    }
    cout << endl;
}