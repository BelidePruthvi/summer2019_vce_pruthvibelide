#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct cell{
	char expr[100];
	int visited;
};
int evaluate(char *expr, struct cell arr[10][10])
{
	//this function can evaluate upto 2 parameters
	if (expr[0] >= '0'&& expr[0] <= '9')
	{
		int num = 0;
		int start = 0;
		while (expr[start] >= '0' && expr[start] <= '9')
		{
			num = num * 10 + (expr[start] - '0');
			start += 1;
		}
		if (expr[start] == '\0')
			return num;
		int temp = start;
		start += 1;
		int col = expr[start] - 'A';
		int row;
		if (expr[start + 1] == '0' && expr[start + 2] == '1')
			row = 10;
		else
			row = expr[start + 1] - '0';
		if (expr[temp] == '*')
		{

			return num*evaluate(arr[row - 1][col].expr, arr);
		}
		else if (expr[temp] == '/')
		{
			return num / evaluate(arr[row - 1][col].expr, arr);
		}
		else if (expr[temp] == '+')
		{
			return num + evaluate(arr[row - 1][col].expr, arr);
		}
		else if (expr[temp] == '-')
		{
			return num - evaluate(arr[row - 1][col].expr, arr);
		}
	}
	else
	{
		int start = 0;
		int col = expr[start] - 'A';
		int row;
		if (expr[start + 1] == '0' && expr[start + 2] == '1')
		{
			start += 1;
			row = 9;
		}
		else
			row = expr[start + 1] - '0' - 1;
		start += 2;
		int temp = start;
		start += 1;
		int num = 0;
		if (expr[start] >= '0' && expr[start] <= '9')
		{
			while (expr[start] != '\0')
			{
				num = num * 10 + (expr[start] - '0');
				start += 1;
			}
			if (expr[temp] == '*')
			{

				return evaluate(arr[row][col].expr, arr)*num;
			}
			else if (expr[temp] == '/')
			{
				return evaluate(arr[row][col].expr, arr) / num;
			}
			else if (expr[temp] == '+')
			{
				return evaluate(arr[row][col].expr, arr) + num;
			}
			else if (expr[temp] == '-')
			{
				return evaluate(arr[row][col].expr, arr) - num;
			}
		}
		else
		{
			int col1 = expr[start] - 'A';
			int row1;
			if (expr[start + 1] == '0' && expr[start + 2] == '1')
			{
				start += 1;
				row1 = 9;
			}
			else
				row1 = expr[start + 1] - '0' - 1;
			if (expr[temp] == '*')
			{

				return evaluate(arr[row][col].expr, arr)*evaluate(arr[row1][col1].expr, arr);
			}
			else if (expr[temp] == '/')
			{
				return evaluate(arr[row][col].expr, arr) / evaluate(arr[row1][col1].expr, arr);
			}
			else if (expr[temp] == '+')
			{
				return evaluate(arr[row][col].expr, arr) + evaluate(arr[row1][col1].expr, arr);
			}
			else if (expr[temp] == '-')
			{
				return evaluate(arr[row][col].expr, arr) - evaluate(arr[row1][col1].expr, arr);
			}
		}
	}
}
int precedence(char ch)
{
	if (ch == '+' || ch=='-')
		return 1;
	if (ch == '*' || ch == '/')
		return 2;
	if (ch == '(')
		return 0;
	return -1;

}
void push(char symbol[100], int numbers[100], int *top_symbol, int *top_numbers,char oper)
{
	
	if (*top_symbol == -1)
	{
		symbol[++*top_symbol] = oper;
	}
	else if (oper == '(')
		symbol[++*top_symbol] = oper;
	else if (oper == ')')
	{
		while (symbol[*top_symbol] != '(')
		{
			char ch = symbol[*top_symbol];
			*top_symbol -= 1;
			int num1 = numbers[*top_numbers];
			*top_numbers -= 1;
			int num2 = numbers[*top_numbers];
			*top_numbers -= 1;
			if (ch == '+')
				numbers[++*top_numbers] = num2 + num1;
			if (ch == '-')
				numbers[++*top_numbers] = num2 - num1;
			if (ch == '*')
				numbers[++*top_numbers] = num2 * num1;
			if (ch == '/')
				numbers[++*top_numbers] = num2 / num1;
		}
		*top_symbol -= 1;
	}
	else
	{
		while (precedence(oper) <= precedence(symbol[*top_symbol]) && *top_symbol!=-1)
		{
			char ch = symbol[*top_symbol];
			*top_symbol -= 1;
			int num1 = numbers[*top_numbers];
			*top_numbers -= 1;
			int num2 = numbers[*top_numbers];
			*top_numbers -= 1;
			if (ch == '+')
				numbers[++*top_numbers] = num2 + num1;
			if (ch == '-')
				numbers[++*top_numbers] = num2 - num1;
			if (ch == '*')
				numbers[++*top_numbers] = num2 * num1;
			if (ch == '/')
				numbers[++*top_numbers] = num2 / num1;

		}
		symbol[++*top_symbol] = oper;
	}
}
//This function evaluate any expression

