#pragma once
#include<iostream>
using namespace std;
#ifndef _Node
#define _Node
class Node
{
private:
	char op;
	double val;
	Node *left, *right;
	int isUnary; //判断是否为单目运算符

public:
	Node()
	{
		op = '\0';
		val = 0;
		left = NULL;
		right = NULL;
		isUnary = 0;
	}//构造函数
	double getval()
	{
		return val;
	}
	char& getop()
	{
		return op;
	}
	void setop(char c)
	{
		op = c;
	}
	void setval(double data)
	{
		val = data;
	}
	Node* getleft()
	{
		return left;
	}
	Node* getright()
	{
		return right;
	}
	void setleft(Node* b)
	{
		left = b;
	}
	void setright(Node* b)
	{
		right = b;
	}
	~Node()
	{
		delete left;
		delete right;
	}
	bool isleaf()
	{
		if (left == NULL && right == NULL)
			return 1;
		else
			return 0;
	}
	void setisUnary(int num)
	{
		isUnary = num;
	}
	int getisUnary()
	{
		return isUnary;
	}
	
};
#endif _Node