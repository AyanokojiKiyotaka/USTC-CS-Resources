#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define n 20


void STRCAT(char s1[], char s2[]);

int main()
{
	char s1[2*n+1];
	char s2[n+1];
	s1[n] = '\0';
	s2[n] = '\0';
	int i, s1len, s2len;
	/*
	 *�����ַ���
	 */ 
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
	
	STRCAT(s1, s2);
	
	//������ 
	printf("�ַ������ӽ����\n");
	puts(s1);
	return 0; 
}
//ƴ��
void STRCAT(char s1[], char s2[])
{
	int s1len = strlen(s1);
	int s2len = strlen(s2); 
	int i = 0;
	while(s2[i] != '\0')
	{
		s1[i + s1len] = s2[i];
		i++;
	}
	s1[i+s1len] = '\0';
}
