#include<stdio.h>
#include<stdlib.h>
#define n 10

int main()
{
	//��n-1���� �����뵽n�� 
	int i = 0, j = n-1,order = -1, total=0;//orderΪ0��ʾ����Ϊ1��ʾ˳�� ,Ϊ-1��ʾδȷ�� 
	char c;
	float x;
	float a[n];
	printf("��ʼ�����ź�������飬���%d��Ԫ�ء�\n", n-1);
	do
	{
		printf("�������%d����(��Ϊ���һ������������һ�ո�)�� ", total+1);
		scanf("%f", &a[total]);
		total++;
		if(total >= n-1)
		{
			printf("�Ѵﵽ���������ޣ��������롣\n");
			break;
		}
	} while((c = getchar()) != ' ');
	
	
	
	//ȷ���Ƿ�Ϊ���� 
	order = 0;
	for(i = 0; i < total-1; i++)
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
		for(i = 0; i < total-1; i++)
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
	j=total;
	if(order == -1)
	{
		printf("����δ������\n");
		exit(-1);
	}
	else 
	{
		printf("����Ҫ��������� ");
		scanf("%f", &x);
		if(order == 1)
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
			} 
		}
	}

	
	//��xӦ���봦֮�����ȫ��˳�� 
	for(i = total; i > j; i--)
	{
		a[i] = a[i-1];
	} 
	a[j] = x;
	
	//���������
	for(i = 0; i < total+1; i++)
	{
		printf("%f ", a[i]);
		if(i%5 == 4) printf("\n");
	}
	printf("\n");
	
	return 0;
} 
