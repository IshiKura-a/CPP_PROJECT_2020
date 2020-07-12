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
public:
	Tree()
	{
		root = new Node;
	}
	double result(Node* b)
	{
		double res1 = 0, res2 = 0;
		if (b->getIsUnary() == 0)
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
		else if (b->getIsUnary() == 1)
		{
			switch (b->getop())
			{
				case 'r':
					res1 = result(b->getleft());
					b->setval(sqrt(res1));
				case 'u':
					res1 = result(b->getleft());
					b->setval(res1 * res1);
			}
		}
		else if (b->getIsUnary() > 1)
		{
			int n = b->getIsUnary();
			switch (b->getop())
			{
			case 'c':
				for (int i = 0; i < n; i++)
				{
					res1 += result(b->getleft());
				}
				b->setval(sqrt(res1));
			case 'n':
				for (int i = 0; i < n; i++)
				{
					res1 *= result(b->getleft());
				}
				b->setval(res1 * res1);
			}
		}
		return b->getval();
	}
};
#endif _Tree