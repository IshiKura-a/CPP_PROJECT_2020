#pragma once
#include<iostream>
#include<cmath>
#include"Node.h"
#define PI 3.14159265
#define E 2.718281828459
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
		if (b->getisSingleEye() == 0)
		{
			double ans;
			switch (b->getop())
			{
			case '+':
				res1 = result(b->getleft(),num);
				res2 = result(b->getright(), num);
				b->setval(res1 + res2);
				break;
			case '-':
				res1 = result(b->getleft(), num);
				res2 = result(b->getright(), num);
				b->setval(res1 - res2);
				break;
			case '*':
				res1 = result(b->getleft(), num);
				res2 = result(b->getright(), num);
				b->setval(res1 * res2);
				break;
			case '/':
				res1 = result(b->getleft(), num);
				res2 = result(b->getright(), num);
				if (res2 == 0)
				{
					//Ӧ�÷���һ�����󣬵��ǲ���д
					exit(1);
				}
				b->setval(res1 / res2);
				break;
			case 'u':
				res1 = result(b->getleft(), num);
				res2 = result(b->getright(), num);
				ans = 1;
				for (int i = 0; i < res2; i++)
				{
					ans *= res1;
				}
				b->setval(ans);
			case 'l'://log,��ߵ����ұ�����
				res1 = result(b->getleft(), num);
				res2 = result(b->getright(), num);
				b->setval(log(res2)/log(res1));
				break;
			default:return b->getval();
			}
		}
		else if (b->getisSingleEye() == 1)
		{
			switch (b->getop())
			{
				case 'r':
					
					res1 = result(b->getleft(), num);
					if(res1<0)
						exit(1);
					b->setval(sqrt(res1));
					break;
				case '1'://sin
					res1 = result(b->getleft(), num);
					
					b->setval(sin(res1* PI / 180.0));
					break;
				case '2'://cos
					res1 = result(b->getleft(), num);
					b->setval(cos(res1* PI / 180.0));
					break;
				case '3'://tan
					res1 = result(b->getleft(), num);
					b->setval(tan(res1* PI / 180.0));
					break;
				case '4'://asin
					res1 = result(b->getleft(), num);
					if (res1 > 1 || res1 < -1)
					{
						//�����쳣
						exit(1);
					}
					b->setval(asin(res1));
					break;
				case '5'://acos
					res1 = result(b->getleft(), num);
					if (res1 > 1 || res1 < -1)
					{
						//�����쳣
						exit(1);
					}
					b->setval(acos(res1));
					break;
				case '6'://atan
					res1 = result(b->getleft(), num);
					if (res1 > 1 || res1 < -1)
					{
						//�����쳣
						exit(1);
					}
					b->setval(atan(res1));
					break;
				case 'e'://exp
					res1 = result(b->getleft(), num);
					b->setval(exp(res1));
					break;
				case '7'://ln
					res1 = result(b->getleft(), num);
					b->setval(log(res1));
					break;
				case '8'://log10
					res1 = result(b->getleft(), num);
					b->setval(log10(res1));
					break;
			}
		}
		else if (b->getisSingleEye() > 1)
		{
			double ans;
			int n = b->getisSingleEye();
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