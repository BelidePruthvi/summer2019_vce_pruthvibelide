#include<stdio.h>
#include<stdlib.h>
int search_word(char **dict, char *word, int n, int m, int len, int i, int j,int k,int direction)
{
	if (k == len)
		return 1;
	if (direction == 1)
	{
		if (i - 1 >= 0 && j -1>=0 && dict[i][j] == word[k])
			return search_word(dict, word, n, m, len, i - 1, j - 1, k + 1, 1);
		else
			return -1;
	}
	if (direction == 2)
	{
		if (i - 1 >= 0  && dict[i][j] == word[k])
			return search_word(dict, word, n, m, len, i - 1, j , k + 1, 2);
		else
			return -1;
	}
	if (direction == 3)
	{
		if (i - 1 >=0  &&  j + 1 < m && dict[i][j] == word[k])
			return search_word(dict, word, n, m, len, i - 1, j + 1, k + 1, 2);
		else
			return -1;
	}
	if (direction == 4)
	{
		if (j+1<m && dict[i][j] == word[k])
			return search_word(dict, word, n, m, len, i, j+1, k + 1, 4);
		else
			return -1;
	}
	if (direction == 5)
	{
		
		if (i + 1 < n  &&  j + 1 < m && dict[i][j] == word[k])
			return search_word(dict, word, n, m, len, i + 1, j + 1, k + 1, 5);
		else
			return -1;
	}
	if (direction == 6)
	{
		if (i+1<n && dict[i][j] == word[k])
			return search_word(dict, word, n, m, len, i + 1, j, k + 1, 6);
		else
			return -1;
	}
	if (direction == 7)
	{
		if (j - 1 >= 0 && i + 1 < n && dict[i][j] == word[k])
			return search_word(dict, word, n, m, len, i + 1, j - 1, k + 1, 7);
		else
			return -1;
	}
	if (direction == 8)
	{
		if (j - 1 >= 0&& dict[i][j] == word[k])
			return search_word(dict, word, n, m, len, i, j - 1, k + 1, 8);
		else
			return -1;
	}
}
void search(char **dict, char *word,int n,int m,int len)
{
	int i, j,k=0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (dict[i][j] == word[k])
			{
				k += 1;
				if (i + 1 < n && dict[i + 1][j] == word[k])
				{
					if (search_word(dict, word, n, m, len, i + 1, j, 1, 6))
					{
						printf("%d %d %d %d \n", i, j, i + len, j);
					}
				}
				if (i - 1 >= 0 && dict[i - 1][j] == word[k])
				{
					if(search_word(dict, word, n, m, len, i - 1, j, 1, 2))
						printf("%d %d %d %d \n", i, j, i - len, j);
				}
				if (j + 1 < m && dict[i][j + 1] == word[k])
				{
					if(search_word(dict, word, n, m, len, i, j + 1, 1, 4))
						printf("%d %d %d %d \n", i, j, i, j+len);
				}
				if (j - 1 >= 0 && dict[i][j - 1] == word[k])
				{
					if(search_word(dict, word, n, m, len, i, j - 1, 1, 8))
						printf("%d %d %d %d \n", i, j, i, j-len);
				}
				if (i + 1 < n && j + 1 < m && dict[i + 1][j + 1] == word[k])
				{
					if(search_word(dict, word, n, m, len, i + 1, j + 1, 1, 5))
						printf("%d %d %d %d \n", i, j, i + len, j+len);
				}
				if (i + 1 < n && j - 1 >= 0 && dict[i + 1][j - 1] == word[k])
				{
					if(search_word(dict, word, n, m, len, i + 1, j - 1, 1, 7))
						printf("%d %d %d %d \n", i, j, i + len, j-len);
				
				}
				if (i - 1 >= 0 && j + 1 < m && dict[i - 1][j + 1] == word[k])
				{
					if(search_word(dict, word, n, m, len, i - 1, j + 1, 1, 3))
						printf("%d %d %d %d \n", i, j, i - len, j+len);
				}
				if (i-1 >= 0 && j-1 >= 0 && dict[i - 1][j - 1] == word[k])
				{
					if(search_word(dict, word, n, m, len, i - 1, j - 1, 1, 1))
						printf("%d %d %d %d \n", i, j, i - len, j-len);
				}
				k = 0;
			}
		}
	}
}
void input_searchdict()
{
	int n, m,len;
	printf("enter rows and cols of dict");
	scanf_s("%d %d", &n, &m);
	printf("enter dict row wise");
	char **dict = (char **)malloc((n+1)*sizeof(char *));
	for (int i = 0; i < n; i++)
		dict[i] = (char *)malloc((m+1)*sizeof(char));
	for (int i = 0; i < n; i++)
	{
			scanf_s("%s", dict[i],n+1);
	}
	printf("enter the length of word");
	scanf_s("%d", &len);
	printf("enter the word");
	char *word = (char *)malloc((len+1)*sizeof(char));
	scanf_s("%s", word, len+1);
	search(dict, word,n,m,len);
	getchar();
	getchar();
}