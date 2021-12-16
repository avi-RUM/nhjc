#pragma once
//BigInteger.h

struct Node        //定义了节点的结构
{
	char Num;
	Node* Prev, * Next;
};

class BigInteger      //定义BigInteger 类
{
	Node* Head, * End, * TempNode;
	void AddHead(char Num);
	void AddEnd(char Num);
public:
	BigInteger();
	BigInteger(const BigInteger& BigNum);
	void GetNumber();
	void disp();
	BigInteger operator + (const BigInteger& BigNum);
	BigInteger operator * (const BigInteger& BigNum);
	BigInteger operator = (const BigInteger& BigNum);
	~BigInteger();
};