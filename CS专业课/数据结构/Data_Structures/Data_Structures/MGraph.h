/*
 * MGraph: for Adjecent Matrix Graph
 */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Vertex {
public:
	int index;
};

// ͼ�࣬���ڽӾ����ʾ����ͼ
class MGraph {
private:
	int* visited = NULL;
	// �Ӷ�k��ʼ��DFSѰ�����Ȧ��
	void FindMaxCircleThrough(int& k, int v, int weight, vector<int>* curCircle);
public:
	Vertex* vexs = NULL;
	int** arcs = NULL; //�ڽӾ���ֱֵ����Ȩ����Ϊ0�����ʾ������
	bool edgeWeighted = false;
	int vexNum = 0, arcNum = 0;
	vector<int> Articul;

	bool hasCircle = false;
	int maxWeight = 0;
	vector<int> maxCircle;

	MGraph(string fileName);
	// ��ӡ�ڽӾ���
	void PrintMatrix();
	// �ҹؽڵ�����������������ҵ����и����Articul��
	void FindArticul();
	// �Ҹ��DFS����
	void DFSArticul(int v0, int& count, int* visited, int* low);
	// �����Ȧ�ĺ���
	void FindMaxCircle();
	// ��ӡ���Ȧ
	void PrintMaxCircle();
	// ��ӡ�
	void PrintArticul();
	// ��ӡ������������Graphvizͼ�Ĵ��루��
	void PrintGraphvizCode();
};

void MGraph::FindMaxCircleThrough(int& k, int v, int weight, vector<int>* curCircle) {
	visited[v] = true;
	curCircle->push_back(v);
	for (int i = 0; i < vexNum; i++) {
		if (arcs[v][i] != 0) {
			if (i == k && curCircle->size() > 2) {
				//˵���ҵ���һ��Ȧ
				if (weight + arcs[v][i] > maxWeight) {
					// ��֮ǰ�ҵ��ĸ���
					maxWeight = weight + arcs[v][i];
					maxCircle = *curCircle;
					continue;
				}
			}
			else if (!visited[i]) {
				// δ���ʶ������������
				FindMaxCircleThrough(k, i, weight + arcs[v][i], curCircle);
				continue;
			}
		}
	}
	curCircle->pop_back();
	visited[v] = false;
}

MGraph::MGraph(string fileName) {
	fstream fs(fileName, ios::in | ios::out);
	// ���붥����
	string line;
	fs >> vexNum;
	getline(fs, line);
	// ���䶥��Ŀռ�
	vexs = new Vertex[vexNum];
	if (vexs == NULL) return;
	for (int i = 0; i < vexNum; i++) {
		vexs[i].index = i;
	}
	// ����visited�Ŀռ�
	visited = new int[vexNum];
	if (visited == NULL) return;
	memset(visited, 0, sizeof(int) * vexNum);
	// ����߾���ռ�
	arcs = new int* [vexNum];
	if (arcs == NULL) return;
	for (int i = 0; i < vexNum; i++) {
		arcs[i] = new int[vexNum];
		if (arcs[i] == NULL) return;
		memset(arcs[i], 0, sizeof(int) * vexNum);
	}
	// ��������
	while (!fs.eof()) {
		getline(fs, line);
		stringstream ss(line);
		int h, t;
		ss >> h >> t;
		// �������Ƿ��е��������������˵�������˱�Ȩ
		if (ss.eof()) {
			arcs[h][t] = 1;
			arcs[t][h] = 1;
		}
		else {
			edgeWeighted = true;
			ss >> arcs[h][t];
			arcs[t][h] = arcs[h][t];
		}
		arcNum++;
	}
	if (arcNum >= vexNum) hasCircle = true;
}

