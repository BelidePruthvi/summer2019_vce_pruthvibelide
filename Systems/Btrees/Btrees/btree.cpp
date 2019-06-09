#include<stdio.h>
#include<string.h>
struct leafpage
{
	char pagetype;
	char unused[4];
	char studentname[3][5];
	int studentid[3];
};
struct nonleafpage
{
	char pagetype;
	char unused[3];
	int childpageid[4];
	int value[3];
};
struct pages
{
	char pagebuffer[32];
	bool used;
	int timestamp;
	int pageid;
};
void query()
{
	struct leafpage studentleaf;
	FILE *fp = fopen("output1.txt", "r");
	fseek(fp, 32 * 4, SEEK_SET);
	char buff[100];
	struct nonleafpage student_nonleaf;
	fread(&student_nonleaf, sizeof(struct nonleafpage), 1, fp);
	for (int i = 0; i < 4; i++)
	{
		printf("value is %d pageno is %d\n", student_nonleaf.value[i],student_nonleaf.childpageid[i]);
	}
	int query;
	while (1)
	{
		printf("enter the query value");
		scanf("%d", &query);
		int pageno=-1;
		for (int i = 0; i < 3; i++)
		{
			if (i == 0 && student_nonleaf.value[i]>query)
			{
				pageno = i;
				break;
			}
			else if (i == 3 && student_nonleaf.value[i] <= query)
			{
				pageno = i + 1;
				break;
			}
			else if (student_nonleaf.value[i] <= query && student_nonleaf.value[i + 1] > query)
			{
				pageno = i + 1;
				break;
			}
		}
		if (pageno == -1)
		{

		}
		else
		{
			fseek(fp, 32 * pageno, SEEK_SET);
			fread(&studentleaf, sizeof(leafpage), 1, fp);
			memcpy(buff, &studentleaf, 32);
			if (buff[0] == '1')
			{
				struct leafpage temp;
				memcpy(&temp, buff, 32);

			}
		}
	}
}
void start_storing()
{
	struct leafpage student[4],student1[4];
	struct nonleafpage student_nonleaf;
	int rno;
	char name[5];
	int noofelements = 0;
	int i = 0;
	FILE *fp1 = fopen("input.txt", "r");
	printf("leaf is %d non leaf is %d\n", sizeof(struct leafpage), sizeof(nonleafpage));
	while (i < 4)
	{
		student[i].pagetype = '1';
		for (int j = 0; j < 3; j++)
		{
			fscanf(fp1,"%d %s", &rno, name);
			student[i].studentid[j] = rno;
			strcpy(student[i].studentname[j], name);
		}
		i += 1;
	}
	fclose(fp1);
	FILE *fp;
	fopen_s(&fp, "output1.txt", "wb");
	fwrite(student, sizeof(leafpage), 4, fp);
	i = 1;
	student_nonleaf.pagetype = '2';
	student_nonleaf.childpageid[0] = 0;
	while (i < 4)
	{
		student_nonleaf.childpageid[i] = i;
		student_nonleaf.value[i-1] = student[i].studentid[0];
		i++;
	}
	fwrite(&student_nonleaf,sizeof(nonleafpage),1,fp);
	char ch;
	fclose(fp);
	FILE *fp2;
	fopen_s(&fp2, "output1.txt", "rb");
	fread(&ch, sizeof(char), 1, fp2);
	if (ch == '1')
	{
		fseek(fp, 0, SEEK_SET);
		fread(student1, sizeof(leafpage), 4, fp2);
		int i = 0;
		while (i < 4)
		{
			for (int j = 0; j < 3; j++)
			{
				printf("rno %d name %s\n",student1[i].studentid[j],student1[i].studentname[j]);
			}
			i += 1;
		}
	}
	else
	{
		printf("not ");
	}
	query();
	fclose(fp2);
	getchar();

}