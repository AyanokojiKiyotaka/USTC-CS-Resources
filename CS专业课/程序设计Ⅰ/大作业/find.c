#include "basic.c"
#define N 20
void findPasser(LinkList *linklist);
void findStu(LinkList *linklist);
Student *nameGet(LinkList *linklist, char name[N]);
Student *IDGet(LinkList *linklist, char ID[N]);
Student *getStu(LinkList *linklist, int index);


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
Function: findPasser
Description: ����ID�ҵ�ѧ������ӡ����Ϣ 
Calls:	NULL 
Called By:	;
Input:	linklist: Ҫ�ҵ�����
		ID: Ҫ�ҵ�ѧ����ID 
Output: ���Ҫ�ҵ�ѧ������Ϣ 
Return:	�� 
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
