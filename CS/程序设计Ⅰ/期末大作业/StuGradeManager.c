/*********************************************************************
Copyright: 2018-9999, Zhanghan Wang
File name: StuGradeManager.c
Description: 
����һ��ѧ���ɼ�����ϵͳ�����ܹ�ʵ��
	��ȡ����ȡ��ʷ�ɼ��ļ�����ʽΪ.txt)
	���룺�����¼�¼ 
	ɾ����ɾ����¼ 
	���ң�(1)����ID����������һ��ѧ���ļ�¼(2)����ƽ����>60��ѧ�� 
	�޸ģ��޸�ĳ��ѧ���ĳɼ� 
	���򣺰���ĳ��ѧ�����Զ�ѧ���������� 
	���棺����ID��ѧ�����򣬲�����ɼ���Ϊtxt�ļ� 
Author:�����	PB18111697
Version:1.0.0
Date: 2018/12/5
*********************************************************************/
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
	float grade[SUBNUM+3]; //Ϊ����߿���չ�ԣ�������������������������¼���Ƴɼ���������ƽ����
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
void findPasser(LinkList *linklist);
void findStu(LinkList *linklist);
Student *nameGet(LinkList *linklist, char name[N]);
Student *IDGet(LinkList *linklist, char ID[N]);
Student *getStu(LinkList *linklist, int index);
void addToLinkList(LinkList *linklist, Student *stu, int index);
void editGrade();
void deleteStu(LinkList *linklist, int index, int mode);
void sortStu(LinkList *linklist);
void strSort(LinkList *linklist, int item);
void gradeSort(LinkList *linklist, int item);
void swapStu(LinkList *linklist, int index1, int index2);
LinkList *getStuInfor();
Student *readStu(FILE *in);
void writeStu(LinkList *linklist);
void printMenu();
void exitSystem(LinkList *linklist);

int main()
{	
	char choice[N];
	LinkList *linklist = newLinkList();
	while(1)
	{
		printMenu();
		scanf("%s", choice);
		switch(strToInt(choice))
		{
			case 1: linklist = getStuInfor(); break;
			case 2: addToLinkList(linklist, newStu(), -1); break;
			case 3: deleteStu(linklist, 0, 1); break;
			case 4: findStu(linklist); break;
			case 5: editGrade(linklist); break;
			case 6: sortStu(linklist); break;
			case 7: writeStu(linklist); break;
			case 8: printLinkList(linklist); break;
			case 9: system("cls"); break;
			case 10: exitSystem(linklist); break;
			default: printf("û�����ѡ����!"); break;
			
		}
	}
//	writeStu(linklist);
	//LinkList *linklist = getStuInfor();
	//printLinkList(linklist);
	return 0;
}

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
	int flag = 1; //�����������Ϸ�����Ҫ��flag����� 
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

/****************************************************************************************
Function: Student *getStu(LinkList *linklist, int index)
Description: ��linklist�л�õ�index���ڵ��ϵ�Student�����������ַ 
Input:	linklist: ��Ҫ���ҵ�����
		index����Ҫ��ȡ��ѧ�����ڽڵ������� 
Return:	linklist�ϵ�index���ڵ��ϵ�Student�ĵ�ַ 
****************************************************************************************/
Student *getStu(LinkList *linklist, int index)
{
	int i;
	Student *stu = NULL;
	stu = (Student*)malloc(sizeof(Student));
	stu = linklist->head->next;
	if(index == 0) return linklist->head;
	for(i = 1; i < index; i++)
	{
		stu = stu->next;
	}
	return stu;
}

