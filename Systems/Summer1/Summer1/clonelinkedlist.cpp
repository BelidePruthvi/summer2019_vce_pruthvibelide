#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
	struct node *random;
};

struct node * insert(int x,struct node *head)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;
	temp->random = NULL;
	if (!head)
		head = temp;
	else
	{
		temp->next=head;
		head = temp;
	}
	return head;
}
struct node * clone(struct node *head)
{
	struct node *head1 = NULL,*p=head;
	while (p)
	{
		struct node *temp = (struct node *)malloc(sizeof(struct node));
		temp->data = p->data;
		temp->next = NULL;
		temp->random = NULL;
		temp->next = p->next;
		p->next = temp;
		p = temp->next;
	}
	p = head;
	while (p)
	{
		printf("data is %d \n", p->data);
		p = p->next;
	}
	p = head;
	while (p)
	{
		struct node *q = p->next;
		if (p->random)
		{
			q->random = p->random->next;
			
		}
		else
		{
			q->random = NULL;
		}
		p = p->next->next;
	}
	head1 = head->next;
	p = head1;
	struct node * q = head;
	while (p && p->next)
	{
		q->next = q->next->next;
		q = q->next;
		p->next = p->next->next;
		p = p->next;
	}
	q->next = NULL;
	return head1;
}
/*
void main()
{
	struct node *head = NULL;
	int arr[4] = { 4, 3, 2, 1 };
	for (int i = 0; i < 4; i++)
		head=insert(arr[i], head);
	head->random = head->next->next;
	struct node *temp ;
	temp = head->next;
	temp->random = temp->next->next;
	temp = temp->next->next;
	temp->random = head;
	struct node *head1 = clone(head);
	struct node *p = head;
	while (p)
	{
		printf("%d \n", p->data);
		p = p->next;
	}
	while (head1)
	{
		if (head1->random)
			printf("random %d ", head1->random->data);
		else
			printf("random NULL");
		printf(" data %d \n", head1->data);
		head1 = head1->next;

	}
	char ch;
	scanf_s("%c", &ch);
	}
	*/