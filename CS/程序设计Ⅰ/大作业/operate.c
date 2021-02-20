#include "find.c"

void addToLinkList(LinkList *linklist, Student *stu, int index);
void editGrade();
void deleteStu(LinkList *linklist, int index, int mode);
void sortStu(LinkList *linklist);
void strSort(LinkList *linklist, int item);
void gradeSort(LinkList *linklist, int item);
void swapStu(LinkList *linklist, int index1, int index2);


/****************************************************************************************
Function: addtoLinkList
Description: ��ѧ��stu���뵽����linklist��β�� 
Calls:	getStu();
		printLinkList();
Called By:	getStuInfor(); 
Input:	linklist: �����ѧ��������
		stu: �������ѧ��
		index: ��index = -1 ��ʾѯ���û����뵽�ģ���0 <= index && index <= linklist->num��ʱ����ֱ�Ӳ����index���ڵ�֮��
Return:	�� 
****************************************************************************************/
void addToLinkList(LinkList *linklist, Student *stu, int index) // 
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

void deleteStu(LinkList *linklist, int index, int mode) //mode == 1 ���ͷ�ɾ����Student���ڴ� 
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
Function: editGrade
Description: �޸�ĳ��ѧ���ĳɼ� 
Calls:	
Called By:	
Input:	linklist: ��ѧ���������� 
		ID: Ҫ�޸ĵ�ѧ����ID  
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
/**************************************************************	
	if(index2 - index1 > 1)
	{
		stu1 = getStu(linklist, index1-1);
		stu2 = getStu(linklist, index2-1);
		Student *temp = (Student*)malloc(sizeof(Student));
		temp = stu1->next->next;
		stu1->next->next = stu2->next->next;
		stu2->next->next = temp;
		temp = stu1->next;
		stu1->next = stu2->next;
		stu2->next = temp;
	}
	else if(index2 - index1 == 1)
	{
		stu1 = getStu(linklist, index1-1);
		stu2 = getStu(linklist, index2-1);
		Student *temp = (Student*)malloc(sizeof(Student));
		temp = stu2->next;
		stu1->next->next = stu2->next->next;
		stu1->next = temp;
		temp->next = stu2;
	}
//����һ����ɵ�Ƶ��㷨 
***************************************************************/
	 
}







