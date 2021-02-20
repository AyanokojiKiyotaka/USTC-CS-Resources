#include <iostream>
#include <string>
#include <queue>
#pragma once

using namespace std;

class BTreeNode {
private:
	BTreeNode* pre = nullptr; //ǰһ�������Ľ��
public:
	static const char IMAGE_NODE = '#'; //��ʾ��ڵ���ַ�
	char data;
	BTreeNode* left = nullptr, * right = nullptr, * parent = nullptr;
	bool LTag, RTag;

	//����һ����㣬��������Ϊdata�����ҡ�˫�׽ڵ�Ϊleft, right, parent
	BTreeNode(char data, BTreeNode* left, BTreeNode* right, BTreeNode* parent);
	//����Ϊ�����ַ�����������Ӧ��
	BTreeNode(string layerIter);
	//�������
	static void PreOrderTraverse(BTreeNode* t, void function(BTreeNode*));
	//�������
	static void InOrderTraverse(BTreeNode* t, void function(BTreeNode*));
	//�������
	static void PostOrderTraverse(BTreeNode* t, void function(BTreeNode*));
	//�����������ӳ���
	void PostThreading(BTreeNode* t);
	//����������
	void PostOrderThreading(BTreeNode* t);
	//���ú����������ı���
	void PostOrderThreadingTraverse(void function(BTreeNode*));
};


BTreeNode::BTreeNode(char data, BTreeNode* left, BTreeNode* right, BTreeNode* parent)
	: data(data), left(left), right(right), parent(parent),
	LTag(false), RTag(false) {};

BTreeNode::BTreeNode(string layerIter) : LTag(false), RTag(false) {
	if (layerIter[0] == IMAGE_NODE) {
		data = IMAGE_NODE;
		cout << "Not a tree!" << endl;
	}
	else {
		//�����ø��ڵ�
		data = layerIter[0];
		queue<BTreeNode*> lastLayer;
		lastLayer.push(this);
		int nodeNum = 2;
		int index = 1;
		int strlen = layerIter.length();
		//��index��һ�����ַ���layerIter
		while (index < strlen) {
			int qSize = lastLayer.size();
			for (int i = 0; i < qSize; i++) {
				BTreeNode* curNode = lastLayer.front();
				lastLayer.pop();
				if (layerIter[index] != IMAGE_NODE) {
					//�����һ���ַ�����ʾ��ڵ�
					curNode->left =
						new BTreeNode(layerIter[index], nullptr, nullptr, curNode);
					lastLayer.push(curNode->left);
				}
				else //��������ڵ�
					curNode->left = nullptr;
				index++;
				if (layerIter[index] != IMAGE_NODE) {
					//�����һ���ַ�����ʾ��ڵ�
					curNode->right =
						new BTreeNode(layerIter[index], nullptr, nullptr, curNode);
					lastLayer.push(curNode->right);
				}
				else //��������ڵ�
					curNode->right = nullptr;
				index++;
			}
		}
	}
};

void BTreeNode::PreOrderTraverse(BTreeNode* t, void function(BTreeNode*)) {
	if (t != nullptr)
	{
		function(t);
		if (t->LTag == 0)
			PreOrderTraverse(t->left, function);
		if (t->RTag == 0)
			PreOrderTraverse(t->right, function);
	}
}

void BTreeNode::InOrderTraverse(BTreeNode* t, void function(BTreeNode*)) {
	if (t != nullptr)
	{
		if (t->LTag == 0)
			InOrderTraverse(t->left, function);
		function(t);
		if (t->RTag == 0)
			InOrderTraverse(t->right, function);
	}
}

void BTreeNode::PostOrderTraverse(BTreeNode* t, void function(BTreeNode*)) {
	if (t != nullptr)
	{
		if (t->LTag == 0)
			PostOrderTraverse(t->left, function);
		if (t->RTag == 0)
			PostOrderTraverse(t->right, function);
		function(t);
	}
}

void BTreeNode::PostThreading(BTreeNode* t) {
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

void BTreeNode::PostOrderThreading(BTreeNode* t) {
	PostThreading(t);
	if (pre != nullptr && pre->right == nullptr) {
		pre->RTag = true;
		pre->right = t;
	}
}

void BTreeNode::PostOrderThreadingTraverse(void function(BTreeNode*)) {
	BTreeNode* temp = this;
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