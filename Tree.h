#pragma once
#include<iostream>
#include<cmath>
#include"Node.h"
using namespace std;
#ifndef _Tree
#define _Tree
class Tree
{
public:
	Node* root;
	Tree()
	{
		root = new Node;
	}
	double result(Node* b)
	{
		double res1 = 0, res2 = 0;
		if (b->getisUnary() == 0)
		{
			switch (b->getop())
			{
			case '+':
				res1 = result(b->getleft());
				res2 = result(b->getright());
				b->setval(res1 + res2);
				break;
			case '-':
				res1 = result(b->getleft());
				res2 = result(b->getright());
				b->setval(res1 - res2);
				break;
			case '*':
				res1 = result(b->getleft());
				res2 = result(b->getright());
				b->setval(res1 * res2);
				break;
			case '/':
				res1 = result(b->getleft());
				res2 = result(b->getright());
				if (res2 == 0)  
				{

				}
				b->setval(res1 / res2);
				break;
			default:return b->getval();
			}
		}
		else if (b->getisUnary() == 1) 
		{
			switch (b->getop())
			{
				case 'r':
					res1 = result(b->getleft());  //递归计算
					b->setval(sqrt(res1)); 
				case 'u':
					res1 = result(b->getleft());
					b->setval(res1 * res1);   //u代表平方
			}
		}
		else if (b->getisUnary() > 1)
		{
			int n = b->getisUnary();
			switch (b->getop())
			{
			case 'c':
				for (int i = 0; i < n; i++)
				{
					res1 += result(b->getleft());  //多次相加?
				}
				b->setval(sqrt(res1));
			case 'n':
				for (int i = 0; i < n; i++)
				{
					res1 *= result(b->getleft());  //累乘?
				}
				b->setval(res1 * res1);
			}
		}
		return b->getval();
	}
};
#endif _Tree