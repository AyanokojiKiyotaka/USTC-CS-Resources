#include<stdio.h>
#include<stdlib.h>
#define n 10

int main()
{
	//��n-1���� �����뵽n�� 
	int i = 0, j = n-1,order = -1;//orderΪ0��ʾ����Ϊ1��ʾ˳�� ,Ϊ-1��ʾδȷ�� 
	float x;
	float a[n] = {10,9,9,6,5,4,3,2,1};//��Ŀδ���������֪���飬�˴��Զ���һ�� 
	printf("�����뽫Ҫ�������: ");
	scanf("%f", &x);
	
	//ȷ���Ƿ�Ϊ���� 
	order = 0;
	for(i = 0; i < n-2; i++)
	{
		if(a[i] < a[i+1]) 
		{
			order = -1;
			break; 
		}
	} 
	if(order == -1)//��ʱ��Ϊ�����ж��Ƿ�Ϊ˳�� 
	{
		order = 1;
		for(i = 0; i < n-2; i++)
		{
			if(a[i] > a[i+1])
			{
				order = -1;
				break;
			}
		}
	} 
	//�ҵ� xӦ��λ�� 
	i=0;
	if(order == -1)
	{
		printf("����δ������\n");
		exit(-1);
	}else if(order == 1)
	{
		while((j - i)*(j - i) >= 1)
		{
			if(a[(i+j)/2] == x) 
			{
				i = (i + j)/2;
				j = i;
			}
			else if(a[(i+j)/2] > x) j = (i + j)/2-1;
			else i = (i + j)/2+1;
		} 
	}else if(order == 0)
	{
		while((j - i)*(j - i) >= 1)
		{
			if(a[(i+j)/2] == x) 
			{
				i = (i + j)/2;
				j = i;
			}
			else if(a[(i+j)/2] < x) j = (i + j)/2-1;
			else i = (i + j)/2+1;
			printf("i = %d  j = %d\n", i , j);
		} 
	}

	
	//��xӦ���봦֮�����ȫ��˳�� 
	for(i = n-1; i > j; i--)
	{
		a[i] = a[i-1];
	} 
	a[j] = x;
	
	//���������
	for(i = 0; i < n; i++)
	{
		printf("%f ", a[i]);
		if(i%5 == 4) printf("\n");
	}
	printf("\n");
	
	return 0;
} 
