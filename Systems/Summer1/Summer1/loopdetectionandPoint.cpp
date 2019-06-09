#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *next;
};
struct node * insert_element(struct node *head, int x)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;
	if (!head)
		head = temp;
	else
	{
		struct node *p = head;
		while (p->next)
			p = p->next;
		p->next = temp;
	}
	return head;
}
int detect_loopintersection(struct node *head)
{
	struct node *p = head, *q = head;
	while (p && q && q->next)
	{
		p = p->next;
		q = q->next->next;
		if (p == q)
		{
			struct node *temp = head;
			while (temp != p)
			{
				temp = temp->next;
				p = p->next;
			}
			return temp->data;
		}
	}
	return -1;
}

int main()
{
	int x;
	int n1;
	scanf_s("%d", &n1);
	struct node *head = NULL;
	for (int i = 0; i < n1; i++)
	{
		scanf_s("%d", &x);
		head = insert_element( head,x);
	}
	struct node *p = head;
	while (p->next)
		p = p->next;
	p->next = head->next->next;
	printf("%d ", detect_loopintersection(head));
	getchar();
	getchar();
}