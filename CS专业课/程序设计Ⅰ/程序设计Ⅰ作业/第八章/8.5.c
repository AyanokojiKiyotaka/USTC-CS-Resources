#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i, n, left, count3 = 0, count = 0;
	//����n 
	printf("����n��");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("�����˷�������");
		exit(-1);
	}
	left = n;
	
	//���ٿռ� 
	int *p = calloc(n, sizeof(int));
	
	//��ʼ�� 
	for(i = 0; i < n; i++)
	{
		*(p + i) = i + 1;
	}
	//��ʼ������3�˳� 
	while(1)
	{
		//�Ƿ����˳� 
		if(*p != 0)
		{
			count3++;
		}
	
		//�Ƿ񵽵������� 
		if(count3 == 3)
		{
			count3 = 0;
			left--;
			if(left != 0) 
			{
				*p = 0;	
			}
		}
		
		if(left == 0) 
		{
			printf("���ʣ�µ���ԭ���ĵ�%d��", *p);
			break;
		}
		
		//ʹpָ����һ���� 
		if(count == n-1)
		{
			p = p - n + 1;
			count = 0;
		}
		else
		{
			p++;
			count++;
		}
	}
	
	free(p-*p);
} 
