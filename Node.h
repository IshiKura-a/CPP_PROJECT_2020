#pragma once
#include<iostream>
#include<vector>
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
	int isn;
	
public:
	vector<int> vari;
	int start;
	Node()
	{
		op = '\0';
		val = 0;
		left = NULL;
		right = NULL;
		isSingleEye = 0;
		isn = -1;
		start = 0;
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
	int getisn()
	{
		return isn;
	}
	void setisn(int n)
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