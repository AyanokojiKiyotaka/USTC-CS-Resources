#include<stdio.h>

int main(){
	int x;
	char level;
	printf("������ٷ��Ƴɼ���");
	scanf("%d", &x);
	if(x > 100 || x < 0) printf("�ɼ��������󣬲��ǰٷ��Ƴɼ���");
	else {
		if(x < 60) level = 'E';
			else if(x <= 69) level = 'D';
			else if(x <= 79) level = 'C';
			else if(x <= 89) level = 'B';
			else level = 'A';
		printf("�ɼ��ȼ�Ϊ�� %c", level);
	}
	return 0;
} 
