#include<stdio.h>
#include<math.h>
int main(){
	float total;
	printf("1000Ԫ����5��\n��ʽ�У�\n1.һ�δ�5���ڣ� \n");
	printf("2.�ȴ�2���ڣ����ں󽫱�Ϣ�ٴ�3���� \n");
	printf("3.��3���ڣ����ں󽫱�Ϣ�ٴ�2���� \n");
	printf("4.��һ���ڣ����ں󽫱�Ϣ�ٴ�1���ڣ�������5�� \n");
	printf("5.����ڴ�������Ϣÿ���Ƚ���һ�� \n\n");
	
	total = 1000 * (1 + 5*0.0414);
	printf("ͨ����ʽ1��5���Ϣ��Ϊ��%f; ������ϢΪ��%f\n", total, total -1000);
	total = 1000 * (1 + 2*0.0468) * (1 + 3*0.054);
	printf("ͨ����ʽ2��5���Ϣ��Ϊ��%f; ������ϢΪ��%f\n", total, total -1000);
	total = 1000 * (1 + 3*0.054) * (1 + 2*0.0468);
	printf("ͨ����ʽ3��5���Ϣ��Ϊ��%f; ������ϢΪ��%f\n", total, total -1000);
	total = 1000 * pow(1 + 1*0.0414, 5);
	printf("ͨ����ʽ4��5���Ϣ��Ϊ��%f; ������ϢΪ��%f\n", total, total -1000);
	total = 1000 * pow(1 + 0.0072/4, 4*5);
	printf("ͨ����ʽ5��5���Ϣ��Ϊ��%f; ������ϢΪ��%f\n", total, total -1000);
	return 0; 
}

/*int main() {
	int choice;
	float total;
	printf("1000Ԫ����5��\n��ʽ�У�\n1.һ�δ�5���ڣ� \n"); 
	printf("2.�ȴ�2���ڣ����ں󽫱�Ϣ�ٴ�3���ڣ� \n");
	printf("3.��3���ڣ����ں󽫱�Ϣ�ٴ�2���ڣ� \n");
	printf("4.��һ���ڣ����ں󽫱�Ϣ�ٴ�1���ڣ�������5�Σ� \n");
	printf("5.����ڴ�������Ϣÿ���Ƚ���һ�Ρ� \n\n");
	printf("�������ʽ���ţ�");
	scanf("%d", &choice);
	switch(choice){
		case 1: total = 1000 * (1 + 5*0.0414); break;
		case 2: total = 1000 * (1 + 2*0.0468) * (1 + 3*0.054); break;
		case 3: total = 1000 * (1 + 3*0.054) * (1 + 2*0.0468); break;
		case 4: total = 1000 * pow(1 + 1*0.0414, 5); break;
		case 5: total = 1000 * pow(1 + 0.0072/4, 4*5); break;
		default: printf("��ʽѡ�����"); 
	}
	printf("ͨ����ʽ%d��5���Ϣ��Ϊ��%f; ������ϢΪ��%f\n", choice, total, total - 1000);
	man();
	return 0;
}
*/
