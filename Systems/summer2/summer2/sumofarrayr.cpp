#include<stdio.h>
#include<stdlib.h>
long sumofarray(int *arr, int n)
{
	if (n >= 0)
		return arr[n] + sumofarray(arr, n - 1);
	return 0;
}
void array_sum()
{
	int n, *a;
	scanf_s("%d", &n);
	a = (int *)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
		scanf_s("%ld", &a[i]);
	printf("%d", sumofarray(a, n-1));
	getchar();
	getchar();
}