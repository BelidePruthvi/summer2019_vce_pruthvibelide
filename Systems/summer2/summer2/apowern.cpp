#include<stdio.h>


int apowern(int a,int n)
{
	if (n > 1)
	{
		if (n % 2 == 0)
		{
			int temp = apowern(a, n / 2)%100000007;
			return (temp*temp) % 100000007;
		}
		else
		{
			int temp = apowern(a, n / 2) % 100000007;
			return (temp*temp*a) % 100000007;
		}

	}
	if (n == 0)
		return 1;
	return a;
}

void findpower()
{
	int a, n;
	scanf_s("%d %d", &a, &n);
	printf("%d ",apowern(a, n));
	getchar();
	getchar();
}