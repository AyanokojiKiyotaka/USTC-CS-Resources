#include<stdio.h>
#include<math.h>

int main(){
	double x, y;
	int h;
	printf("�������ĺ����꣺ ");
	scanf("%lf", &x); 
	printf("�������������꣺ ");
	scanf("%lf", &y); 
	h = ( ((fabs(x)-2)*(fabs(x)-2) + (fabs(y)-2)*(fabs(y)-2)) <= 1 ) ? 10 : 0;
	printf("�õ㽨���߶�Ϊ�� %d", h);
}