/****************************************************************************************
Function: Student *IDGet(LinkList *linklist, char ID[N])
Description: ��linklist�л��IDΪID��Student�����������ַ 
Input:	linklist: ��Ҫ���ҵ�����
		ID����Ҫ��ȡ��ѧ����ID 
Return:	linklist��IDΪID��Student�ĵ�ַ 
****************************************************************************************/
Student *IDGet(LinkList *linklist, char ID[N])
{
	int flag = 0;  
	Student *stu = linklist->head->next;
	while(stu != NULL)
	{
		if(strcmp(stu->ID, ID) == 0)
		{
			flag = 1;
			break;
		}
		if(flag == 1) break;
		stu = stu->next;
	}
	if(stu == NULL)
	{
		printf("\n�Ҳ�����ѧ��\n");
		return NULL;
	}
	else
	{
		return stu;
	}
}

/****************************************************************************************
Function: Student *nameGet(LinkList *linklist, char name[N])
Description: ��linklist�л��nameΪname��Student�����������ַ 
Input:	linklist: ��Ҫ���ҵ�����
		name����Ҫ��ȡ��ѧ����name 
Return:	linklist��nameΪname��Student�ĵ�ַ 
****************************************************************************************/
Student *nameGet(LinkList *linklist, char name[N])
{
	int flag = 0;
	Student *stu = linklist->head->next;
	while(stu != NULL)
	{
		if(strcmp(stu->name, name) == 0) 
		{
			flag = 1;
			break;
		}
		if(flag == 1) break;
		stu = stu->next;
	}
	if(stu == NULL)
	{
		printf("\n�Ҳ�����ѧ��\n");
	}
	else
	{
		return stu;
	}
}

/****************************************************************************************
Function: void findStu(LinkList *linklist)
Description: ���û��ṩѡ����ʵ��1.����ID����������һ��ѧ����¼��2.����ƽ����>60��ѧ����
���������� 
Input:	linklist: ��Ҫ���ҵ�����
****************************************************************************************/
void findStu(LinkList *linklist)
{
	if(linklist->head->next == NULL)
	{
		printf("������û�нڵ�");
		return;
	}
	int choice;
	char temp[N];
	printf("��Ҫ�ĸ��أ��������\n\t1.����ID������������һ��ѧ���ļ�¼\n\t2.����ƽ���֣�60��ѧ��\n\t3.ȡ��\n");
	scanf("%s", temp);
	choice = strToInt(temp);
	while(choice != 1 && choice != 2 && choice !=3)
	{
		printf("��������������������룺");
		scanf("%s", temp);
		choice = strToInt(temp);
	}
	if(choice == 1)
	{
		char infor[N];
		int flag = 1; //���infor���������Ϊ1������Ϊ0��1Ϊ��ֵ
		int i;
		printf("������ҪѰ�ҵ�ѧ���� ID �� ����: \n");
		scanf("%s", infor);
		for(i = 0; i < strlen(infor); i++)
		{
			if(infor[i] > '9' || infor[i] < '0')
			{
				flag = 0;
			}
			if(flag == 0) break;
		}
		if(flag == 1)
		{
			if(IDGet(linklist, infor) != NULL)
			{
				printf("\n����ѧ����Ϣ���£�\n");
				printStu(IDGet(linklist, infor));
			}
		}
		else if(flag == 0)
		{
			if(nameGet(linklist, infor) != NULL)
			{
				printf("\n����ѧ����Ϣ���£�\n");
				printStu(nameGet(linklist, infor));
			}
		}
		else
		{
			printf("��������");
		}
	}
	else if(choice == 2)
	{
		findPasser(linklist);
	}
	else if(choice == 3)
	{
		return;
	}
	
}

/****************************************************************************************
Function: void findPasser(LinkList *linklist)
Description: ����linklist��average����60��Student�������
Input:	linklist: Ҫ�ҵ�����
****************************************************************************************/
void findPasser(LinkList *linklist)
{
	Student *stu = linklist->head->next;
	int flag = 0, i;
	printf("\n������ƽ����>60��ѧ��:\n");
	printf("���\tID\t\t\t����\t����\t��ѧ\tӢ��\tƽ����\t��߷�\t��ͷ�\n"); //�����ͷ
	for(i = 0; i < linklist->num; i++)
	{
		if(stu->grade[0] > 60) 
		{
			printf("%d\t", i+1);
			printStu(stu);
			flag = 1;
		}
		stu = stu->next;
	}
	if(flag == 0)
	{
		printf("\n��ѽ��û��ƽ����>60��ѧ��\n");
	}
} 

