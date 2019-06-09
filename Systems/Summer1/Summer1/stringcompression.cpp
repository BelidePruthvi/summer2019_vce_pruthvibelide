#include<stdio.h>
void compress(char *str)
{
	int cnt = 0,j=1;
	for (int i = 1; str[i] != '\0'; i++)
	{
		if (str[i] == str[i - 1])
		{
			cnt += 1;
		}
		else
		{
			if (cnt>0)
				str[j++] = cnt + 1+  '0';
			str[j++] = str[i];
			
			cnt = 0;
		}

	}
	if (cnt>0)
		str[j++] = cnt + 1 +'0';
	str[j] = '\0';
}
int main()
{
	char str[100];
	scanf_s("%s", str, 100);
	compress(str);
	printf("%s", str);
	getchar();
	getchar();
}