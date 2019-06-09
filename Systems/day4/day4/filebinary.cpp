#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct sample
{
	char name[8];
	int marks;
	int nooffrnds;

};
void binary_file_test()
{
	FILE *fp;
	/*fopen_s(&fp, "text2.bin", "wb");
	int x = 4321;
	fwrite(&x, sizeof(x), 1, fp);
	fclose(fp);*/
	struct sample s1,s2;
	strcpy(s1.name, "pruthvi");
	s1.marks = 80;
	s1.nooffrnds = 10;
	fopen_s(&fp, "text3.bin", "wb");
	printf("%d",fwrite(&s1, sizeof(struct sample), 1, fp));
	fclose(fp);
	fopen_s(&fp, "text3.bin", "rb");
	printf("%d",fread(&s2, sizeof(struct sample), 1, fp));
	printf("%d   ", fread(&s2, sizeof(struct sample), 1, fp));
	printf("%s %d %d", s2.name, s2.marks, s2.nooffrnds);
	fclose(fp);


	system("pause"); 
	fclose(fp);
}