/*********************************************************************
Copyright: 2019-9999, Zhanghan Wang
File name: EXP0.cpp
Description:
����һ��С��Ӣ���ʵ䣬���Ĺ����У�
	��ȡ����ȡ�����ļ�����ʽΪ.dat)
	��ѯ����ѯ���д���
	��ӣ�����´���
	ɾ����ɾ������
	�༭���༭����
	�����������д���
Author:�����	PB18111697
Version:1.0.0
Date: 2019/5/14
*********************************************************************/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#pragma warning(disable:4996)

using namespace std;
const int MAX_WORD_LEN = 32;
const int MAX_EXPLAIN_LEN = 256;
const int MAX_SENTENCE_LEN = 256;
const int MAX_LINE_LEN = MAX_WORD_LEN + MAX_EXPLAIN_LEN + MAX_SENTENCE_LEN + 5;
const int ADD_SIZE = 1;

typedef struct entry {
	bool exist;		//�Ƿ�ɾ��
	long flocation;	//���ļ���λ��
	char* word;		//����
	char* explain;	//����
	char* sentence;	//����
} entry;

typedef struct entryArray {
	entry** enArray;		//��������
	entry* lastInFile;		//�ļ������һ������
	int startLetterIndex[26];//��¼��������ĸλ�õ�����
	int wordsNum;			//��ʾ�����ܴ�����
	int fwordsNum;			//��ʾ�ļ����ܴ�����������δɾ���ģ�
	int size;				//��ʾ��������enArray�Ĵ�С
} entryArray;

void listHelp();
void dealCommand(entryArray* entries, char* command);
void printEntry(entry* en);
void printAllEntries(entryArray* entries, int mode);
void entryInitiate(entry* en);
int entryCompare(const entry* en1, const entry* en2);
void sortEntryArray(entryArray* entries);
void readEntries(entryArray* entries);
entry* searchEntry(entryArray* entries, char* word);
void addEntry(entryArray* entries, entry* en);
void deleteEntry(entryArray* entries, char* word);
void editEntry(entryArray* entries, char* word, char* newData, int mode);
void clear(entryArray* entries);


int main() {
	char* command = (char*)calloc(MAX_LINE_LEN,sizeof(char));
	entryArray* entries = (entryArray*)malloc(sizeof(entryArray));
	readEntries(entries);
	listHelp();
	while (true) {
		fgets(command, MAX_LINE_LEN, stdin);
		dealCommand(entries, command);
	}
}

void listHelp() {
	printf("\
С��Ӣ���ʵ��������:\n\
help\t\t\t�г������б�\n\
consult word\t\t��ѯ����,(����Ҫ��ѯ�ĵ��ʴ���word)\n\
add word_ex_sen	\t��ӵ���,(word���������ʣ�ex�����ͣ�sen������)\n\
del word\t\tɾ������,(word����������)\n\
edit word_item_data\t�༭����,\n\
\t\t\t\t|word���������ʣ�\n\
\t\t\t\t|item������Ϊw(����),e(����),s(����)��\n\
\t\t\t\t|data���༭������\n\
clear\t\t\t����\t,����ɾ����Ǵ���\n\
cls\t\t\t����\n\
quit\t\t\t�˳�\t,�رճ���\n\
");
}

/*
 *�������� dealCommand
 *���ܣ������û������ִ�в���
 */ 