/****************************************************************************************
Function: addtoLinkList
Description: ��ѧ��stu���뵽����linklist��ָ��λ�� 
Input:	linklist: �����ѧ��������
		stu: �������ѧ��
		index: ��index = -1 ��ʾѯ���û����뵽�ģ���0 <= index && index <= linklist->num��ʱ����ֱ�Ӳ����index���ڵ�֮��
Return:	�� 
****************************************************************************************/
void addToLinkList(LinkList *linklist, Student *stu, int index) 
{
	if(linklist->head->next == NULL)
	{
		linklist->head->next = stu;
		stu->next = NULL;
		linklist->num++;
	}
	else
	{
		if(index >= 0 && index <= linklist->num)
		{
			Student *tstu = (Student*)malloc(sizeof(Student));
			if(index > 0 && index <= linklist->num)
			{
				tstu = (getStu(linklist, index))->next;
				(getStu(linklist, index))->next = stu;
				stu->next = tstu;
			}
			else if(index == 0)
			{
				stu->next = linklist->head->next;
				linklist->head->next = stu;
			}
			linklist->num++;
		}
		else if(index == -1)
		{
			char temp[N];
			printLinkList(linklist);
			printf("�ڵڼ�λ�ĺ��������(0��ʾ���뵽��λ��)��");
			scanf("%s", temp);
			index = strToInt(temp);
			while(index < 0 || index > linklist->num)
			{
				printf("λ�������д���.����������: ");
				scanf("%s", temp);
				index = strToInt(temp);
			} 
			Student *tstu = (Student*)malloc(sizeof(Student));
			if(index > 0 && index <= linklist->num)
			{
				tstu = (getStu(linklist, index))->next;
				(getStu(linklist, index))->next = stu;
				stu->next = tstu;
			}
			else if(index == 0)
			{
				stu->next = linklist->head->next;
				linklist->head->next = stu;
			}
			linklist->num++;
			printf("\n�������ǽ��ϣ�\n");
			printLinkList(linklist);
		}
	}
}

/****************************************************************************************
Function: void deleteStu(LinkList *linklist, int index, int mode) 
Description: ��linklist�е�index���ڵ���������Ƴ��� 
Input:	linklist: �����ѧ��������
		mode����modeΪ1���Ż��ͷŵ�index���ڵ���ڴ� 
Return:	�� 
****************************************************************************************/
void deleteStu(LinkList *linklist, int index, int mode) 
{
	if(linklist->head->next == NULL)
	{
		printf("������û�нڵ�");
		return;
	}
	if(index > 0 && index <= linklist->num)
	{
		Student *stu1 = getStu(linklist, index-1);
		Student *stu2 = getStu(linklist, index);
		stu1->next = stu2->next;
		if(mode == 1) free(stu2); 
		linklist->num--;
	}
	else
	{
		printLinkList(linklist);
		printf("Ҫɾ���ļ�¼�����ʲô�أ�(����0ȡ��ɾ����)\n");
		scanf("%d", &index);
		while(index < 0 && index > linklist->num)
		{
			printf("��Ų��ڷ�Χ����.����������(���Ҫȡ��ɾ��,����0)��");
			scanf("%d", &index); 
		}
		if(index == 0)
		{
			return;
		} 
		Student *stu1 = getStu(linklist, index-1);
		Student *stu2 = getStu(linklist, index);
		stu1->next = stu2->next;free(stu2);
		linklist->num--;
		printf("ɾ���ɹ�,ɾ���������£�\n");
		printLinkList(linklist);
	}
}

