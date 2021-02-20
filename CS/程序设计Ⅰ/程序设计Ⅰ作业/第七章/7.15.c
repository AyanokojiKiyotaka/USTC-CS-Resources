#include<stdio.h>
#include<string.h>
#define N 10

void setOrder(char name[N][20], long long ID[N]);
void search(long long id, long long ID[N], char name[N][20]);
void scan(char name[N][20], long long ID[N]);
 
int main()
{
	char name[N][20];
	long long ID[N];
	long long id;
	int i,index;
	
	//���� 
	scan(name, ID);
	
	
	//���������� 
	setOrder(name, ID);
	printf("��ְ������������\nְ����\t\t����\n");
	for(i = 0; i < N; i++)
	{
		printf("%d\t\t%s\n", ID[i], name[i]);	
	} 
	
	
	printf("\n������Ҫ���ҵ�ְ���ţ�");
	scanf("%lld", &id);
	search(id, ID, name);
	
	return 0;
}

//����ְ����������ְ���� 
void scan(char name[N][20], long long ID[N])
{
	int i;
	for(i = 0; i < N; i++)
	{
		fflush(stdin);
		printf("�������%dλְ��������:", i+1);
		gets(name[i]);
		printf("�������%dλְ����ְ���ţ�", i+1);
		scanf("%lld", &ID[i]);
	}
/*	for(i = 0; i < N; i++)
	{
		printf("%d\t\t", ID[i]);
		puts(name[i]);
		printf("\n");
	} */
} 

//��ְ������С������������˳��Ҳ��֮���� 
void setOrder(char name[N][20], long long ID[N])
{
	int left = 0,right = N-1, i;
	long long x;
	char Name[20];
	while(left < right)
	{
		for(i = left; i < right; i++)
		{
			if(ID[i] > ID[i+1]) 
			{
				x = ID[i+1];
				strcpy(Name, name[i+1]);
				ID[i+1] = ID[i];
				strcpy(name[i+1], name[i]);
				ID[i] = x;
				strcpy(name[i], Name);
			}
		}
		right--;
		for(i = right; i > left; i--)
		{
			if(ID[i] < ID[i-1])
			{
				x = ID[i];
				strcpy(Name, name[i]);
				ID[i] = ID[i-1];
				strcpy(name[i], name[i-1]);
				ID[i-1] = x;
				strcpy(name[i-1], Name);
			}
		}
		left++;
	}
}

//����һ��ְ���ţ��������ҷ��ҳ���ְ�������� 
void search(long long id, long long ID[N], char name[N][20])
{
	//���� 
	int i = 0, j = N-1, mid;
	while(i < j)
	{
		mid = ID[(i+j)/2];
		if(mid > id) j = (i+j)/2 - 1;
		else if(mid < id) i = (i+j)/2 + 1;
		else if(mid == id) 
		{
			i = (i+j)/2;
			j = i;
		}
	}
	
	//��� 
	/*
	if(ID[i] == id){
		return i;
	}
	else return -1;
	*/
	if(ID[i] == id)
	{
		puts(name[i]);
	}
	else printf("���޴�ְ����\n");
	
}