void dealCommand(entryArray* entries, char* command) {
	command[strlen(command) - 1] = '\0';
	//�������� help 
	if (strstr(command, "help") - command == 0) {
		listHelp();
	}
	//�������� consult 
	else if (strstr(command, "consult") - command == 0) {
		if (strlen(command) <= 8) {
			printf("��Ч���\n");
			return;
		}
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		double time;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);
		entry*en = searchEntry(entries, command + 8);
		QueryPerformanceCounter(&nEndTime);
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		if (en == (entry*)NULL) {
			printf("�Ҳ����õ��ʣ���ʱ%lf�룡\n", time);
		}
		else {
			printf("�Ѳ��ҵ����ʣ���ʱ%lf�룡\n", time);
			printEntry(en);
		}
	}
	//�������� add 
	else if (strstr(command, "add") - command == 0) {
		if (strlen(command) <= 4) {
			printf("��Ч���\n");
			return;
		}
		else if (command[3] != ' ') {
			printf("��Ч���\n");
			return;
		}
		entry* en = (entry*)malloc(sizeof(entry));
		entryInitiate(en);
		char* word = (char*)calloc(MAX_WORD_LEN, sizeof(char));
		char* explain = (char*)calloc(MAX_EXPLAIN_LEN, sizeof(char));
		char* sentence = (char*)calloc(MAX_SENTENCE_LEN, sizeof(char));
		memset(word, 0, sizeof(word));
		memset(explain, 0, sizeof(word));
		memset(sentence, 0, sizeof(word));
		word = strtok(command + 4, "_");
		if ((explain = strtok(NULL, "_")) == NULL || (sentence = strtok(NULL, "_")) == NULL) {
			printf("��Ч���\n");
		}
		else {
			strcpy(en->word, word);
			strcpy(en->explain, explain);
			strcpy(en->sentence, sentence);
			addEntry(entries, en);
		}
	}
	//�������� del 
	else if (strstr(command, "del") - command == 0) {
		if (strlen(command) <= 4 || command[3] != ' ') {
			printf("��Ч���\n");
			return;
		}

		deleteEntry(entries, command+4);
	}
	//�������� edit 
	else if (strstr(command, "edit") - command == 0) {
		char* word = (char*)calloc(MAX_WORD_LEN, sizeof(char));
		char* item = (char*)calloc(MAX_EXPLAIN_LEN, sizeof(char));
		char* data = (char*)calloc(MAX_EXPLAIN_LEN, sizeof(char));
		memset(word, 0, sizeof(word));
		memset(item, 0, sizeof(word));
		memset(data, 0, sizeof(word));
		word = strtok(command + 5, "_");
		if (command[4] != ' ') {
			printf("��Ч���\n");
		}
		else if ((item = strtok(NULL, "_")) == NULL || (data = strtok(NULL, "_")) == NULL) {
			printf("��Ч���\n");
		}
		else {
			if (item[0] == 'w') {
				editEntry(entries, word, data, 0);
			}
			else if (item[0] == 'e') {
				editEntry(entries, word, data, 1);
			}
			else if (item[0] == 's') {
				editEntry(entries, word, data, 2);
			}
			else {
				printf("��Ч���\n");
			}
		}
		return;
	}
	//�������� clear 
	else if (strcmp(command, "clear") == 0) {
		clear(entries);
	}
	//�������� all0 
	else if (strcmp(command, "all0") == 0) {
		printAllEntries(entries, 0);
	}
	//�������� all1 
	else if (strcmp(command, "all1") == 0) {
		printAllEntries(entries, 1);
	}
	//�������� wordsNum 
	else if (strcmp(command, "wordsNum") == 0) {
		printf("Ŀǰ��%d������\n", entries->wordsNum);
	}
	//�������� fwordsNum 
	else if (strcmp(command, "fwordsNum") == 0) {
		printf("Ŀǰ��%d������(f)\n", entries->fwordsNum);
	}
	//�������� cls 
	else if (strcmp(command, "cls") == 0) {
		system("cls");
		listHelp();
	}
	//�������� quit 
	else if (strcmp(command, "quit") == 0) {
		exit(0);
	}
	//������������ 
	else {
		printf("��Ч���\n");
		return;
	}

}


/*
 *�������� printEntry
 *���ܣ���ӡ����en���������� 
 */ 
void printEntry(entry* en) {
	printf("����:%s\n����:%s\n����:%s\n", en->word, en->explain, en->sentence);
}

/*
 *�������� printAllEntries
 *���ܣ���ӡ��������entries�����д���
 */ 
void printAllEntries(entryArray* entries, int mode) {
	printf("\n");
	if (mode == 0) {
		for (int i = 0; i < entries->fwordsNum; i++) {
			printEntry(entries->enArray[i]);
		}
	}
	else if (mode == 1) {
		for (int i = 0; i < entries->wordsNum; i++) {
			printEntry(entries->enArray[i]);
		}
	}
	printf("\n");
}

/*
 *�������� entryInitiate
 *���ܣ���ʼ������en 
 */ 
void entryInitiate(entry *en) {
	en->exist = true;
	en->flocation = 0;
	en->word = (char*)calloc(MAX_WORD_LEN, sizeof(char));
	en->explain = (char*)calloc(MAX_EXPLAIN_LEN, sizeof(char));
	en->sentence = (char*)calloc(MAX_SENTENCE_LEN, sizeof(char));
	strcpy(en->word, "NULL");
	strcpy(en->explain, "NULL");
	strcpy(en->sentence, "NULL");
}

/*
 *�������� freeEntry
 *���ܣ��ͷŴ���en�漰�������ڴ�ռ� 
 */ 
void freeEntry(entry* en) {
	if (en->word != (char*)NULL) { free(en->word); en->word = NULL; }
	if (en->explain != (char*)NULL) { free(en->explain); en->explain = NULL; }
	if (en->sentence != (char*)NULL) { free(en->sentence); en->sentence = NULL; }
	free(en);
}

/*
 *�������� entryCompare
 *���ܣ��Դ���en1��en2���бȽϣ��൱�ڽṹ��entry��һ��compare���� 
 */ 
