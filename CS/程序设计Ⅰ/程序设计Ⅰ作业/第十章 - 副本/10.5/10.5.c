#include<stdio.h>
#include "..\\Student.h"


int main()
{
	int i;
	FILE *in = fopen("stud", "r");
	fscanf(in, "%d\n", &STUNUM);
	fclose(in);
	FILE *out = fopen("stud", "w+");
	fprintf(out, "%d\n", STUNUM);
	for(i = 0; i < STUNUM; i++)
	{
		printf("�ֱ������%dλѧ����ID,name,sub1,sub2,sub3�����Ʊ������:\n", i); 
		scanfStu(out);
	}
	printf("д�����");
	fclose(out);
} 



