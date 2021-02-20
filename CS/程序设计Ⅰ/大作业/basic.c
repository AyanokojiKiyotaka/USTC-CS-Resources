#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define N 20
#define IDLen 4
#define SUBNUM 3

struct Student{
	char ID[N];
	char name[N];
	float grade[SUBNUM+3];
	struct Student *next;
};
typedef struct Student Student;

struct LinkList{
	Student *head;
	int num;
};
typedef struct LinkList LinkList;


LinkList *newLinkList();
Student *newStu();
void printStu(Student *stu);
void printLinkList(LinkList *linklist);
void calculate(Student *stu);
void swap(LinkList *linklist, int index1, int index2);
int strToInt(char str[N]);
float strToPFloat(char str[N]);


/****************************************************************************************
Function: newLinkList
Description: �½�һ��LinkList��������ָ�룬���½�ʧ���򷵻�NULL
Return:	�ú��������½��������ָ�룬���½�ʧ���򷵻�NULL 
****************************************************************************************/
LinkList *newLinkList()
{
	LinkList *linklist = (LinkList*)malloc(sizeof(LinkList));
	if(linklist == 0)
	{
		printf("�ڴ�ռ䲻��,�޷���������");
		return NULL;
	}
	linklist->head = (Student*)malloc(sizeof(Student));
	linklist->head->next = NULL;
	linklist->num = 0;
	return linklist;
}

/****************************************************************************************
Function: newStu
Description: �½�һ��ѧ����������ָ�룬���½�ʧ���򷵻�NULL�� 
Return:	�ú������ظ�ѧ����ָ�룬���½�ʧ���򷵻�NULL
****************************************************************************************/
Student *newStu()
{
	int i;
	int flag = 1;
	Student *stu = NULL;
	stu = (Student*)malloc(sizeof(Student));
	stu->next = NULL;
	if(stu == 0)
	{
		printf("�ڴ�ռ䲻��,�޷�����ѧ��");
		return NULL;
	}
	else
	{
		char subject[SUBNUM][N] = {"����", "��ѧ", "Ӣ��"}; 
		char grade[SUBNUM][N] = {0};
		stu->next = NULL;
		printf("��ֱ�����Ҫ�������ѧ����ID ���� ���ĳɼ� ��ѧ�ɼ� Ӣ��ɼ�(�Կո����)��\n");
		scanf("%s\t%s\t%s\t%s\t%s", stu->ID, stu->name, grade[0], grade[1], grade[2]);//����Ҫ��IDΪ4λ�����֣�name��ӦΪ������,����gradeӦΪ�Ǹ��� 
		while(strlen(stu->ID) != 4)
		{
			printf("����ѧ��ID�Ƿ���ӦΪ%dλ.����������ID��", IDLen);
			scanf("%s", stu->ID);
		}//���ID��ʽ�Ϸ��Խ��� 
		
		do
		{
			for(i = 0; i < strlen(stu->name); i++)
			{
				if((stu->name)[i] > '9' || (stu->name)[i] < '0')
				{
					flag = 0;
				}
				if(flag == 0) break;
			}
			if(flag == 1)
			{
				printf("����ѧ�������Ƿ�����ӦΪ������.����������������");
				scanf("%d", stu->name); 
			}
		}while(flag == 1);//���������ʽ�Ϸ��Խ��� 
		for(i = 0; i < SUBNUM; i++)
		{
			while(strToPFloat(grade[i]) == -1)
			{
				printf("��⵽��ѧ�� %s �ĳɼ��Ƿ���ӦΪ�Ǹ���. ����������: ", subject[i]);
				scanf("%s", grade[i]);
			}
		}//���ɼ���ʽ�Ϸ��Խ��� 
		
		for(i = 0; i < SUBNUM; i++)
		{
			stu->grade[i+3] = strToPFloat(grade[i]);
		}
		calculate(stu); 
		return stu;
	}
}

