#include<stdio.h>
#include "..\\Student.h"


int main()
{
	FILE *in = fopen("..\\10.6\\stu_sort", "r");
	FILE *out = fopen("stu_add", "w");
	printf("������Ҫ�����ѧ����ID,name,sub1,sub2,sub3�����Ʊ������:\n");
	Student *stu = (Student*)malloc(sizeof(Student));
	scanf("%d\t%s\t%d\t%d\t%d", &stu->ID, stu->name, &stu->sub1, &stu->sub2, &stu->sub3);
	stu->average = (stu->sub1+stu->sub2+stu->sub3)/3;
	add(in, out, stu);
	printf("������");
	fclose(in);
	fclose(out);
	
	return 0;
}
