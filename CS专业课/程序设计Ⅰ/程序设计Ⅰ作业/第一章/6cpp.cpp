#include<stdio.h>

int max(int a, int b, int c);

int main(){
	int a, b, c, m;
	printf("���������������� ");
	scanf("%d%d%d", &a, &b, &c);
	m = max(a, b, c);
	printf("�������������ֵΪ�� %d", m);
}


int max(int a, int b, int c){
	int x;
	if(a >= b) x = a;
	else x = b;
	if(c >= x) x = c;
	return x;
}
