// Bintree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Tree.h"
int main()
{
	Tree* t=new Tree;
	t->root->setop('c');
	t->root->setisSingleEye(3);
	Node* left=new Node, *right=new Node;
	Node* left1 = new Node, *right1 = new Node;
	Node* left2 = new Node, *right2 = new Node;
	Node* left3 = new Node, *right3 = new Node;


	//left->setisn(0);
	t->root->setleft(left);
	t->root->setright(right);
	
	//right1->setval(1);
	left->setop('c');
	left->setisSingleEye(3);
	//left1->setisn(1);
	left1->setop('+');
	//left2->setop('+');
	left2->setisn(1);
	right2->setisn(0);
	//left->setval(1);

	left->setleft(left1);
	left->setright(right1);
	left1->setleft(left2);
	left1->setright(right2);
	//left2->setleft(left3);
	//left2->setright(right3);
	//int num[1] = { 0 };
	//<int> num{ 0 };	
	//这个测试的式子是sum（sum（m+n）），m和n范围都是0-2
	printf("%lf", t->result(t->root,t->root->vari));
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
