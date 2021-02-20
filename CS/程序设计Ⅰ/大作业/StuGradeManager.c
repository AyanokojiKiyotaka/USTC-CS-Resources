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
#include "fileOperate.c"

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