/****************************************************************************************
Function: void editGrade(LinkList *linklist)
Description: �޸�ĳ��ѧ���ĳɼ� 
Input:	linklist: ��ѧ����������
Return:	�� 
****************************************************************************************/
void editGrade(LinkList *linklist)
{
	if(linklist->head->next == NULL)
	{
		printf("������û�нڵ�");
		return;
	}
	int sub = 0;
	float grade;
	Student *stu = (Student*)malloc(sizeof(Student));
	char infor[N];
	char temp[N];
	int index;
	printLinkList(linklist);
	printf("������Ҫ�޸ĵ�ѧ�������(����0ȡ���޸�): ");
	scanf("%s", temp);
	index = strToInt(temp);
	while(index < 1 || index > linklist->num)
	{
		printf("�����������.���������룺");
		scanf("%s", temp);
		index = strToInt(temp);
	}
	if(index == 0)
	{
		return;
	}
	stu = getStu(linklist, index);
	if(stu != NULL)
	{
		printf("������Ҫ�޸ĵĿ�Ŀ�������:\n\t1.����\n\t2.��ѧ\n\t3.Ӣ��\n");
		scanf("%s", temp);
		sub = strToInt(temp);
		while(sub < 1 || sub > SUBNUM)
		{
			printf("��Ŀ��������,����������:");
			scanf("%s", temp);
			sub = strToInt(temp);
		} 
		printf("�������޸ĺ�ĳɼ�ӦΪ: ");
		scanf("%s", temp);
		grade = strToPFloat(temp);
		while(grade == -1)
		{
			printf("�ɼ�����Ƿ���ӦΪ�Ǹ���.�����������޸ĺ�ĳɼ�: ");
			scanf("%s", temp);
			grade = strToPFloat(temp);
		}
		if(sub == 1 || sub == 2 || sub == 3)
		{
			switch(sub)
			{
				case 1: stu->grade[3] = grade; break;
				case 2: stu->grade[4] = grade; break;
				case 3: stu->grade[5] = grade; break;
			}
			calculate(stu);
			printf("\n�޸Ľ����\n");
			printStu(stu);
		}
		else
		{
			printf("\n��Ŀѡ�����\n"); 
		}
	}
	else
	{
		printf("\n�����������\n");
	}
}

/****************************************************************************************
Function: void sortStu(LinkList *linklist)
Description: �����û�ѡ����������ݶ�linklist�ĸ����ڵ��������Ȼ�����������ÿ���ڵ� 
Input:	linklist: ����������� 
Return:	�� 
****************************************************************************************/
void sortStu(LinkList *linklist)
{
	if(linklist->head->next == NULL)
	{
		printf("������û�нڵ�");
		return;
	}
	int choice;
	char temp[N]; 
	printf("\n������������ݵ����:\n\t1.ID\n\t2.����\n\t3.ƽ����\n\t4.��߷�\n\t5.��ͷ�\n\t6.����\n\t7.��ѧ\n\t8.Ӣ��\n\t9.ȡ������\n");
	while(1)
	{
		scanf("%s", temp);
		choice = strToInt(temp);
		switch(choice)
		{
			case 1: 
			case 2: strSort(linklist, choice); break;
			case 3: 
			case 4: 
			case 5:
			case 6:
			case 7: 
			case 8: gradeSort(linklist, choice); break;
			case 9: return; break;
			default: printf("������������������:"); break;
		}
		if(choice >=1 && choice <= 8) break;
		else if(choice == 9) return;
	}
	printLinkList(linklist);
}

