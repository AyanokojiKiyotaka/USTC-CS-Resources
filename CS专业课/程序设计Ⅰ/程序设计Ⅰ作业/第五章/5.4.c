#include<stdio.h>

int main()
{
	char c;
	int letters = 0, space = 0, num = 0, others = 0;
	while((c = getchar()) != '\n'){
		if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) letters++;
		else if(c == ' ') space++;
		else if('0' <= c  && c <= '9') num++;
		else others++;
	}
	printf("Ӣ����ĸ�� %d��\n",letters);
	printf("�ո��� %d��\n", space);
	printf("������ %d��\n", num);
	printf("�����ַ��� %d��\n", others);
	return 0;	
}