int evaluate_expression(char expr[100], struct cell arr[10][10])
{
	int i,res=0;
	for (i = 0; expr[i] != '\0'; i++)
	{
		if (expr[i] < '0' || expr[i] > '9')
			break;
		res = res * 10 + (expr[i] - '0');
	}
	if (expr[i] == '\0')
		return res;

	char symbol[100];
	int numbers[100];
	int top_symbol = -1;
	int top_numbers = -1;
	int k = 0;
	
	for (int i = 0; expr[i] != '\0'; i)
	{

		char temp[100];
		int idx = 0;
		if (expr[i] == '*' || expr[i] == '+' || expr[i] == '-' || expr[i] == '/' || expr[i] == '(' || expr[i] == ')')
		{
			push(symbol, numbers, &top_symbol, &top_numbers, expr[i]);
			i += 1;
		}
		else if (expr[i] >= '0' && expr[i] <= '9')
		{
			int num = 0;
			while (expr[i] >= '0' && expr[i] <= '9')
			{
				num = num * 10 + (expr[i] - '0');
				i += 1;
			}
			numbers[++top_numbers] = num;
		}
		else
		{
			int col = expr[i] - 'A';
			i += 1;
			int row;
			if (expr[i] == '0' && expr[i] == '1')
			{
				i += 1;
				row = 9;
			}
			else
				row = expr[i] - '0' - 1;
			numbers[++top_numbers] = evaluate_expression(arr[row][col].expr, arr);
			i += 1;

		}
	}
	while (top_symbol != -1)
		{
			char ch = symbol[top_symbol];
			top_symbol -= 1;
			int num1 = numbers[top_numbers];
			top_numbers -= 1;
			int num2 = numbers[top_numbers];
			top_numbers -= 1;
			if (ch == '+')
				numbers[++top_numbers] = num2 + num1;
			if (ch == '-')
				numbers[++top_numbers] = num2 - num1;
			if (ch == '*')
				numbers[++top_numbers] = num2 * num1;
			if (ch == '/')
				numbers[++top_numbers] = num2 / num1;
		}
	return numbers[top_numbers];
}

