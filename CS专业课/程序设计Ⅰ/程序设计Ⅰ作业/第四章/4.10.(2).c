#include<stdio.h>

int main(){
	float I;
	float s;
	
	printf("��������ҵ���� ");
	scanf("%f", &I);
	if(I>=0){
		float s1 = 100000*0.1;
		float s2 = 100000*0.075 + s1;
		float s4 = 200000*0.05 + s2;
		float s6 = 200000*0.03 + s4;
		float s10 = 400000*0.015 + s6;//��������۳��� 
		
		switch((int)I/100000){
			case 0 : s = I*0.1; break;
			case 1 : s = (I-100000)*0.075 + s1; break;
			case 2 : s = (I-200000)*0.05 + s2; break;
			case 3 :
			case 4 : s = (I-400000)*0.03 + s4; break;
			case 5 :
			case 6 :
			case 7 : s = (I-600000)*0.015 + s6; break;
			case 8 :
			case 9 :
			default : s = (I-1000000)*0.01 + s10; break; //����������ֵ��s 
		}
		printf("Ӧ��������Ϊ�� %.2f", s);
	}else printf("������������"); 
}
