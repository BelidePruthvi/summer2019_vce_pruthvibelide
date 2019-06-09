#include<stdio.h>
#include<stdlib.h>
long fibo(int n)
{
	if (n > 1)
		return fibo(n - 1) + fibo(n - 2);
	return n;

}

long fibo1(int n, int *arr){
	if (n > 1)
	{
		if (arr[n - 1] == -1){
			arr[n - 1] = fibo1(n - 1, arr);
		}
		if (arr[n - 2] == -1)
		{
			arr[n - 2] = fibo1(n - 2, arr);
		}
		return arr[n - 1] + arr[n - 2];
		
	}
	return n;
}
void fibo_cal()
{
	int n;
	scanf_s("%d", &n);
	int *arr = (int *)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++)
		arr[i] = -1;
	//printf("%ld\n",fibo(n));
	printf("%ld", fibo1(n, arr));
	getchar();
	getchar();
}