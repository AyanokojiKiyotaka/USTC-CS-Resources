#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#pragma once

using namespace std;

class ExpressionTree {
private:
	//�ɲ������ʽ����
	ExpressionTree* createTree_P(stringstream& ss, ExpressionTree* t);
	//���沨�����ʽ����
	ExpressionTree* createTree_IP(stringstream& ss, ExpressionTree* t);
public:
	string op = IMAGE_NODE; //�������������Ϊ�������
	string operand; //������ֵ����Ϊ����
	bool isOperand = false;
	ExpressionTree* left = nullptr, * right = nullptr;
	const string IMAGE_NODE = "#";
	bool isValueGetted = false;
	int value; //����ֵ

	//ͨ��data���Ƿ��ǲ�����������һ�����
	ExpressionTree(string data, bool isOperand);
	//byΪ1��ͨ���������ʽ������byΪ0��ͨ���沨�����ʽ����
	ExpressionTree(string polish, int by);

	//��ӡ��׺���ʽ
	static void printInfixExpression(ExpressionTree* t);
	//��ӡ�������ʽ
	static void printPolishExpression(ExpressionTree* t);
	//��ӡ�沨�����ʽ
	static void printInversePolishExpression(ExpressionTree* t);
	//�����������ֵ
	static int getValue(ExpressionTree* t);
};

ExpressionTree::ExpressionTree(string data, bool isOperand) {
	this->isOperand = isOperand;
	if (isOperand) {
		operand = data;
		stringstream ss(data);
		ss >> value;
		isValueGetted = true;
	}
	else {
		isValueGetted = false;
		op = data[0];
	}
}

ExpressionTree* ExpressionTree::createTree_P(stringstream& ss, ExpressionTree* t) {
	string polish;
	ss >> polish;
	if (polish[0] == '+' || polish[0] == '-'
		|| polish[0] == '*' || polish[0] == '/') {
		if (t != this)
			t = new ExpressionTree(polish, false);
		else {
			t->isOperand = false;
			t->isValueGetted = false;
			t->op = polish[0];
		}
		if (!ss.eof()) {
			t->left = createTree_P(ss, t->left);
			t->right = createTree_P(ss, t->right);
		}
	}
	else {
		t = new ExpressionTree(polish, true);
	}
	return t;
}

ExpressionTree* ExpressionTree::createTree_IP(stringstream& ss, ExpressionTree* t) {
	string polish;
	ss >> polish;
	if (polish[0] == '+' || polish[0] == '-'
		|| polish[0] == '*' || polish[0] == '/') {
		if (t != this)
			t = new ExpressionTree(polish, false);
		else {
			t->isOperand = false;
			t->isValueGetted = false;
			t->op = polish[0];
		}
		if (!ss.eof()) {
			t->right = createTree_IP(ss, t->right);
			t->left = createTree_IP(ss, t->left);
		}
	}
	else {
		t = new ExpressionTree(polish, true);
	}
	return t;
}

ExpressionTree::ExpressionTree(string polish, int by) {
	if (by) {
		stringstream ss(polish);
		createTree_P(ss, this);
	}
	else {
		int len = polish.length();
		stringstream ss(polish);
		string inversed;
		while (!ss.eof()) {
			string temp;
			ss >> temp;
			inversed = temp + " " + inversed;
		}
		stringstream iss(inversed);
		createTree_IP(iss, this);
	}
}

void ExpressionTree::printInfixExpression(ExpressionTree* t) {
	if (t != nullptr) {
		//����������
		if (t->left->isOperand) {
			cout << t->left->operand;
		}
		else {
			if ((t->left->op == "+" || t->left->op == "-")
				&& (t->op == "*" || t->op == "/")) {
				cout << '(';
				printInfixExpression(t->left);
				cout << ')';
			}
			else
				printInfixExpression(t->left);
		}

		//����ǰ���
		if (t->isOperand) {
			cout << t->operand;
		}
		else {
			cout << t->op;
		}

		//����������
		if (t->right->isOperand) {
			cout << t->right->operand;
		}
		else {
			if ((t->right->op == "*" || t->right->op == "/")
				&& (t->op == "+" || t->op == "-")) {
				printInfixExpression(t->right);
			}
			else {
				cout << '(';
				printInfixExpression(t->right);
				cout << ')';
			}
		}
	}
}

void ExpressionTree::printPolishExpression(ExpressionTree* t)
{
	if (t != nullptr) {
		if (t->isOperand)
			cout << t->operand << ' ';
		else
			cout << t->op << ' ';
		printPolishExpression(t->left);
		printPolishExpression(t->right);
	}
}

void ExpressionTree::printInversePolishExpression(ExpressionTree* t)
{
	if (t != nullptr) {
		printInversePolishExpression(t->left);
		printInversePolishExpression(t->right);
		if (t->isOperand)
			cout << t->operand << ' ';
		else
			cout << t->op << ' ';
	}
}

int ExpressionTree::getValue(ExpressionTree* t) {
	if (t->isValueGetted)
		return t->value;
	else {
		if (t->op == "+") {
			t->value = getValue(t->left) + getValue(t->right);
			t->isValueGetted = true;
			return t->value;
		}
		else if (t->op == "-") {
			t->value = getValue(t->left) - getValue(t->right);
			t->isValueGetted = true;
			return t->value;
		}
		else if (t->op == "*") {
			t->value = getValue(t->left) * getValue(t->right);
			t->isValueGetted = true;
			return t->value;
		}
		else if (t->op == "/") {
			t->value = getValue(t->left) / getValue(t->right);
			t->isValueGetted = true;
			return t->value;
		}
	}
}


