/*
 * BiTree: for BinaryTree.
 */

#pragma once

#include <iostream>
#include <string>
#include <queue>

using namespace std;

namespace BiTreeSpace {
	const string Test1 = "AB#C#D##E##";
	const string Test2 = "A#BC##DE##F##";
	const string Test3 = "ABCD##E##F###";
}

class BiTree {
private:
	BiTree* pre = nullptr; //ǰһ�������Ľ��
public:
	static const char IMAGE_NODE = '#'; //��ʾ��ڵ���ַ�
	char data;
	BiTree* left = nullptr, * right = nullptr, * parent = nullptr;
	bool LTag, RTag;

	//����һ����㣬��������Ϊdata�����ҡ�˫�׽ڵ�Ϊleft, right, parent
	BiTree(char data, BiTree* left, BiTree* right, BiTree* parent);
	//����Ϊ�����ַ�����������Ӧ��
	BiTree(string layerIter);
	//�������
	static void PreOrderTraverse(BiTree* t, void function(BiTree*));
	//�������
	static void InOrderTraverse(BiTree* t, void function(BiTree*));
	//�������
	static void PostOrderTraverse(BiTree* t, void function(BiTree*));
	//�����������ӳ���
	void PostThreading(BiTree* t);
	//����������
	void PostOrderThreading(BiTree* t);
	//���ú����������ı���
	void PostOrderThreadingTraverse(void function(BiTree*));
	static void printTree(BiTree* t);
};


BiTree::BiTree(char data, BiTree* left, BiTree* right, BiTree* parent)
	: data(data), left(left), right(right), parent(parent),
	LTag(false), RTag(false) {};

BiTree::BiTree(string layerIter) : LTag(false), RTag(false) {
	if (layerIter[0] == IMAGE_NODE) {
		data = IMAGE_NODE;
		cout << "Not a tree!" << endl;
	}
	else {
		//�����ø��ڵ�
		data = layerIter[0];
		queue<BiTree*> lastLayer;
		lastLayer.push(this);
		int nodeNum = 2;
		int index = 1;
		int strlen = layerIter.length();
		//��index��һ�����ַ���layerIter
		while (index < strlen) {
			int qSize = lastLayer.size();
			for (int i = 0; i < qSize; i++) {
				BiTree* curNode = lastLayer.front();
				lastLayer.pop();
				if (layerIter[index] != IMAGE_NODE) {
					//�����һ���ַ�����ʾ��ڵ�
					curNode->left =
						new BiTree(layerIter[index], nullptr, nullptr, curNode);
					lastLayer.push(curNode->left);
				}
				else //��������ڵ�
					curNode->left = nullptr;
				index++;
				if (layerIter[index] != IMAGE_NODE) {
					//�����һ���ַ�����ʾ��ڵ�
					curNode->right =
						new BiTree(layerIter[index], nullptr, nullptr, curNode);
					lastLayer.push(curNode->right);
				}
				else //��������ڵ�
					curNode->right = nullptr;
				index++;
			}
		}
	}
};

void BiTree::PreOrderTraverse(BiTree* t, void function(BiTree*)) {
	if (t != nullptr)
	{
		function(t);
		if (t->LTag == 0)
			PreOrderTraverse(t->left, function);
		if (t->RTag == 0)
			PreOrderTraverse(t->right, function);
	}
}

void BiTree::InOrderTraverse(BiTree* t, void function(BiTree*)) {
	if (t != nullptr)
	{
		if (t->LTag == 0)
			InOrderTraverse(t->left, function);
		function(t);
		if (t->RTag == 0)
			InOrderTraverse(t->right, function);
	}
}

void BiTree::PostOrderTraverse(BiTree* t, void function(BiTree*)) {
	if (t != nullptr)
	{
		if (t->LTag == 0)
			PostOrderTraverse(t->left, function);
		if (t->RTag == 0)
			PostOrderTraverse(t->right, function);
		function(t);
	}
}

void BiTree::PostThreading(BiTree* t) {
	if (t == nullptr)
		return;
	//��������������
	PostThreading(t->left);
	//��������������
	PostThreading(t->right);
	//�Ա�����pre������
	if (t->left == nullptr) {
		t->left = pre;
		t->LTag = true;
	}
	if (pre != nullptr && pre->right == nullptr) {
		pre->RTag = true;
		pre->right = t;
	}
	pre = t;
}

void BiTree::PostOrderThreading(BiTree* t) {
	PostThreading(t);
	if (pre != nullptr && pre->right == nullptr) {
		pre->RTag = true;
		pre->right = t;
	}
}

void BiTree::PostOrderThreadingTraverse(void function(BiTree*)) {
	BiTree* temp = this;
	// �Һ�������ĵ�һ�����
	while (!temp->LTag || !temp->RTag) {
		while (!temp->LTag)
			temp = temp->left;
		while (!temp->RTag)
			temp = temp->right;
	}
	function(temp);

	while (temp != nullptr && temp->parent != nullptr) {
		//����ý����˫�׽����Һ��ӻ�˫�׽ڵ�û���Һ���
		if (temp->parent->right == temp
			|| temp->parent->RTag) {
			temp = temp->parent;
		}
		else {
			//�����̽����˫�׽ڵ���������к��������һ�����
			temp = temp->parent->right;
			// �Һ�������ĵ�һ�����
			while (!temp->LTag || !temp->RTag) {
				while (!temp->LTag)
					temp = temp->left;
				while (!temp->RTag)
					temp = temp->right;
			}
		}
		function(temp);
	}
}

void BiTree::printTree(BiTree* t)
{
	if (t != nullptr)
		cout << t->data;
}
