#include<stdio.h>
void print_anagram()
{
	FILE *fp;
	char input[50],check[50];
	int freq[26] = { 0 };
	fopen_s(&fp, "words.txt", "r");
	if (!fp)
	{
		printf("cant open the file");
		return;
	}
	scanf("%s", &input);
	while (fscanf(fp, "%s", check) != -1)
	{
		int i;
		for (i = 0; input[i] != '\0'; i++)
		{
			int idx = 0;
			if (input[i] >= 'A' && input[i] <= 'Z')
				idx = input[i] - 'A';
			else
				idx = input[i] - 'a';
			freq[idx] += 1;
		}
		for (i = 0; check[i] != '\0'; i++)
		{
			int idx;
			if (check[i] >= 'A' && check[i] <= 'Z')
				idx = input[i] - 'A';
			else
				idx = input[i] - 'a';
			if (freq[idx] == 0)
				break;
		}
		if (check[i] == '\0')
			printf("%s\n", check);
		i = 0;
		while (i < 26)
		{
			freq[i] = 0;
			i += 1;
		}
	}
	getchar();
	getchar();
}