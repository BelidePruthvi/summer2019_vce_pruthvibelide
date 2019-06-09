#include<stdio.h>
void print_lengthn(int len,int num){
	int cnt = 0,num1=num;
	while (num)
	{
		num = num / 10;
		cnt += 1;
	}
	if (cnt == len)
		return;
	printf("%d ", num1);
	print_lengthn(len, num1 + 1);
}
void print_length(int n,int num)
{
	if (n > 0)
	{
		
		for (int k = 0; k <= 9; k++)
		{
			num = (num) * 10 + k;
			print_length(n - 1,num);
			
		}
	}
	printf("%d \n", num);
}
void input_printlengthn(){
	int n;
	scanf_s("%d", &n);
	//print_lengthn(n,1);
	int num = 0;
	print_length(n,num);
	getchar();
	getchar();
}