/****************************************************************************************
Function: void sortStu(LinkList *linklist)
Description: ʵ��������itemΪ1���������������ID����itemΪ2������������������� 
Input:	linklist: ����������� 
		item���ú�����Ҫ����item��ֵ������ͬ���Զ�linklist���� 
Return:	�� 
****************************************************************************************/
void strSort(LinkList *linklist, int item)
{
	int i, j;
	int max_index;
	char max[N];
	Student *stu1 = linklist->head;
	Student *stu2 = NULL;
	if(item == 1)
	{
		for(i = 1; i < linklist->num; i++)
		{
			stu1 = getStu(linklist, i);
			max_index = i;
			stu2 = stu1;
			strcpy(max, stu1->ID);
			for(j = i+1; j <= linklist->num; j++)
			{
				stu2 = stu2->next;
				if(strcmp(stu2->ID, max) < 0)
				{
					strcpy(max, stu2->ID);
					max_index = j;
				}
			}
			if(max_index != i) swapStu(linklist, i, max_index);
		}
	}
	else if(item == 2)
	{
		for(i = 1; i < linklist->num; i++)
		{
			stu1 = getStu(linklist, i);
			max_index = i;
			stu2 = stu1;
			strcpy(max, stu1->name);
			for(j = i+1; j <= linklist->num; j++)
			{
				stu2 = stu2->next;
				if(strcmp(stu2->name, max) < 0)
				{
					strcpy(max, stu2->ID);
					max_index = j;
				}
			}
			if(max_index != i) swapStu(linklist, i, max_index);
		}
	}
}

/****************************************************************************************
Function: void sortStu(LinkList *linklist)
Description: ���ճɼ����򣬸����û�ѡ����������ݶ�linklist�ĸ����ڵ��������
Input:	linklist: ����������� 
		item���ú�����Ҫ����item��ֵ������ͬ���Զ�linklist����  
Return:	�� 
****************************************************************************************/
void gradeSort(LinkList *linklist, int item)
{
	int i, j;
	int max, max_index;
	Student *stu1 = linklist->head;
	Student *stu2 = NULL;
	for(i = 1; i < linklist->num; i++)
	{
		stu1 = getStu(linklist, i);
		max_index = i;
		stu2 = stu1;
		max = stu1->grade[item-3];
		for(j = i+1; j <= linklist->num; j++)
		{
			stu2 = stu2->next;
			if(stu2->grade[item-3] > max)
			{
				max = stu2->grade[item-3];
				max_index = j;
			}
		}
		if(max_index != i) swapStu(linklist, i, max_index);
	}
}

/****************************************************************************************
Function: void swapStu(LinkList *linklist, int index1, int index2)
Description: ����linklist�е�index1�͵�index2���ڵ��ѧ�� 
Input:	linklist: ������ѧ�������� 
		index1����һ��Ҫ������ѧ��
		index2���ڶ���Ҫ������ѧ�� 
Return:	�� 
****************************************************************************************/
void swapStu(LinkList *linklist, int index1, int index2)
{
	if(index1 > index2)
	{
		index2 = index1 + index2;
		index1 = index2 - index1;
		index2 = index2 - index1;
	}
	else if(index1 == index2) return;//��֤index1<index2
	if(index1 <= 0 || index2 > linklist->num)
	{
		printf("��������");
		return;
	}
	Student *stu1 = (Student*)malloc(sizeof(Student));
	Student *stu2 = (Student*)malloc(sizeof(Student));
	
	stu1 = getStu(linklist, index1);
	stu2 = getStu(linklist, index2);
	deleteStu(linklist, index1, 0);
	deleteStu(linklist, index2-1, 0);
	addToLinkList(linklist, stu2, index1-1);
	addToLinkList(linklist, stu1, index2-1);
}

