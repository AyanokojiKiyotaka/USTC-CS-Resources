#include<stdio.h>
#include<stdlib.h>
#define n 5
int main()
{
	char s1[n];
	char s2[n];
	printf("�ַ����Ƚ�"); 
	printf("�ַ�������\n�������ַ���s1(������%d���ַ�)�� ", n);
	gets(s1);

	if(s1[n] != '\0')
	{
		printf("�������s1����%d���ַ�\n", n);
		exit(-1); 
	}
	
	printf("�������ַ���s2(������%d���ַ�)�� ", n);
	gets(s2);
	if(s2[n] != '\0')
	{
		printf("�������s2����%d���ַ�\n", n);
		exit(-1); 
	}

	printf("�ȽϵĽ���ǣ�%d\n", STRCMP(s1, s2));
	return 0;
}

int STRCMP(char s1[], char s2[])
{
	int i = 0, j = 0, flag = 0;
	while(s1[j] != '\0' && i == 0)
	{
		i = s1[j] - s2[j];
		j++;
	}
	return i;
} 
