#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
	struct node *random;
};

struct node * insert2(int x, struct node *head)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;
	temp->random = NULL;
	if (!head)
		head = temp;
	else
	{
		temp->next = head;
		head = temp;
	}
	return head;
}
struct node * reverse_k(struct node *head, int k)
{
	int cnt = 0;
	struct node *prev = NULL, *curr, *nxt = head;

	while (nxt && cnt<k)
	{
		curr = nxt;
		nxt = nxt->next;
		curr->next = prev;
		prev = curr;
		cnt += 1;
	}
	if (nxt)
		head->next = reverse_k(nxt, k);

	return prev;

}

void reverseK()
{
	int x;
	int n1, k;
	scanf_s("%d %d", &n1,&k);
	struct node *head1 = NULL;
	for (int i = 0; i < n1; i++)
	{
		scanf_s("%d", &x);
		head1 = insert2(x, head1);
	}
	head1 = reverse_k(head1, k);
	while (head1)
	{
		printf("%d ", head1->data);
		head1 = head1->next;
	}
	getchar();
	getchar();
	}
