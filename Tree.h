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
	double result(Node* b,int num)
	{
		double res1 = 0, res2 = 0;
		if (b->getisn() == 1)//���˺�����������Ҫ�ϲ�ڵ��n�����Դ�һ��������ȥ���������ڵ���n��ֱ�ӷ��ز���
			return num;
		if (b->getissingleeye() == 0)
		{
			double ans;
			switch (b->getop())
			{
			case '+':
				res1 = result(b->getleft(),-1);
				res2 = result(b->getright(),-1);
				b->setval(res1 + res2);
				break;
			case '-':
				res1 = result(b->getleft(),-1);
				res2 = result(b->getright(),-1);
				b->setval(res1 - res2);
				break;
			case '*':
				res1 = result(b->getleft(),-1);
				res2 = result(b->getright(),-1);
				b->setval(res1 * res2);
				break;
			case '/':
				res1 = result(b->getleft(),-1);
				res2 = result(b->getright(),-1);
				if (res2 == 0)
				{
					//Ӧ�÷���һ�����󣬵��ǲ���д
				}
				b->setval(res1 / res2);
				break;
			case 'u':
				res1 = result(b->getleft(),-1);
				res2 = result(b->getright(),-1);
				ans = 1;
				for (int i = 0; i < res2; i++)
				{
					ans *= res1;
				}
				b->setval(ans);
			default:return b->getval();
			}
		}
		else if (b->getissingleeye() == 1)
		{
			switch (b->getop())
			{
				case 'r':
					res1 = result(b->getleft(),-1);
					b->setval(sqrt(res1));
					break;
				
			}
		}
		else if (b->getissingleeye() > 1)
		{
			double ans;
			int n = b->getissingleeye();
			switch (b->getop())
			{
			case 'c':
				ans = 0;
				for (int i = 0; i < n; i++)
				{
					res1 = result(b->getleft(), i);
					ans += res1;
				}
				b->setval(ans);
				break;
			case 'n':
				ans = 1;
				for (int i = 0; i < n; i++)
				{
					res1 = result(b->getleft(), i);
					ans *= res1;
				}
				b->setval(ans);
				break;
			}
		}
		return b->getval();
	}
};
#endif _Tree