int entryCompare(const entry* en1, const entry* en2) {
	if ((en1->exist && en2->exist) || (!en1->exist && !en2->exist)) {
		return strcmp(en1->word, en2->word);
	}
	else if (en1->exist && !en2->exist) {
		return -1;
	}
	else if (en2->exist && !en1->exist) {
		return 1;
	}
	else {
		return 0;
	}
}

/*
 *�������� sortEntryArray
 *���ܣ��Դ���entries�������� 
 */ 
void sortEntryArray(entryArray* entries) {
	int i, j;
	bool changed;
	entry* temp;
	for (i = entries->fwordsNum - 1; i >= 0; i--) {
		changed = false;
		for (j = 0; j < i; j++) {
			if (entryCompare(entries->enArray[j], entries->enArray[j + 1]) > 0) {
				changed = true;
				temp = entries->enArray[j];
				entries->enArray[j] = entries->enArray[j + 1];
				entries->enArray[j + 1] = temp;
			}
		}
		if (!changed) {
			break;
		}
	}
}


/*
 *�������� readEntries
 *���ܣ����ļ��ж�ȡ������Ϣ�����浽��������entries�� 
 */ 
void readEntries(entryArray* entries) {
	FILE* dict = fopen("dict.dat", "r");
	fscanf(dict, "%d\n", &entries->fwordsNum);
	entries->enArray = (entry**)calloc(entries->fwordsNum + ADD_SIZE, sizeof(entry*)); //��ʼ������ADD_SIZE���ռ䣬�Ա����ʱʹ��
	entries->size = entries->fwordsNum + ADD_SIZE; entries->wordsNum = 0;
	memset(entries->startLetterIndex, 0, sizeof(entries->startLetterIndex));
	entry** cur = entries->enArray;
	char exist;
	long tempLocation;
	char* curLine;
	int curLetter = 0;
	while (!feof(dict)) {
		curLine = (char*)calloc(MAX_LINE_LEN, sizeof(char));
		tempLocation = ftell(dict);
 		fgets(curLine, MAX_LINE_LEN, dict);
		if (curLine[0] == '\0') {
			break;
		}
		*cur = (entry*)malloc(sizeof(entry));
		entryInitiate(*cur);
		exist = *strtok(curLine, "_");
		(*cur)->flocation = tempLocation;
		strcpy((*cur)->word, strtok(NULL, "_"));
		strcpy((*cur)->explain, strtok(NULL, "_"));
		strcpy((*cur)->sentence, strtok(NULL, "_"));
		(*cur)->sentence[strlen((*cur)->sentence)-1] = '\0';
		//�ж��Ƿ��Ǿɴ������������ 
		if (exist == '#') {
			(*cur)->exist = false;
		}
		else {
			(*cur)->exist = true;
			entries->startLetterIndex[(*cur)->word[0] - 'a']++;
			entries->wordsNum++;
		}
		cur++;
	}

	for (int i = 1; i < 26; i++) {
		entries->startLetterIndex[i] += entries->startLetterIndex[i - 1];
	}
	fclose(dict);
	entries->lastInFile = entries->enArray[entries->fwordsNum-1];
	sortEntryArray(entries);
}

/*
 *�������� searchEntry
 *���ܣ��ڴ�������entries�в��ҵ���word 
 */ 
entry* searchEntry(entryArray* entries, char* word) {
	entry* en = (entry*)malloc(sizeof(entry));
	int comp;
	entryInitiate(en);
	strcpy(en->word, word);
	int start = 0, end = 0, middle = 0;
	end = entries->wordsNum - 1;
	//ͨ��������ȡ��ʼλ�� 
	if ((word[0] > 'a'&& word[0] <= 'z')) {
		start = entries->startLetterIndex[word[0]-'a'-1];
	}
	else if (word[0] == 'a') {
		start = 0;
	}
	end = entries->startLetterIndex[word[0]-'a'] - 1;
	//���ֲ��� 
	while (true) {
		middle = (start + end) / 2;
		comp = entryCompare(entries->enArray[middle], en);
		if (comp > 0) {
			if (start >= end) {
				freeEntry(en);
				return (entry*)NULL;
			}
			end = middle - 1;
		}
		else if (comp < 0) {
			if (start >= end) {
				freeEntry(en);
				return (entry*)NULL;
			}
			start = middle + 1;
		}
		else if (comp == 0) {
			freeEntry(en);
			return entries->enArray[middle];
		}
	}
	freeEntry(en);
}

/*
 *�������� addEntry
 *���ܣ��ڴ�������entriesĩβ��Ӵ���en 
 */ 
