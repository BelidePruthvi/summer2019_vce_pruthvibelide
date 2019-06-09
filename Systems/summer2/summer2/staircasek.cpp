#include<stdio.h>
#include<stdlib.h>
int staircase(int n, int k, int *arr){
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	long sum1 = 0;
	for (int i = 1; i <= k; i++)
	{
		if (arr[n - i] == -1)
			arr[n - i] = staircase(n - i, k, arr);
		sum1 += arr[n - i];
		return sum1;
	}
}

void input_staircase()
{
	int n, k;
	scanf_s("%d %d ", &n, &k);
	printf("%d %d", n, k);
	int *arr = (int *)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
		arr[i] = -1;
	arr[0] = 0;
	arr[1] = 1;
	if (k > n)
		k = n;
	printf("%d",staircase(n, k,arr));
	getchar();
	getchar();
}