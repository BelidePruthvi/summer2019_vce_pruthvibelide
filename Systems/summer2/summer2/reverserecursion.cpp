#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *next;
};
/*struct node * insert(struct node *head, int x)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;
	if (head) 
	{
		temp->next - head;
		head = temp;
	}
}*/