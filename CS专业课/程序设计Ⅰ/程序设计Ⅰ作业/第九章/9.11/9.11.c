#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 20

struct Student{
	long long ID;
	char name[N];
	struct Student *next;
};
typedef struct Student Student;

struct LinkList{
	Student *head;
	int num;
}; 
typedef struct LinkList LinkList;


void fInLinkList(FILE *in, LinkList *linklist);
LinkList *createLinkList();
Student *createStu(long long ID, char name[N]);
void addStu(LinkList *linklist, Student *student);
Student *getStu(LinkList *linklist, int index);
void swapStu(LinkList *linklist, int index1, int index2);
void IDOrder(LinkList *linklist);
void deleteStu(LinkList *linklist, int index);
void deleteSame(LinkList *la, LinkList *lb);
void print(LinkList *linklist);

int main()
{
	LinkList *La = createLinkList();
	LinkList *Lb = createLinkList();

	FILE *in = fopen("La.dat", "r");
	fInLinkList(in, La);
	fclose(in);
	in = fopen("Lb.dat", "r");
	fInLinkList(in, Lb);
	fclose(in);
	
	printf("ԭ����a:\n");
	print(La);
	printf("ԭ����b:\n");
	print(Lb);
	deleteSame(La, Lb);
	printf("ɾ����ͬ�������a:\n");
	print(La); 
	return 0;
}
//���ļ��ж������ݲ�����linklist�� 
void fInLinkList(FILE *in, LinkList *linklist)
{
	long long ID;
	char name[N];
	if(in != NULL)
	{
		while(!feof(in))
		{
			fscanf(in, "%lld,%s", &ID, name);
			addStu(linklist, createStu(ID, name));
		}
	}
}
//�������� 
LinkList *createLinkList()
{
	LinkList *linklist = (LinkList*)malloc(sizeof(LinkList));
	if(linklist == NULL)
	{
		printf("no enough memory");
		return;
	}
	linklist->head = (Student*)malloc(sizeof(Student));
	linklist->head->next = NULL;
	linklist->num = 0;
	return linklist;
}
//����ѧ�� 
Student *createStu(long long ID, char name[N])
{
	Student *student = (Student*)malloc(sizeof(Student));
	if(student == NULL)
	{
		printf("no enough memory");
		return;
	}
	student->ID = ID;
	strcpy(student->name, name);
	student->next = NULL;
	return student;
}
//���ѧ�� 
void addStu(LinkList *linklist, Student *student)
{
	Student *sp = getStu(linklist, linklist->num);
	linklist->num++;
	sp->next = student;
}
//��ȡѧ����ָ�� 
Student *getStu(LinkList *linklist, int index)
{
	int i;
	Student *sp = linklist->head;
	for(i = 0; i < index; i++)
	{
		sp = sp->next;
	}
	return sp;
}
//������linklist�н���ѧ��λ�� 
void swapStu(LinkList *linklist, int index1, int index2)
{
	int i;
	if(index1 > index2)
	{
		i = index1;
		index1 = index2;
		index2 = i;
	}
	else if(index1 = index2) return;
	Student *bs1 = getStu(linklist, index1-1);
	Student *bs2 = getStu(linklist, index2-1);
	Student *s1 = bs1->next;
	Student *s2 = bs2->next;
	Student *as2 = bs2->next->next;
	Student *temp = (Student*)malloc(sizeof(Student));
	if(index2 - index1 == 1)
	{
		s1->next = as2;
		s2->next = s1;
		bs1->next = s2;
	}
	else
	{
		temp = s1->next;
		s1->next = s2->next;
		s2->next = temp;
		bs1->next = s2;
		bs2->next = s1;
	}
}
//����ID���� 
void IDOrder(LinkList *linklist)
{
	int i, j, min;
	for(i = 1; i < linklist->num+1; i++)
	{
		for(j = i+1; j < linklist->num+1; j++)
		{
			if(getStu(linklist, j) < getStu(linklist, min)) min = j;
		}
		if(min != i) swapStu(linklist, i, min);
	}
}
//ɾ��ѧ�� 
void deleteStu(LinkList *linklist, int index)
{
	Student *before = getStu(linklist, index-1);
	Student *present = getStu(linklist, index);
	before->next = present->next;
	free(present);
	linklist->num--;
}
//��la��ɾȥ��b��������ͬѧ�ŵĽڵ� 
void deleteSame(LinkList *la, LinkList *lb)
{
	int i,j;
	long long ID;  
	Student *sb = lb->head;
	Student *sa =NULL;
	
	while((sb = sb->next) != NULL)
	{
		ID = sb->ID;
		sa = la->head;
		i=0;
		while((sa = sa->next) != NULL)
		{
			i++;
			if(sa->ID == ID)
			{
				deleteStu(la, i);
				break;
			}
		}
	}
}
//��ӡ������Ϣ 
void print(LinkList *linklist)
{
	Student *sp = linklist->head;
	printf("ѧ��\t\t����\n");
	while((sp = sp->next) != NULL)
	{
		printf("%lld\t\t%s\n", sp->ID, sp->name);	
	}
	printf("\n");
}








