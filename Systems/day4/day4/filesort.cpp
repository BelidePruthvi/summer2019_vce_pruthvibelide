#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void sortfile();
int comparator(const void * p, const void *q)
{
	int l = *(const int *)p;
	int r = *(const int *)q;
	return l - r;
}
void file_write(char *filename, int *a,int idx)
{
	strcat(filename, ".txt");
	FILE *fp = fopen(filename, "w");
	for (int i = 0; i < idx; i++)
	{
		fprintf(fp, "%d", a[i]);
		fprintf(fp, "%c", '\n');
	}
	fclose(fp);
}
int reverse(int num)
{
	int rev = 0;
	while (num)
	{
		rev = rev * 10 + num % 10;
		num /= 10;
	}
	return rev;
}
void write_new_file(FILE *fp1,FILE * fp2,FILE * fp3)
{
	int num1, num2;
	fscanf(fp1, "%d", &num1);
	fscanf(fp2, "%d", &num2);
	while (1)
	{
		if (num1 < num2)
		{
			fprintf(fp3, "%d", num1);
			fprintf(fp3, "%c", '\n');
			if (fscanf(fp1, "%d", &num1) == -1)
			{
				fprintf(fp3, "%d", num2);
				fprintf(fp3, "%c", '\n');
				break;
			}
		}
		else
		{
			fprintf(fp3, "%d", num2);
			fprintf(fp3, "%c", '\n');
			if (fscanf(fp2, "%d", &num2) == -1)
			{
				fprintf(fp3," %d", num1);
				fprintf(fp3, "%c", '\n');
				break;
			}

		}
	}
	while (fscanf(fp1, "%d", &num1) != -1)
	{
		fprintf(fp3, "%d", num1);
		fprintf(fp3, "%c", '\n');
	}
	while (fscanf(fp2, "%d", &num2) != -1)
	{
		fprintf(fp3, "%d", num2);
		fprintf(fp3, "%c", '\n');	
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}
void file_name_update(char filename1[20],int i)
{
	strcpy(filename1, "file");
	int num = reverse(i);
	int j = 4;
	while (num)
	{
		filename1[j++] = (num % 10) + '0';
		num /= 10;
	}
	filename1[j++] = '.';
	filename1[j++] = 't';
	filename1[j++] = 'x';
	filename1[j++] = 't';
	filename1[j++] = '\0';
}
void basic_input()
{
	int size_divide = 30000;
	int *a = (int *)malloc(size_divide * sizeof(int));
	FILE *fp;
	fopen_s(&fp, "input.txt", "r");
	if (!fp)
	{
		printf("cant open");
		return;
	}
	int idx = 0;
	int cnt = 0, j = 0;
	int start, end = 0;
	char filename[10] = "file\0";
	while (fscanf(fp, "%d", &a[idx])!=-1)
	{
		idx += 1;
		if (idx == size_divide)
		{
			qsort((void *)a, idx, sizeof(a[0]), comparator);
			cnt += 1;
			int num = reverse(cnt);
			j=4;
			while (num)
			{
				filename[j++] = (num % 10)+'0';
				num = num / 10;
			}
			filename[j] = '\0';
			printf("%s", filename);
			file_write(filename, a,idx);
			printf("%s \n", filename);
			idx = 0;
		}
	}
	if (idx != size_divide)
	{
		cnt += 1;
		int num = reverse(cnt);
		j = 4;
		while (num)
		{
			filename[j++] =( num % 10)+'0';
			num = num / 10;
		}
		filename[j] = '\0';
		file_write(filename, a, idx);
	}
	fclose(fp);
	start = 1;
	end = cnt;
	while (start<end)
	{
		int temp = cnt,i;
		for (i = start; i < end; i)
		{
			FILE *fp1, *fp2, *fp3;
			int num1, num2;
			char filename1[20];
			char filename2[20];
			char filename3[20];
			file_name_update(filename1,i);
			cnt += 1;
			fopen_s(&fp1, filename1, "r");
			if (fp1)
			{
				break;
			}
			i += 1;
			file_name_update(filename2, i);
			fopen_s(&fp2, filename2, "r");
			if (fp2)
			{
				break;
			}
			file_name_update(filename3, cnt);
			fopen_s(&fp3, filename3, "w");
			write_new_file(fp1, fp2, fp3);
			i += 1;
		}
		if (i == end)
			start = temp;
		else
			start = temp + 1;
		end = cnt;

	}

	getchar();
	getchar();
}