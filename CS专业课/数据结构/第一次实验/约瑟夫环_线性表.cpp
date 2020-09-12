#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

// Լɪ����
class JosephNode {
public:
	int index; //������
	int code; // �������
	int nextCur; //��һ������λ��
	JosephNode(int index, int code, int nextCur) 
		: index(index), code(code), nextCur(nextCur) {};
};

// ���ַ���s�ж�ȡ������������dest��
bool tryReadNum(int* dest, char* s) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (!isdigit(s[i])) {
			cout << "���ַ�������\n";
			return false;
		}
	}
	sscanf(s, "%d", dest);
	return true;
}

// ��Լɪ������
void solve(int num, int m, JosephNode** list) {
	FILE* f = fopen("answer.txt", "w");
	int beforeCur = num - 1;
	int cur = 0;
	while (num--) {
		m--;
		// ѭ�����ˣ�ֱ���ﵽm
		while (m--) {
			beforeCur = cur;
			cur = list[cur]->nextCur;
		}
		cout << list[cur]->index << ' ';
		fprintf(f, "%d ", list[cur]->index);
		m = list[cur]->code;
		list[beforeCur]->nextCur = list[cur]->nextCur;
		cur = list[cur]->nextCur;
	}
	cout << endl;
	fprintf(f, "\n");
}

int main(int argc, char* argv[])
{
	int num, m, code;
	JosephNode** list = nullptr;
	bool flag = true;
	// �������в��������������࣬Ҫ������ĿҪ��������4������
	if (argc >= 4) {
		// ��ȡ����
		if (!tryReadNum(&num, argv[1])) {
			flag = false;
		}
		// �ж��������������Ƿ�һ��
		if (num != argc - 3 && flag) {
			cout << "����������������\n";
			flag = false;
		}
		// ��ȡ��ʼ����
		if (!tryReadNum(&m, argv[2]) && flag) {
			flag = false;
		}
		if (flag) {
			list = new JosephNode*[num];
			// ��ȡ��������
			for (int i = 0; i < num; i++) {
				if (!tryReadNum(&code, argv[i + 3])) {
					flag = false;
					break;
				}
				list[i] = new JosephNode(i + 1, code, i == num - 1 ? 0 : i + 1);
			}
			// ִ��
			solve(num, m, list);
			return 0;
		}
	}
	if (flag) {
		// ������������Ϣ������
		cout << "��������Ϣ�����������������룬�������¸�ʽ��\n"
			<< "������n������ʼ�ı�������m��������1�� ���� ������n��\n" << endl;
		// ���¶�ȡ�����ͳ�ʼ����
		cin >> num >> m;
		list = new JosephNode*[num];
		// ���¶�ȡ����
		for (int i = 0; i < num; i++) {
			cin >> code;
			list[i] = new JosephNode(i + 1, code, i == num - 1 ? 0 : i + 1);
		}
		// ִ��
		solve(num, m, list);
	}
}

