#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *lptr;
	struct node *rptr;
};
struct node * insert(int x, struct node* head)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = x;
	temp->lptr = NULL;
	temp->rptr = NULL;
	if (!head)
	{
		head = temp;
	}
	else
	{
		temp->rptr = head;
		head->lptr = temp;
		head = temp;
	}
	return head;
}
void display(struct node *head)
{
	while (head)
	{
		printf("%d ", head->data);
		head = head->rptr;
	}
}
void merge(struct node **low, struct node *mid, struct node *high)
{
	struct node *p = *low,*q=mid,*temp;
	while (p != mid && q != high->rptr)
	{
		if (p->data > q->data)
		{
			temp = p->rptr;
			p->lptr->rptr = p->rptr;
			p->rptr->lptr = p->lptr;
			p->rptr = q->rptr;
			q->rptr = p;
			p->lptr = p;
			p = temp;
		}
		else
		{
			temp = q->rptr;
			q->lptr->rptr = q->rptr;
			q->rptr->lptr = q->lptr;
			q->rptr = p->rptr;
			p->rptr = q;
			q->lptr = p;
			p = q->lptr;
			q = temp;
		}
	}

}
void sort_dll(struct node *low, struct node *high){
	struct node *mid = low, *fast = low;
	if (low != high)
	{
		while (fast && fast->rptr)
		{
			mid = mid->rptr;
			fast = fast->rptr->rptr;
		}
		sort_dll(low, mid->lptr);
		sort_dll(mid, high);
		merge(&low, mid, high);
	}
}
void createDoubleLL()
{
	struct node *head = NULL;
	int n,x;
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &x);
		head=insert(x, head);
	}
	display(head);
	struct node *low = head, *high = head;
	while (high && high->rptr)
		high = high->rptr;


	sort_dll(low, high);
	
	getchar();
	getchar();

}