void addEntry(entryArray* entries, entry* en) {
	entry* temp;
	if (en == NULL) {
		printf("���Ĵ���ʧ��\n");
		return;
	}
	else if ((temp = searchEntry(entries, en->word)) != (entry*)NULL) {
		printf("�ô����Ѵ���,��������:\n");
		printEntry(temp);
		printf("��������Ҫ�༭����������help�鿴����.\n");
	}
	else {
		if (entries->size <= entries->fwordsNum) {
			entries->enArray = (entry**)realloc(entries->enArray, (entries->size + ADD_SIZE)*sizeof(entry*));
			entries->size += ADD_SIZE;
		}
		temp = entries->lastInFile;
		en->flocation = temp->flocation + strlen(temp->word) + strlen(temp->explain) + strlen(temp->sentence) + 6;
		entries->enArray[entries->fwordsNum] = en;
		entries->wordsNum++; entries->fwordsNum++;

		FILE* dict = fopen("dict.dat", "a+"); 
		fprintf(dict, "*_%s_%s_%s\n", en->word, en->explain, en->sentence);
		fclose(dict);
		dict = fopen("dict.dat", "r+");
		fprintf(dict, "%06d\n", entries->fwordsNum);
		fclose(dict);
		entries->lastInFile = en;
		for (int i = en->word[0] - 'a'; i < 26; i++) {
			entries->startLetterIndex[i]++;
		}
		sortEntryArray(entries);
		printf("���Ĵ����ɹ�\n");
	}
}

/*
 *�������� deleteEntry
 *���ܣ��ڴ�������entries��ɾ������Ϊword�Ĵ��� 
 */ 
void deleteEntry(entryArray* entries, char* word) {
	entry* toDelete = searchEntry(entries, word);
	if (toDelete == (entry*)NULL) {
		printf("ɾ������\"%s\"ʧ�ܣ�δ�ҵ��ô���\n", word);
	}
	else {
		toDelete->exist = false;
		sortEntryArray(entries);
		entries->wordsNum--;

		FILE* dict = fopen("dict.dat", "r+");
		fseek(dict, toDelete->flocation, SEEK_CUR);
		fprintf(dict, "%c", '#');
		fclose(dict);
		for (int i = word[0] - 'a'; i < 26; i++) {
			entries->startLetterIndex[i]--;
		}
		printf("ɾ������%s�ɹ���\n", word);
		sortEntryArray(entries);
	}

}

/*
 *�������� editEntry
 *���ܣ��༭entries�е���Ϊword�Ĵ�����newDataΪ�����ݣ�����mode�����޸�������һ� 
 */ 
void editEntry(entryArray* entries, char* word, char* newData, int mode) {
	entry* oldEntry = searchEntry(entries, word);
	if (oldEntry == (entry*)NULL) {
		printf("�Ҳ����ô���\n");
	}
	else if (mode == 0 && strcmp(word, newData) == 0) {
		printf("����");
		fputs(newData, stdout);
		printf("�Ѵ��ڣ��޸�ʧ�ܡ�");
	}
	else {
		entry* newEntry = (entry*)malloc(sizeof(entry));
		entryInitiate(newEntry);
		newEntry->exist = true;
		newEntry->flocation = oldEntry->flocation;
		strcpy(newEntry->word, oldEntry->word);
		strcpy(newEntry->explain, oldEntry->explain);
		strcpy(newEntry->sentence, oldEntry->sentence);
		if (mode == 0) {
			strcpy(newEntry->word, newData);
		}
		if (mode == 1) {
			strcpy(newEntry->explain, newData);
		}
		else if (mode == 2) {
			strcpy(newEntry->sentence, newData);
		}
		oldEntry->exist = false;
		entries->wordsNum--;
		FILE* dict = fopen("dict.dat", "r+");
		fseek(dict, oldEntry->flocation, SEEK_CUR);
		fprintf(dict, "%c", '#');
		fclose(dict);
		for (int i = word[0] - 'a'; i < 26; i++) {
			entries->startLetterIndex[i]--;
		}
		addEntry(entries, newEntry);
		sortEntryArray(entries);
	}
}

/*
 *�������� clear
 *���ܣ��Դ�������entries������ͬʱ�����ļ��� 
 */ 
void clear(entryArray* entries) {
	sortEntryArray(entries);
	FILE* dict = fopen("dict.dat", "w");
	fprintf(dict, "%06d\n", entries->wordsNum);
	entry* en;
	for (int i = 0; i < entries->wordsNum; i++) {
		en = entries->enArray[i];
		if (en->exist) {
			fprintf(dict, "%c", '*');
		}
		else {
			fprintf(dict, "%c", '#');
		}
		fprintf(dict, "_%s_%s_%s\n", en->word, en->explain, en->sentence);
	}
	for (int i = entries->wordsNum; i < entries->fwordsNum; i++) {
		freeEntry(entries->enArray[i]);
	}
	entries->fwordsNum = entries->wordsNum;
	entries->lastInFile = entries->enArray[entries->wordsNum - 1];
	fclose(dict);
	printf("�������\n");
}
