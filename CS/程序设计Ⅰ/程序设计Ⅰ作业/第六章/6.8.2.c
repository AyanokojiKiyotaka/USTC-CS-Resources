#include<stdio.h>
#define m 10
#define n 10
int main()
{
	int a[m][n] = {0};
	int i, j, k, x, index_j,num = 0, totalM = 0, totalN = 0,N=0;
	char c;
	
	 //��������Ԫ��
	printf("������������У���Ϊһ�����һ�������һ���ո�\n\t\t��Ϊ���һ�����һ������������ո�.\n"); 
	do
	{
		do
		{
			printf("�������%d�У���%d�е���(��Ϊ���һ�������һ�ո�)�� ", totalM+1, N+1);
			scanf("%d", &a[totalM][N]);
			N++;
			if(N >= n)
			{
				printf("�Ѵﵽ�������ޣ��������롣\n");
				break;
			}
		} while((c = getchar()) != ' '); 
		totalN = totalN>N ? totalN : N;
		N=0;
		totalM++;
		if(totalM >= m)
		{
			printf("�Ѵﵽ�������ޣ��������롣\n");
			break;
		}
	} while((c = getchar()) != ' ');
	
	
	 //Ѱ�Ұ��� 
	for(i = 0; i < totalM; i++)
	{
		x = a[i][0];
		for(j = 0; j < totalN; j++)
		{
			if(a[i][j] > x) 
			{
				x = a[i][j];
				index_j = j;
			} 
		}//ʹxΪ��i+1����� 
		//���x�Ƿ�Ϊ��index_j+1����С 
		for(k = 0; k < totalM; k++)
		{
			if(a[k][index_j] < x) break;
		}
		if(k == totalM)
		{
			printf("%d Ϊһ����, λ�ڵ�%d�е�%d��\n", a[i][index_j], i+1, index_j + 1);
			num++;
		}
	}
	
	if(num == 0) printf("�ö�ά���鲻���ڰ���");
	return 0;
}
