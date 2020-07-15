#pragma once
#include<iostream>
#include<memory>
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
	double result(Node* b,vector<int> num)
	{
		double res1 = 0, res2 = 0;
		//memcpy(b->vari, num, sizeof(int)*(b->vari[0] + 1));
		if(num.size()>0)
		b->vari.assign(num.begin(),num.end());
		if (b->getisn() >= 0)//连乘和连加由于需要上层节点的n，所以传一个参数下去，如果这个节点是n，直接返回参数
			return (double)b->vari[b->getisn()];
		if (b->getisSingleEye() == 0)
		{
			double ans;
			switch (b->getop())
			{
			case '+':
				res1 = result(b->getleft(), b->vari);
				res2 = result(b->getright(), b->vari);
				b->setval(res1 + res2);
				break;
			case '-':
				res1 = result(b->getleft(), b->vari);
				res2 = result(b->getright(), b->vari);
				b->setval(res1 - res2);
				break;
			case '*':
				res1 = result(b->getleft(), b->vari);
				res2 = result(b->getright(), b->vari);
				b->setval(res1 * res2);
				break;
			case '/':
				res1 = result(b->getleft(), b->vari);
				res2 = result(b->getright(), b->vari);
				if (res2 == 0)
				{
					//应该返回一个错误，但是不会写
					exit(1);
				}
				b->setval(res1 / res2);
				break;
			case 'u':
				res1 = result(b->getleft(), b->vari);
				res2 = result(b->getright(), b->vari);
				ans = 1;
				for (int i = 0; i < res2; i++)
				{
					ans *= res1;
				}
				b->setval(ans);
			case 'l'://log,左边底数右边真数
				res1 = result(b->getleft(), b->vari);
				res2 = result(b->getright(), b->vari);
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
					
					res1 = result(b->getleft(), b->vari);
					if(res1<0)
						exit(1);
					b->setval(sqrt(res1));
					break;
				case '1'://sin
					res1 = result(b->getleft(), b->vari);
					
					b->setval(sin(res1* PI / 180.0));
					break;
				case '2'://cos
					res1 = result(b->getleft(), b->vari);
					b->setval(cos(res1* PI / 180.0));
					break;
				case '3'://tan
					res1 = result(b->getleft(), b->vari);
					b->setval(tan(res1* PI / 180.0));
					break;
				case '4'://asin
					res1 = result(b->getleft(), b->vari);
					if (res1 > 1 || res1 < -1)
					{
						//返回异常
						exit(1);
					}
					b->setval(asin(res1));
					break;
				case '5'://acos
					res1 = result(b->getleft(), b->vari);
					if (res1 > 1 || res1 < -1)
					{
						//返回异常
						exit(1);
					}
					b->setval(acos(res1));
					break;
				case '6'://atan
					res1 = result(b->getleft(), b->vari);
					if (res1 > 1 || res1 < -1)
					{
						//返回异常
						exit(1);
					}
					b->setval(atan(res1));
					break;
				case 'e'://exp
					res1 = result(b->getleft(), b->vari);
					b->setval(exp(res1));
					break;
				case '7'://ln
					res1 = result(b->getleft(), b->vari);
					b->setval(log(res1));
					break;
				case '8'://log10
					res1 = result(b->getleft(), b->vari);
					b->setval(log10(res1));
					break;
			}
		}
		else if (b->getisSingleEye() > 1)
		{
			double ans;
			int n = b->getisSingleEye();
			//int *p = b->vari.end();
			switch (b->getop())
			{
				
			case 'c':
				ans = 0;
				//p += b->vari[0];
				//b->vari[0]++;
				for (int i = 0; i < n; i++)
				{
					//*p = i;
					
					b->vari.push_back(i);
					res1 = result(b->getleft(), b->vari);
					ans += res1;
					b->vari.pop_back();
				}
				b->setval(ans);
				break;
			case 'n':
				ans = 1;
				//int *p = b->vari + 1;
				//p += b->vari[0];
				//b->vari[0]++;
				for (int i = 0; i < n; i++)
				{
					//*p = i;
					b->vari.pop_back();
					b->vari.push_back(i);
					res1 = result(b->getleft(), b->vari);
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