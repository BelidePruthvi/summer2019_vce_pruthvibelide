#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n;
	scanf_s("%d", &n);
	int *arr = (int *)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
		scanf_s("%d", &arr[i]);
	int cnt = 0;
	for (int i = 0; i < n; i++)
		cnt += arr[i];
	for (int i = 0; i < n - cnt; i++)
		printf("%d ", 0);
	for (int i = n - cnt; i < n; i++)
		printf("%d ", 1);
	getchar();
	getchar();
}