/****************************************************************************************
Function: printLinkList
Description: ��ӡ���������нڵ����Ϣ 
Input:	linklist: ����ӡ������
Return:	��ӡ���������нڵ����Ϣ 
****************************************************************************************/
void printLinkList(LinkList *linklist)
{
	if(linklist->head->next == NULL)
	{
		printf("������û�нڵ�");
		return;
	}
	int i;
	Student *stu = linklist->head;
	printf("���\tID\t\t\t����\t����\t��ѧ\tӢ��\tƽ����\t��߷�\t��ͷ�\n"); //�����ͷ
	for(i = 0; i < linklist->num; i++)
	{
		stu = stu->next;
		printf("%d\t",i+1);
		printStu(stu);
	}
} 

/****************************************************************************************
Function: printStu
Description: ��ӡstu����Ϣ 
Input:	stu: ����ӡ��Ϣ��ѧ�� 
Return:	��ӡstu����Ϣ 
****************************************************************************************/
void printStu(Student *stu)
{
	printf("%4s\t%20s\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n", 
		stu->ID, stu->name, stu->grade[3], stu->grade[4], stu->grade[5], stu->grade[0], stu->grade[1], stu->grade[2]);
} 


/****************************************************************************************
Function: void calculate(Student *stu)
Description: ��ѧ��stu��ƽ������ߣ���ͷ� 
Input:	stu: ��Ҫ��ƽ������ߣ���ͷֵ�ѧ�� 
Return:	�� 
****************************************************************************************/
void calculate(Student *stu)
{
	int i;
	float max, min;
	if(stu != NULL)
	{
		stu->grade[0] = (stu->grade[3] + stu->grade[4] + stu->grade[5]) /3;
		max = stu->grade[3];
		min = stu->grade[3];
		for(i = 3; i < SUBNUM+3; i++)
		{
			if(stu->grade[i] > max) max = stu->grade[i];
			if(stu->grade[i] < min) min = stu->grade[i];
		}
		stu->grade[1] = max;
		stu->grade[2] = min;
	}
} 



/****************************************************************************************
Function: int strToInt(char str[N])
Description: ��str�ɱ�ʾ�Ǹ��������򷵻ظ����������򷵻�-1 
Input:	str: ��Ҫת�����ַ��� 
Return:	��str�ɱ�ʾ�Ǹ��������򷵻ظ����������򷵻�-1 
****************************************************************************************/
int strToInt(char str[N]) 
{
	int i, result = 0,flag = 1;
	for(i = 0; i < strlen(str); i++)
	{
		if(str[i] > '9' || str[i] < '0')
		{
			flag = 0;
		}
		if(flag == 0) break;
	}
	if(flag == 1)
	{
		for(i = strlen(str) - 1; i >= 0; i--)
		{
			result += (str[i]-48)*pow(10, strlen(str) - i - 1);	
		}
		return result;
	}
	else if(flag == 0)
	{
		return -1;
	}
}

/****************************************************************************************
Function: float strToPFloat(char str[N])
Description: ��str�ɱ�ʾ�Ǹ����������򷵻ظø�����(��float����)�����򷵻�-1 
Input:	str: ��Ҫת�����ַ��� 
Return:	��str�ɱ�ʾ�Ǹ����������򷵻ظø�����(��float����)�����򷵻�-1 
****************************************************************************************/
float strToPFloat(char str[N])
{
	float result = 0;
	int i, flag = 1, point = strlen(str);
	for(i = 0; i < strlen(str); i++)
	{
		if((str[i] > '9' || str[i] < '0') )
		{
			if(str[i] == 46)
			{
				point = i;
			}
			else
			{
				flag = 0;
			}
		}
		if(flag == 0) break;
	}
	if(flag == 1)
	{
		for(i = point - 1; i >= 0; i--)
		{
			result += (str[i]-48)*pow(10, point - i - 1);	
		}
		for(i = point + 1; i < strlen(str); i++)
		{
			result += (str[i]-48)*pow(10, -(i-point));	
		}
		return result;
	}
	else if(flag == 0)
	{
		return -1;
	}
}







