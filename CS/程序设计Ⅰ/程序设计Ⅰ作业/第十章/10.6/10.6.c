#include<stdio.h>
#include "..\\Student.h"



int main()
{
	FILE *in = fopen("..\\10.5\\stud", "r");
	FILE *out = fopen("stu_sort", "w");
	char str[20];
	int d;
	sort(in, out);
	printf("�������");
	fclose(out);
	fclose(in);
	return 0;
}