/****************************************************************************************
Function: LinkList *getStuInfor()
Description: ��ȡ�ļ�"Information.txt"��ѧ����Ϣ����������ѧ����Ϊ�ڵ�������ָ��
Return:	���ش���ѧ����Ϣ�������ָ�� 
****************************************************************************************/ 
LinkList *getStuInfor()
{
	FILE *in = fopen("Information.txt", "r");
	LinkList *linklist = newLinkList();
	if(linklist == 0)
	{
		fclose(in);
		printf("�ڴ�ռ䲻�㣬������ʧ��.\n");
		char c;
		printf("�Ƿ񱣴������޸ģ�(Y/N)(���������ַ���ʾ������)");
		fflush(stdin);
		scanf("%c", &c);
		if(c == 89 || c ==121)
		{
			writeStu(linklist);
		}
		exit(-1);
		return NULL;
	}
	else
	{
		while(!feof(in))
		{
			addToLinkList(linklist, readStu(in), linklist->num);
		}
		fclose(in);
		printf("��ȡ��Ϣ���£�\n");
		printLinkList(linklist); 
		return linklist;
	}
}

/****************************************************************************************
Function: readStu
Description: ͨ���ļ�ָ��in����ȡ��һ��ѧ������Ϣ��������ָ���ѧ����ָ�� 
Input:	in:��Ҫ���ж�ȡ���ļ����ļ�ָ�� 
Return:	���ظ�ѧ����ָ�� 
****************************************************************************************/
Student *readStu(FILE *in)
{
	Student *stu = (Student*)malloc(sizeof(Student));
	fscanf(in, "%s\t%s\t%f\t%f\t%f\t%f\t%f\t%f\n", 
		stu->ID, stu->name, &stu->grade[3], &stu->grade[4], &stu->grade[5], &stu->grade[0], &stu->grade[1], &stu->grade[2]);
	return stu;
}

/****************************************************************************************
Function: writeStu
Description: ����ǰlinklist�е���Ϣ���浽�ļ�"Information.txt"�� 
Input:	linklist: ��Ҫ��������� 
Return:	�� 
****************************************************************************************/
void writeStu(LinkList *linklist)
{
	FILE *out = fopen("Information.txt", "w");
	Student *stu = stu = (Student*)malloc(sizeof(Student));
	stu = getStu(linklist, 1);
	while(stu != NULL)
	{
		fprintf(out, "%s\t%20s\t%f\t%f\t%f\t%f\t%f\t%f\n", 
			stu->ID, stu->name, stu->grade[3], stu->grade[4], stu->grade[5], stu->grade[0], stu->grade[1], stu->grade[2]);
		stu = stu->next;
	}
	fclose(out);
	printf("д��ɹ�����"); 
}

/****************************************************************************************
Function: void printMenu()
Description: ����˵� 
Input:	linklist: ��Ҫ��������� 
Return:	�� 
****************************************************************************************/
void printMenu()
{
	printf("\n��������Ҫִ�еĲ�������ţ�\n\
	1. ��ȡ����ȡ��ʷ�ɼ����ļ� \n\
	2. ���룺�����¼�¼ \n\
	3. ɾ����ɾ����¼ \n\
	4. ���� \n\
	5. �޸�ѧ���ɼ� \n\
	6. ����ĳ�����Զ�ѧ������ \n\
	7. ����:����ID��ѧ�����򣬲�����ɼ���Ϊtxt�ļ� \n\
	8. �б�:�г����������е����� \n\
	9. ����\n\
	10.�˳����˳�ϵͳ\n");
}

/****************************************************************************************
Function: void exitSystem(LinkList *linklist)
Description: �˳�ϵͳ����ѯ���û��Ƿ񱣴�linklist 
Input:	linklist: ���ܱ������linklist 
Return:	�� 
****************************************************************************************/
void exitSystem(LinkList *linklist)
{
	char c;
	printf("�Ƿ񱣴������޸ģ�(Y/N)(���������ַ���ʾȡ���˳�)");
	fflush(stdin);
	scanf("%c", &c);
	if(c == 89 || c ==121)
	{
		writeStu(linklist);
		exit(-1);
	}
	else if(c == 78 || c == 110)
	{
		exit(-1);
	}
	else
	{
		printf("��ȡ���˳�!");
		return;
	}
}






