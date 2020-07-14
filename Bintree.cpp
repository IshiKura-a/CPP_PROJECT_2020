// Bintree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Tree.h"
int main()
{
	Tree* t=new Tree;
	t->root->setop('c');
	t->root->setisSingleEye(10);
	Node* left=new Node, *right=new Node;
	Node* left1 = new Node, *right1 = new Node;
	left1->setisn(1);
	right1->setval(1);
	left->setop('+');
	//left->setval(1);
	//left->setisn(1);
	t->root->setleft(left);
	t->root->setright(right);
	left->setleft(left1);
	left->setright(right1);
	printf("%lf", t->result(t->root,-1));
		return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
