#include<stdio.h>
#include<stdlib.h>
void transpose(int **arr, int r, int c)
{
	int **b = (int **)malloc(r*sizeof(int *));
	for (int i = 0; i<r; i++)
		b[i] = (int *)malloc(c*sizeof(int));
	
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			b[i][j] = arr[j][i];
		}
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}
	char ch;
	scanf_s("%c", &ch);
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
	transpose(arr, r, c);
	
}
