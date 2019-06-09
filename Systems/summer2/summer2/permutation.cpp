#include<stdio.h>
#include<stdlib.h>
void print_permutation()
{

}
void input_permutation()
{
	int *a, n;
	scanf_s("%d", &n);
	a = (int *)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &a[i]);
	}

}