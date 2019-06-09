#include<stdio.h>
#include<stdlib.h>
void spiral(int **arr, int r, int c)
{
	char direction = 'R';
	int i = 0, j = 0;
	while (i < r && j < c)
	{
		if (direction == 'R')
		{
			for (int k = j; k < c; k++)
				printf("%d ", arr[i][k]);
			direction = 'D';
			i += 1;
		}
		else if (direction == 'D')
		{
			for (int k = i; k < r; k++)
				printf("%d ", arr[k][c-1]);
			direction = 'L';
			c -= 1;
		}
		else if (direction == 'L')
		{
			for (int k = c - 1; k >= j; k--)
				printf("%d ", arr[r - 1][k]);
			r -= 1;
			direction = 'U';
		}
		else if (direction = 'U')
		{
			for (int k = r - 1; k >= i; k--)
				printf("%d ", arr[k][j]);
			j += 1;
			direction = 'R';
		}
	}
	getchar();
	getchar();
}

void main()
{
	int r;
	int c;
	scanf_s("%d %d", &r, &c);
	int **arr=(int **)malloc(r*sizeof(int *));
	for(int i=0;i<r;i++)
		arr[i]=(int *)malloc(c*sizeof(int));
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			scanf_s("%d",&arr[i][j]);
	spiral(arr, r, c);
	}