#include<stdio.h>
#include<stdlib.h>
#define N 20

void STRCPY(char s1[], char s2[]);
int main()
{
	char s1[N+1];
	char s2[N+1];
	s2[N] = '\0';
	printf("������s2(������%d���ַ�): ", N);
	gets(s2);
	if(s2[N] != '\0')
	{
		printf("�������s2����%d���ַ�\n", N);
		exit(-1); 
	}
	printf("���ƽ���У�s1Ϊ�� ");
	STRCPY(s1, s2);
	puts(s1); 
} 

void STRCPY(char s1[], char s2[])
{
	int i = 0;
	while(s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}
