#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
	int i, n, sum, a;
	sum = 0;
	printf("������a: ");
	scanf("%d", &a);
	if(a < 0 || a > 9){
		printf("�����a����0��9�����֡�");
		exit(-1);
	}
	printf("������n��"); 
	scanf("%d", &n);
	if(!(n >= 1)){
		printf("�����n������������");
		exit(-1);
	} 
	
	for(i = 0; i < n; i++)
	{
		sum += (n-i)*a*pow(10,i);//���n��a*10^i��� 
	}
	printf("S[n] = %d", sum);
	
	return 0;
}