void get(struct cell arr[10][10], int row, int col)
{
	printf("%d\n", evaluate_expression(arr[row][col].expr, arr));
	
}
int check_cycle(char *expression, struct cell arr[10][10])
{
	for (int i = 0; expression[i] != '\0'; i)
	{
		if (expression[i] == '*' || expression[i] == '+' || expression[i] == '-' || expression[i] == '/' || expression[i] == ')' || expression[i] == '(')
		{
			i += 1;
		}
		else if (expression[i] >= '0' && expression[i] <= '9')
		{
			while (expression[i] >= '0' && expression[i] <= '9')
			{
				i += 1;
			}
		}
		else
		{
			int col = expression[i] - 'A';
			i += 1;
			int row;
			if (expression[i] == '0' && expression[i] == '1')
			{
				i += 1;
				row = 9;
			}
			else
				row = expression[i] - '0' - 1;
			i += 1;
			if (arr[row][col].visited == 1)
				return 0;
			arr[row][col].visited = 1;
			if (check_cycle(arr[row][col].expr, arr) == 0)
				return 0;
			arr[row][col].visited = 0;

		}
	}
	return 1;
}
void set(struct cell arr[10][10], int row, int col, char *expression)
{
	arr[row][col].visited = 1;
	if (check_cycle(expression,arr))
		strcpy_s(arr[row][col].expr, expression);
	else
		printf("cant accept the input-> leads to cycle\n");
	arr[row][col].visited= 0;

}
void export1(char *filename, struct cell arr[10][10])
{
	int i = 0;
	for (i = 0; filename[i] != '\0'; i++);
	filename[i] = '.';
	i += 1;
	filename[i] = 'c';
	filename[i + 1] = 's';
	filename[i + 2] = 'v';
	filename[i + 3] = '\0';
	FILE *fp;
	fopen_s(&fp, filename, "w");
	for (int row = 0; row <= 9; row++)
	{
		for (int col = 0; col <= 9; col++)
		{
			fprintf(fp, "%s", arr[row][col].expr);
			fprintf(fp, "%c %c ",' ', ',');

		}
		fprintf(fp, "\n");
	}
	filename[i-1] = '\0';
	fclose(fp);

}
void import1(char *filename, struct cell arr[10][10])
{
	char dummy[100];
	int i = 0;
	for (i = 0; filename[i] != '\0'; i++);
	filename[i] = '.';
	i += 1;
	filename[i] = 'c';
	filename[i + 1] = 's';
	filename[i + 2] = 'v';
	filename[i + 3] = '\0';
	FILE *fp;
	char ch;
	fopen_s(&fp, filename, "r");
	if (!fp)
	{
		printf("file doesnot exit\n");
		return;
	}
	for (int row = 0; row <= 9; row++)
	{
		for (int col = 0; col <= 9; col++)
		{
			fscanf(fp, "%s", arr[row][col].expr);
			fscanf(fp, "%s", dummy);
			fscanf(fp, "%c", &ch);
		}
	}
	filename[i-1] = '\0';
	fclose(fp);

}
void print(struct cell arr[10][10])
{
	printf("       ");
	for (int col = 0; col < 10; col++)
	{
		printf("%c     ", col + 'A');
	}
	printf("\n");
	for (int row = 0; row <= 9; row++)
	{
		printf("%2d ", row + 1);
		for (int col = 0; col <= 9; col++)
		{
			printf("%5d ", evaluate_expression(arr[row][col].expr, arr));
		}
		printf("\n");
	}
}
void basic_inputs()
{
	struct cell	arr[10][10];
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			arr[row][col].expr[0] = '0';
			arr[row][col].expr[1] = '\0';
			arr[row][col].visited = 0;
		}
	}
	char input[100];
	char match[100];
	char *filename = (char *)malloc(sizeof(char) * 100);
	filename[0] = '\0';
	int start, idx;
	int col, row;
	while (1)
	{
		start = 0;
		printf(">");
		gets_s(input);
		if (input[0]=='\0')
			continue;
		for (idx = 0; input[idx] != ' ' && input[idx] != '\0'; idx++)
		{
			match[start++] = input[idx];
		}
		match[start] = '\0';
		if (strcmp(match, "get") == 0)
		{
			while (input[idx] == ' ' && input[idx] != '\0')
				idx += 1;
			if (input[idx] >= 'a' && input[idx] <= 'z')
				input[idx] = input[idx] - 'a' + 'A';
			col = input[idx] - 'A';
			idx += 1;
			if (input[idx] == '1' && input[idx + 1] == '0')
			{
				idx += 1;
				row = 10;
			}
			else
				row = input[idx] - '0';
			get(arr, row - 1, col);
		}
		else if (strcmp(match, "set") == 0)
		{
			while (input[idx] == ' ' && input[idx] != '\0')
				idx += 1;
			if (input[idx] >= 'a' && input[idx] <= 'z')
				input[idx] = input[idx] - 'a' + 'A';

			col = input[idx] - 'A';
			idx += 1;
			if (input[idx] == '1' && input[idx + 1] == '0')
			{
				idx += 1;
				row = 10;
			}
			else
				row = input[idx] - '0';
			idx += 1;
			if (input[idx] == '=')
				idx += 1;
			char *expression = (char *)malloc(100 * sizeof(char));
			int num = 0;
			while (input[idx] != '\0')
			{
				if (input[idx] >= 'a' && input[idx] <= 'z')
					input[idx] = input[idx] - 'a' + 'A';
				expression[num++] = input[idx];
				idx += 1;
			}
			expression[num] = '\0';
			set(arr, row - 1, col, expression);
		}
		else if (strcmp(match, "print") == 0)
		{
			print(arr);
		}
		else if (strcmp(match, "import") == 0)
		{
			int fileidx = 0;
			while (input[idx] != '.' && input[idx] != '\0')
			{
				filename[fileidx++] = input[idx];
				idx += 1;
			}
			filename[fileidx] = '\0';
			if (!input[idx])
				import1(filename, arr);
			else
			{
				idx += 1;
				if (input[idx] == 'c' && input[idx + 1] == 's' && input[idx + 2] == 'v' && input[idx + 3] == '\0')
					import1(filename, arr);
				else
				{
					printf("extension not supported\n");
				}
			}

		}
		else if (strcmp(match, "export") == 0)
		{
			int fileidx = 0;
			while (input[idx] != '.' && input[idx] != '\0')
			{
				filename[fileidx++] = input[idx];
				idx += 1;
			}
			filename[fileidx] = '\0';
			if (!input[idx])
				export1(filename, arr);
			else
			{
				idx += 1;
				if (input[idx] == 'c' && input[idx + 1] == 's' && input[idx + 2] == 'v' && input[idx + 3] == '\0')
					export1(filename, arr);
				else
				{
					printf("extension not supported\n");
				}
			}
		}
		else if (strcmp(match, "save") == 0)
		{
			if (filename[0]!='\0')
			{
				export1(filename, arr);
			}
			else
			{
				printf("file doesnt exist\n");
			}
		}
		else if (strcmp(match, "exit") == 0)
		{
			break;
		}
		else
		{
			printf("Invalid cammand format\n");
		}
	}
}