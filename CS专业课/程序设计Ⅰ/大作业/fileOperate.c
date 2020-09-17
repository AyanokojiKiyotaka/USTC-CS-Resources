#include "operate.c"

LinkList *getStuInfor();
Student *readStu(FILE *in);
void writeStu(LinkList *linklist);


/****************************************************************************************
Function: getStuInfor
Description: ͨ���ļ�ָ��in����ȡ�ļ���ѧ����Ϣ����������ѧ����Ϣ���ɵ������ָ�� 
Calls:
Called By:
Input:	in:��Ҫ���ж�ȡ���ļ����ļ�ָ�� 
Return:	�ú������ش���ѧ����Ϣ�������ָ�� 
****************************************************************************************/ 
LinkList *getStuInfor()
{
	FILE *in = fopen("Information.txt", "r");
	if(in == 0)
	{
		printf("�ļ���û�м�¼.��Ϊ�������µ�ָ��");
		return newLinkList();
	}//������ܻ�û�취ʵ�� �����о� 
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
Description: ͨ���ļ�ָ��in����ȡ��һ��ѧ������Ϣ�������ظ�ѧ����ָ�� 
Calls:	NULL 
Called By:	getStuInfor; 
Input:	in:��Ҫ���ж�ȡ���ļ����ļ�ָ�� 
Return:	�ú������ظ�ѧ����ָ�� 
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
Description: ����ǰlinklist�е���Ϣ���浽�ļ� 
Calls:	NULL 
Called By:	
Input:	out:��Ҫ����������ļ����ļ�ָ�� 
		linklist: ��Ҫ��������� 
Return:	�ú������ظ�ѧ����ָ�� 
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
