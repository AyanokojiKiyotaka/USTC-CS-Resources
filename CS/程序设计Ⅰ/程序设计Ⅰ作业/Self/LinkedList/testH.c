#include "LinkedList.h" 

int main()
{
	
	struct LinkedList *linkedlist = createLinkedList(linkedlist);//����һ������ 
	
	addObj(linkedlist, createObj("wHAT the?"));
	addObj(linkedlist, createObj("what THe?"));
	addObj(linkedlist, createObj("what the?"));//�������object�������� 
	listLinkedList(linkedlist); 
	
	insertObj(linkedlist, createObj("hiahiahia"), 1);//����һ��object
	listLinkedList(linkedlist);
	
	swapObj(linkedlist, 1,2);
	listLinkedList(linkedlist);//����λ��1��2��object 
	
	deleteObj(linkedlist, 2);
	listLinkedList(linkedlist);//ɾ���ڶ���object 
	return 0;
	
}
