#include<stdio.h>
#include<math.h> 
#define N 100
int main()
{
	int a[N];
	int i, j, n = sqrt(N);
	for(i = 0; i < N; i++)
	{
		a[i] = i+1;
	}
	a[0] = 0; //����1���⣬�ȸ�ֵΪ0�� 
	//����������ֵΪ0 
	for(i = 1; i < n; i++)
	{
		if(a[i] != 0)
		{
			for(j = i + 1; j < N; j++)
			{
				if(a[j] % a[i] == 0) a[j] = 0;
			}
		}
	}
	
	//������� 
	printf("%d֮�ڵ������У�\n", N);
	for(i = 0; i < 100; i++)
	{
		if(a[i] != 0) printf("%d\n", a[i]);
	} 
	return 0; 
} 
