#include<stdio.h>
struct node *insert(int x,struct node *head);
void createDoubleLL();
void display(struct node *head);
void sort_dll(struct node *low, struct node *high);
void merge(struct node*low, struct node *mid, struct node *high);