void MGraph::PrintMatrix() {
	for (int i = 0; i < vexNum; i++) {
		for (int j = 0; j < vexNum; j++) {
			cout << arcs[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
// �������ͼ��ͨ
void MGraph::FindArticul() {
	// ȫ�ּ���
	int count = 1;
	// ������ʹ��������
	int* visited = new int[vexNum];
	if (visited == NULL) return;
	memset(visited, 0, sizeof(int) * vexNum);
	// ����low����
	int* low = new int[vexNum];
	if (low == NULL) return;
	memset(low, 0, sizeof(int) * vexNum);

	// ��һ�����vexs[0]�Ѿ�����
	visited[0] = 1;
	int v = -1;
	v++;
	while (v < vexNum && arcs[0][v] == 0) v++;
	DFSArticul(v, count, visited, low);
	if (count < vexNum) {
		// ˵����������������������������ʱ��vexs[0]�Ǹ
		Articul.push_back(0);
		// ����������������
		v++;
		while (v < vexNum && arcs[0][v] == 0) v++;
		DFSArticul(v, count, visited, low);
	}
	// �Ը��������
	sort(Articul.begin(), Articul.end(), less<int>());
}

void MGraph::DFSArticul(int v0, int& count, int* visited, int* low) {
	// ״̬��
	class State {
	public:
		int v;
		int w;
		int min;
		State(int v, int w, int min) : v(v), w(w), min(min) {};
	};

	stack<State*> DFSStack;
	int w = -1;
	DFSStack.push(new State(v0, w, count + 1));
	visited[v0] = ++count;

	State* s = DFSStack.top();
	while (!DFSStack.empty()) {
		s = DFSStack.top();
		// ����һ���ڶ����������ĺ��ӣ�
		s->w++;
		while (s->w < vexNum && arcs[s->v][s->w] == 0) s->w++;
		if (s->w >= vexNum) {
			// ��˵�����к��Ӷ����ʹ��ˣ�Ӧpop
			// popǰ���ú�low
			low[s->v] = s->min;
			DFSStack.pop();
			if (DFSStack.empty())
				return;
			delete s;
			// ��ǰ��Ľ������һЩ��������minֵ��ȷ�ϸ
			s = DFSStack.top();
			if (low[s->w] < s->min) s->min = low[s->w];
			if (low[s->w] >= visited[s->v]) {
				bool isIn = false;
				for (auto a : Articul) {
					if (a == s->v) {
						isIn = true;
						break;
					}
				}
				if (!isIn) Articul.push_back(s->v);
			}
			continue;
		}
		if (!visited[s->w]) {
			// ���û�����ʹ����������
			State* nexts = new State(s->w, -1, -1);
			visited[nexts->v] = nexts->min = ++count;
			DFSStack.push(nexts);
			continue;
		}
		else if (visited[s->w] < s->min) {
			// ���򣬳����޸�s->min�������Ҫ��
			s->min = visited[s->w];
		}
	}
}

void MGraph::FindMaxCircle() {
	for (int k = 0; k < vexNum; k++) {
		memset(visited, 0, sizeof(int) * vexNum);
		FindMaxCircleThrough(k, k, 0, new vector<int>);
	}
}

void MGraph::PrintMaxCircle()
{
	if (hasCircle) {
		cout << maxWeight << endl << maxCircle[0];
		int vsize = maxCircle.size();
		for (int i = 1; i < vsize; i++) {
			cout << "->" << maxCircle[i];
		}
		cout << "->" << maxCircle[0] << endl;
	}
	else {
		cout << "û��Ȧ" << endl;
	}
}

void MGraph::PrintArticul() {
	for (auto e : Articul) {
		cout << e << ' ';
	}
	cout << endl;
}

void MGraph::PrintGraphvizCode() {
	if (!edgeWeighted) {
		// �Ǵ�Ȩͼ
		cout << "graph g {" << endl;
		for (int i = 0; i < vexNum; i++) {
			for (int j = i; j < vexNum; j++) {
				if (arcs[i][j] != 0) {
					cout << "\t" << i << "--" << j << endl;
				}
			}
		}
		cout << "}" << endl;
	}
	else {
		// ��Ȩͼ
		cout << "graph g {" << endl;
		for (int i = 0; i < vexNum; i++) {
			int a1 = -1;
			int a2 = -1;
			for (int k = 0; k < maxCircle.size(); k++) {
				// ȷ��k�Ƿ������Ȧ·���ϵĶ�������ǣ���a1,a2��¼���ڶ���
				if (maxCircle[k] == i) {
					a1 = k == maxCircle.size() - 1 ? maxCircle[0] : maxCircle[k + 1];
					a2 = k == 0 ? maxCircle[maxCircle.size() - 1] : maxCircle[k - 1];
					break;
				}
			}
			for (int j = i; j < vexNum; j++) {
				if (arcs[i][j] != 0) {
					// ����ɫ���ǵ����
					cout << "\t" << i << "--" << j
						<< "[label = \"" << arcs[i][j] << "\""
						<< ", color = \"" << (j == a1 || j == a2 ? "red" : "black") << "\"]" << endl;
				}
			}
		}
		cout << "}" << endl;;
	}
}