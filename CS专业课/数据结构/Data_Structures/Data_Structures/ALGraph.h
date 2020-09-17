/*
 * ALGraph: for Adjecent Linklist Graph
 */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// ������ࡣ��Ϊ��Ȩ��Ϊ1���ʲ��������Ϣ��Ա����
class ArcNode {
public:
	int adjVex; // �û�ָ��Ķ�������
	ArcNode* nextArc; // ָ����һ����

	ArcNode(int av, ArcNode* na) : adjVex(av), nextArc(na) {};
};

// ���ࡣ
class VNode {
public:
	int index; // �������
	ArcNode* firstArc; //��һ���ڱ�

	// Ĭ�Ϲ��췽��
	VNode() : index(-1), firstArc(nullptr) {};
	// ����ź͵�һ���ڱ߹��춥
	VNode(int index, ArcNode* fa) : index(index), firstArc(fa) {};
	// ���һ��������
	void addAdjArc(ArcNode* arcnode);
};

class ALGraph {
public:
	VNode* vexs; //��
	int vexNum = 0, arcNum = 0; //����������
	int* distance = NULL; // ��Dijkstra�㷨�õ������·������
	int* front = NULL; // ��Dijkstra�㷨�õ���ǰ�����

	// ���캯����ͨ���ļ�������
	ALGraph(string fileName);
	// Dijkstra�㷨ʵ��
	void ShortestPath_DIJ();
	// ͨ��front������Ѱ�ҵ�0�����·��
	void printShortestPath(int i);
	// ͨ��front������Ѱ�ҵ�0�����·��
	void printAllShortestPath();
	// ��ӡ�ڽӱ�
	void printAdjacentList();
};

void VNode::addAdjArc(ArcNode* arcnode)
{
	if (firstArc == NULL) {
		firstArc = arcnode;
		return;
	}
	ArcNode* p = firstArc;
	while (p->nextArc != NULL) p = p->nextArc;
	p->nextArc = arcnode;
	return;
}

void ALGraph::ShortestPath_DIJ()
{
	// һЩ��ʼ��
	bool* defined = new bool[vexNum];
	for (int i = 0; i < vexNum; i++) {
		distance[i] = INT_MAX;
		defined[i] = false;
	}
	// �ȿ���0��
	int v = 0;
	ArcNode* an = vexs[v].firstArc;
	while (an != NULL) {
		distance[an->adjVex] = 1;
		front[an->adjVex] = v;
		an = an->nextArc;
	}
	// �������ж�
	for (int i = 0; i < vexNum; i++) {
		int minD = INT_MAX;
		// �����·����
		for (int j = 0; j < vexNum; j++) {
			if (!defined[j]) {
				if (distance[j] < minD) {
					v = j; minD = distance[j];
				}
			}
		}
		defined[v] = true;
		// �������·��
		an = vexs[v].firstArc;
		while (an != NULL) {
			if (distance[an->adjVex] > minD + 1) {
				distance[an->adjVex] = minD + 1;
				front[an->adjVex] = v;
			}
			an = an->nextArc;
		}
	}
}

ALGraph::ALGraph(string fileName) {
	fstream fs(fileName, ios::in | ios::out);
	// ���붥����
	string line;
	fs >> vexNum;
	getline(fs, line);
	// ���䶥��Ŀռ�
	vexs = new VNode[vexNum];
	if (vexs == NULL) return;
	for (int i = 0; i < vexNum; i++) {
		vexs[i].index = i;
	}
	// ����distance�ռ�
	distance = new int[vexNum];
	if (distance == NULL) return;
	memset(distance, 0, sizeof(int) * vexNum);
	// ����front�ռ�
	front = new int[vexNum];
	if (front == NULL) return;
	memset(front, 0, sizeof(int) * vexNum);

	// ��������
	while (!fs.eof()) {
		getline(fs, line);
		stringstream ss(line);
		int h, t;
		ss >> h >> t;
		vexs[h].addAdjArc(new ArcNode(t, nullptr));
		vexs[t].addAdjArc(new ArcNode(h, nullptr));
		arcNum++;
	}
}

void ALGraph::printShortestPath(int i)
{
	int t = i;
	stack<int> s;
	while (t != 0) {
		s.push(t);
		t = front[t];
	}
	int ssize = s.size();
	cout << distance[i] << " 0";
	for (int t = 0; t < ssize; t++) {
		cout << "->" << s.top();
		s.pop();
	}
	cout << endl;
}

void ALGraph::printAllShortestPath()
{
	for (int i = 1; i < vexNum; i++) {
		printShortestPath(i);
	}
}

void ALGraph::printAdjacentList()
{
	for (int i = 0; i < vexNum; i++) {
		cout << i << ":";
		ArcNode* p = vexs[i].firstArc;
		while (p != NULL) {
			cout << p->adjVex << " ";
			p = p->nextArc;
		}
		cout << endl;
	}
}