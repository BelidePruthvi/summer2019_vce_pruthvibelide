#include<stdio.h>
#include<stdlib.h>
void sort3color(int *a, int n)
{
	int start = 0,mid=0,end=n-1;
	while (mid <= end)
	{
		if (a[mid] == 0)
		{
			int temp = a[mid];
			a[mid] = a[start];
			a[start] = temp;
			mid += 1;
			start += 1;
		}
		else if (a[mid] == 1)
			mid += 1;
		else
		{
			int temp = a[mid];
			a[mid] = a[end];
			a[end] = temp;
			end -= 1;
		}
	}
}
int main()
{
	int n;
	scanf_s("%d", &n);
	int *a = (int *)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
		scanf_s("%d", &a[i]);
	sort3color(a,n);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	getchar();
	getchar();
}