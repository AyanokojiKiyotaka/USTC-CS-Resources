#include<stdio.h>
#include "..\\Student.h"


int main()
{
	int i;
	FILE *out = fopen("stud", "w");
	for(i = 0; i < STUNUM; i++)
	{
		printf("�ֱ������%dλѧ����ID,name,sub1,sub2,sub3�����Ʊ������:\n", i); 
		scanfStu(out);
	}
	printf("д�����");
	fclose(out);
} 



