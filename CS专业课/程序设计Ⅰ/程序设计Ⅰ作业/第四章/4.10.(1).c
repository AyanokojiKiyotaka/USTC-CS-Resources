#include<stdio.h>

int main(){
	float I;
	float s;
	
	printf("��������ҵ���� ");
	scanf("%f", &I);
	
	if(I >= 0){
		float s1 = 100000*0.1;
		float s2 = 100000*0.075 + s1;
		float s4 = 200000*0.05 + s2;
		float s6 = 200000*0.03 + s4;
		float s10 = 400000*0.015 + s6;//��������۳��� 
	
		if(I <= 100000) s = I*0.1;
			else if(I <= 200000) s = (I-100000)*0.075 + s1;
			else if(I <= 400000) s = (I-200000)*0.05 + s2;
			else if(I <= 600000) s = (I-400000)*0.03 + s4;
			else if(I<= 1000000)s = (I-600000)*0.015 + s6; 
			else s = (I-1000000)*0.01 + s10;//����������ֵ��s 
	
		printf("Ӧ��������Ϊ�� %.2f", s);
		
	}else printf("������������"); 
}
