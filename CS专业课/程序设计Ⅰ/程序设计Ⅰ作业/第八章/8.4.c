#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
void adjust(int *pn, int n, int m);

int main()
{
	int i, n, m;
	printf("����n :");
	scanf("%d", &n);
	printf("����m :");
	scanf("%d", &m);
	if(m > n) 
	{
		printf("m>n,������Ҫ��");
		exit(-1);
	} 
	int *pn = calloc(n, sizeof(int));
	for(i = 0; i < n; i++)
	{
		printf("�����%d��������", i);
		scanf("%d", (pn++));
	}
	pn -= n;//let p point to the beginning.
	
	adjust(pn, n, m);
	
	//��� 
	printf("������õ���\n");
	for(i = 0; i < n; i++)
	{
		printf("%d\t", *(pn++));
		if(i % 10 == 9) printf("\n");
	}
}

void adjust(int *pn, int n, int m)
{
	int *pm = calloc(m, sizeof(int));
	int i;
	for(i = 0; i < m; i++)
	{
		*(pm + i) = *(pn + n-m + i);
	}
	for(i = n-1; i > m - 1; i--)
	{
		*(pn + i) = *(pn + i - m);
	}
	for(i = 0; i < m; i++)
	{
		*(pn + i) = *(pm + i);
	}
}





