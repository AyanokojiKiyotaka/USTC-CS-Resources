#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define n 10
void sort(char *str[n]);

int main()
{
	int i;
	char *str[n] = {NULL};
	for(i = 0; i < n; i++)
	{ 
		printf("�����%d���ַ���(С��20���ַ�)", i);
		str[i] = calloc(21, sizeof(char));
		gets(str[i]);
	}
	
	sort(str);
	for(i = 0; i < n; i++)
	{
		puts(str[i]);
	}
} 

void sort(char *str[n])
{
	//ѡ������
	char *t;
	int i, j, k;
	for(i = 0; i < n-1; i++)
	{
		k = i;
		for(j = i + 1; j < n; j++)
		{
			if(strcmp(str[k], str[j]) > 0) k = j;
		}
		if(i != k)
		{
			t = str[i];
			str[i] = str[k];
			str[k] = t;
		}
	}
}



