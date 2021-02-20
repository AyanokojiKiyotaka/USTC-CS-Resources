#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

// Լɪ��ѭ��������
class JosephNode {
public:
	int index; // ������
	int code; //�������
	JosephNode* next; // ��һ�����

	JosephNode(int index, int code) : index(index), code(code), next(nullptr) {};
};

// Լɪ��ѭ������
class JosephRing {
public:
	int num; // �ܽ����
	int sup; //��������
	JosephNode* cur; //��ǰָ����
	JosephNode* beforeCur; //��ǰָ�����ǰһ�����
	JosephRing(int num, int sup, int* codes) : num(num), sup(sup){
		cur = new JosephNode(1, codes[0]);
		JosephNode* p = cur;
		for (int i = 1; i < num; i++) {
			p->next = new JosephNode(i + 1, codes[i]);
			p = p->next;
		}
		beforeCur = p;
		p->next = cur;
	}

	// ������
	void printAnswer() {
		FILE* f = fopen("answer.txt", "w");
		while (num--) {
			sup--;
			//��������ȥ��ֱ������������
			while (sup--) {
				beforeCur = cur;
				cur = cur->next;
			}
			cout << cur->index << ' ';
			fprintf(f, "%d ", cur->index);
			sup = cur->code;
			beforeCur->next = cur->next;
			JosephNode* toDelete = cur;
			cur = cur->next;
			delete toDelete; //ɾ��ȥ���˵Ľڵ�ռ�õ��ڴ�ռ�
		}
		cout << endl;
		fprintf(f, "\n");
	}
};

//���ַ����ж�ȡһ��������
bool tryReadNum(int* dest, char* s) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (!isdigit(s[i])) {
			cout << "���ַ�������\n";
			return false;
		}
	}
	sscanf(s, "%d", dest);
}

int main(int argc, char* argv[])
{
	bool flag = true;
	// �������в��������������࣬Ҫ������ĿҪ��������4������
	if (argc >= 4) {
		int* codes = new int[argc - 1];
		// �������в���ת��Ϊint�������ݴ洢��code��
		for (int i = 1; i < argc; i++) {
			if (!tryReadNum(codes + i - 1, argv[i])) {
				flag = false;
				break;
			}
		}
		// �ж��������������Ƿ��Ӧ
		if (codes[0] != argc - 3 && flag) {
			cout << "����������������\n";
			flag = false;
		}
		if (flag) {
			// ʵ����JosephRing,������printAnswer()�����������Ŀ
			JosephRing* jr = new JosephRing(codes[0], codes[1], codes + 2);
			jr->printAnswer();
		}
	}
	if(!flag) {
		// �����в�����ʽ����ȷ��Ҫ���������롣
		int num, m;
		cout << "��������Ϣ�����������������룬�������¸�ʽ��\n"
			<< "������n������ʼ�ı�������m��������1�� ���� ������n��\n" << endl;
		cin >> num >> m;
		int* codes = new int[num]; 
		for (int i = 0; i < num; i++) {
			cin >> codes[i];
		}
		// ʵ����JosephRing,������printAnswer()�����������Ŀ
		JosephRing* jr = new JosephRing(num, m, codes);
		jr->printAnswer();
	}
}
