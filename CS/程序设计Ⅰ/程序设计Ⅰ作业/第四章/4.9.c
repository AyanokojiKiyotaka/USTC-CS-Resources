#include<stdio.h>

int main(){
	int x0, x1, x2, x3, x4, x;
	int n = 0; //��ʾλ��
	printf("������һ����������λ������������ ");
	scanf("%d", &x);
	if(x > 0 && x <100000){
		x4 = x%10;
		x = (x - x4)/10;
		if(x == 0 && n == 0) n = 1;
		x3 = x%10;
		x = (x - x3)/10;
		if(x == 0 && n == 0) n = 2;
		x2 = x%10;
		x = (x - x2)/10;
		if(x == 0 && n == 0) n = 3;
		x1 = x%10;
		x = (x - x1)/10;
		if(x == 0 && n == 0) n = 4;
		x0 = x%10;
		x = (x - x0)/10;
		if(x == 0 && n == 0) n = 5;//��x�ĸ���ʮ���١�ǧ����λ�ֱ�ֵ�� x4,x3,x2,x1,x0 ; ���һ��λ��n 
		
		//�����λ�� 
		
		printf("��������� %d λ\n", n); 
		
		//�ڷֱ����ÿһλ������ 
		switch(n){
			case 5 : printf("��������λΪ�� %d\n", x0);
			case 4 : printf("������ǧλΪ�� %d\n", x1);
			case 3 : printf("�����ְ�λΪ�� %d\n", x2);
			case 2 : printf("������ʮλΪ�� %d\n", x3);
			case 1 : printf("�����ָ�λΪ�� %d\n", x4);
		}	 
		
		//�۰����������λ����
		printf("�����������λ���ֽ��ӦΪ��"); 
		
		switch(n){
			case 5 : printf("%d", x4); printf("%d", x3); printf("%d", x2); printf("%d", x1); printf("%d", x0); break;
			case 4 : printf("%d", x4); printf("%d", x3); printf("%d", x2); printf("%d", x1); break;
			case 3 : printf("%d", x4); printf("%d", x3); printf("%d", x2); break;
			case 2 : printf("%d", x4); printf("%d", x3); break;
			case 1 : printf("%d", x4); break;
		}
		
	}else printf("������������ǲ�����5λ��������");
	return 0;
} 
