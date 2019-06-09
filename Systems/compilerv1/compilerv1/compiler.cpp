#include<stdio.h>
#include<string.h>
struct symboltable
{
	int size;
	char name;
	int address;
};
struct block
{
	char blockname[10];
	int address;

}; 
struct intermediatecode
{
	int opcode;
	int parameters[4];
};
int datainstruction(char buff[100], struct symboltable arr[100], int *symbolsize, int address,int idx)
{
	int size;
	arr[*symbolsize].name = buff[idx];
	if (buff[idx+1] == '\n')
	{
		arr[*symbolsize].size = 1;
	}
	else if (buff[idx] == '[')
	{
		int num = 0;
		idx = idx + 1;
		while (buff[idx] != ']')
		{
			num = num * 10 + (buff[idx] - '0');
			idx += 1;
		}
		arr[*symbolsize].size = num;
	}
	arr[*symbolsize].address = address;
	*symbolsize += 1;
	return address + *symbolsize;
}
int find_symbol(char ch, struct symboltable arr[100], int symbolsize)
{
	for (int i = 0; i < symbolsize; i++)
	{
		if (arr[i].name == ch)
		{
			return i;
		}
	}
	return -1;
}
void write_arithmetic(int opcode,struct intermediatecode ic[100], char buff[100], int index,int *length_ic)
{
	ic[*length_ic].opcode = opcode;
	int j = 0;
	for (int i = index; buff[i] != '\n'; i++)
	{
		if (buff[i] >= 'A' && buff[i] <= 'H')
		{
			ic[*length_ic].parameters[j++] = buff[i] - 'A';
		}
	}
}
int getopcode(char operation1[100])
{
	if (strcmp(operation1, "EQ") == 0)
		return 8;
	else if (strcmp(operation1, "LT") == 0)
		return 9;
	else if (strcmp(operation1, "GT") == 0)
		return 10;
	else if (strcmp(operation1, "LTEQ") == 0)
		return 11;
	else if (strcmp(operation1, "GTEQ") == 0)
		return 12;
	return -1;
}
int processif(char buff[100], int idx,struct intermediatecode ic[100],int *length_ic,int stack[100],int top)
{
	ic[*length_ic].opcode = 7;
	ic[*length_ic].parameters[0] = buff[idx] - 'A';
	while (buff[idx] != ' ')
		idx += 1;
	idx += 1;
	char operation1[10];
	int j = 0;
	while (buff[idx] != ' ')
		operation1[j++] = buff[idx++];
	operation1[j] = '\0';
	ic[*length_ic].parameters[1] = getopcode(operation1);
	idx += 1;
	ic[*length_ic].parameters[2] = buff[idx]-'A';
	ic[*length_ic].parameters[3] = -10;
	stack[++top] = *length_ic;
	*length_ic += 1;
	return top;
}
int addblock(char name[100], int address, struct block blocks[100], int blocksize)
{
	strcpy(blocks[blocksize].blockname, name);
	blocks[blocksize].address = address;
	blocksize += 1;
	return blocksize;
}
void addentry(int idx, int value, struct intermediatecode ic[100])
{
	if (ic[idx].opcode == 6)
	{
		ic[idx].parameters[0] = value;
	}
	else
	{
		ic[idx].parameters[3] = value;
	}
}
int parse(char buff[100],int *address,struct intermediatecode ic[100],int length_ic,struct symboltable arr[100],int *symbolsize,int stack[100],int *top,struct block blocks[100],int *blocksize)
{
	int idx = 0;
	char operation1[10];
	int registers[8];
	for (idx = 0; buff[idx] != ' ' && buff[idx]!=':' && buff[idx]!='\0'; idx++)
	{
		operation1[idx] = buff[idx];
	}
	operation1[idx] = '\0';
	printf("operation is %s", operation1);
	while (buff[idx] == ' ')
		idx += 1;
	if (strcmp(operation1, "DATA")==0)
	{
		*address=datainstruction(buff,arr,symbolsize,*address,idx);
	}
	else if (strcmp(operation1, "CONST") == 0)
	{
		//*address = constantinstruction(buff, arr, &symbolsize, *address, idx);
	}
	else if (strcmp(operation1, "START")==0)
	{
		return length_ic;
	}
	else if (strcmp(operation1, "READ")==0)
	{
		if ((buff[idx] >= 'A' && buff[idx] <= 'H') && buff[idx + 1] == 'X' && buff[idx + 2] == '\n')
		{
			ic[length_ic].opcode = 14;
			ic[length_ic].parameters[0] = buff[idx] - 'A';
			length_ic += 1;
		}
	}
	else if (strcmp(operation1, "MOV")==0)
	{
		if ((buff[idx] >= 'A' && buff[idx] <= 'H') && buff[idx + 1] == 'X')
		{
			ic[length_ic].opcode = 2;
			ic[length_ic].parameters[0]=buff[idx] - 'A';
			idx += 3;
			ic[length_ic].parameters[1]=find_symbol(buff[idx], arr, *symbolsize);
			length_ic += 1;
		}
		else
		{
			ic[length_ic].opcode = 1;
			ic[length_ic].parameters[0] = find_symbol(buff[idx], arr, *symbolsize);
			idx += 2; 
			ic[length_ic].parameters[1] = buff[idx] - 'A';
			length_ic += 1;
		
		}
	}
	else if (strcmp(operation1, "ADD") == 0)
	{
		int opcode = 3;
		write_arithmetic(opcode, ic, buff, idx,&length_ic);
		length_ic += 1;
	}
	else if (strcmp(operation1, "SUB") == 0)
	{
		int opcode = 4;
		write_arithmetic(opcode, ic, buff, idx, &length_ic);
		length_ic += 1;
	}
	else if (strcmp(operation1, "MUL") == 0)
	{
		int opcode = 5;
		write_arithmetic(opcode, ic, buff, idx, &length_ic);
		length_ic += 1;
	}
	else if (strcmp(operation1, "END\n") == 0)
	{
		return length_ic;
	}
	else if (strcmp(operation1, "PRINT")==0)
	{
		ic[length_ic].opcode = 1;
		ic[length_ic].parameters[0] = buff[idx];
		length_ic += 1;
	}
	else if (strcmp(operation1, "IF")==0)
	{
		*top=processif(buff, idx,ic,&length_ic,stack,*top);
	}
	else if (strcmp(operation1, "ELSE\n") == 0)
	{

		int x = stack[*top];
		if (*top == 0)
			*top = -1;
		else
			*top--;
		addentry(x, length_ic, ic);
		ic[length_ic].opcode = 6;
		ic[length_ic].parameters[0] =-10;
		stack[++*top] = length_ic;
		*blocksize=addblock(operation1, length_ic,blocks,*blocksize);
		length_ic += 1;
	}
	else if (strcmp(operation1, "ENDIF\n") == 0)
	{
		int x = stack[*top];
		addentry(x, length_ic, ic);
		*top--;
	}
	else if (buff[idx] == ':')
	{
		strcpy(operation1, blocks[*blocksize].blockname);
		blocks[*blocksize].address = length_ic;
	}
	else if (strcmp(operation1, "JMP") == 0)
	{
		char temp[100],j=0;
		for (int i = idx; i != '\n'; i++)
		{
			temp[j++] = buff[i];
		}
		temp[j] = '\0';
		ic[length_ic].opcode = 6;
		for (int i = 0; i < *blocksize; i++)
		{
			if (strcmp(temp, blocks[*blocksize].blockname)== 0)
			{
				ic[length_ic].parameters[0] = blocks[*blocksize].address;
				length_ic += 1;
				break;
			}
		}
		ic[length_ic].parameters[0]=
	}
	else
	{
		printf("Invalid");
	}
	
	return length_ic;

}

void read_file()
{
	FILE *fp;
	char buff[100],ch;
	struct symboltable arr[100];
	struct block blocks[100];
	int blocksize=0;
	int symbolsize = 0;
	struct intermediatecode ic[100];
	int length_ic = 0;
	int stack[100];
	int top = -1;
	fopen_s(&fp, "input.txt", "r");
	if (!fp)
	{
		printf("cant open the file");
		getchar();
		return;
	}
	while (1)
	{
		int address = 0;
		int idx = 0;
		ch = '1';
		while (ch != '\n' && ch!=EOF)
		{
			ch = fgetc(fp);
			buff[idx++] = ch;
		}
		buff[idx] = '\0';
		printf("buff is %s\n", buff);
		length_ic=parse(buff,&address,ic,length_ic,arr,&symbolsize,stack,&top,blocks,&blocksize);
		if (ch == EOF)
			break;
	}
	fclose(fp);
	printf("length is %d\n", length_ic);
	for (int i = 0; i < length_ic; i++)
	{
		printf("%d opcode %d parameters ", i + 1, ic[i].opcode);
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", ic[i].parameters[j]);
		}
		printf("\n");
	}
	getchar();

}