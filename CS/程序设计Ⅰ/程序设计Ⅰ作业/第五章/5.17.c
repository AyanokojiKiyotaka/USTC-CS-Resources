#include<stdio.h>

int main()
{
	int a = 0, b = 0, c = 0, flag = 0; //��i, j, k ��ʾA, B, C����0, 1, 2 ��ʾX, Y, Z 
	for(a = 0; a < 3; a++)
	{//����6����� 
		for(b = 0; b < 3; b++)
		{
		//	if(a == b) break;
			c = 3-a-b;
			if(a != b && a != c && b != c)
			{
				if(a != 0 && c != 0 && c != 2) 
				{//��Ŀ������ 
					flag = 1;
					break;
				}
			}
		}
		if(flag == 1) {
			printf("A��%c\n", 'X' + a);
			printf("B��%c\n", 'X' + b);
			printf("C��%c\n", 'X' + c);
			flag = 0;
		} 
	}
	

} 






























/*
char add(char x);

int main(){
	char A, B, C;
	int flag = 0;
	for(A = 'X';; A++){
		for(B = add(A); B != A; B = add(B)){
			C = 'X' + 'Y' + 'Z' - A - B; //ͨ��ѭ������A, B, C�ֱ�ֵΪA, B, C���������� 
			if(A != 'X' && C != 'X' && C != 'Z') flag = 1;
			if(flag == 1) break;
		}
		if(flag == 1) break;
	}
	if(flag == 1){
		printf("A��%c\n", A);
		printf("B��%c\n", B);
		printf("C��%c\n", C);
	}else printf("û���ҵ����ʵĽ��");
	return 0;
} 

char add(char x){
	return x == 'Z' ? 'X' : (x+1);
}
*/
//ɵ�Ʒ��� 
