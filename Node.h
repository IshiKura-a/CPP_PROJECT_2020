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
	int isSingleEye;
	bool isn;

public:
	Node()
	{
		op = '\0';
		val = 0;
		left = NULL;
		right = NULL;
		isSingleEye = 0;
		isn = 0;
	}
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
	bool getisn()
	{
		return isn;
	}
	void setisn(bool n)
	{
		isn = n;
	}
	bool isleaf()
	{
		if (left == NULL && right == NULL)
			return 1;
		else
			return 0;
	}
	void setisSingleEye(int num)
	{
		isSingleEye = num;
	}
	int getisSingleEye()
	{
		return isSingleEye;
	}
	
};
#endif _Node