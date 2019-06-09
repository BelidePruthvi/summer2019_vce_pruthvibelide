#include"disk.h"

void write_block(int block, void* buff)
{
	FILE* fp = fopen("harddisk.hdd", "rb+");
	fseek(fp, block * BLOCKSIZE, SEEK_SET);
	fwrite(buff, sizeof(char), BLOCKSIZE, fp);
	fclose(fp);
}

void read_block(int block, void* buff)
{
	FILE* fp = fopen("harddisk.hdd", "rb+");
	fseek(fp, block * BLOCKSIZE, SEEK_SET);
	fread(buff, sizeof(char), BLOCKSIZE, fp);
	fclose(fp);
}
void writenumber(int block,char num,int offset)
{
	FILE* fp = fopen("harddisk.hdd", "rb+");
	fseek(fp, (block * BLOCKSIZE)+offset, SEEK_SET);
	fwrite(&num, sizeof(int), 1, fp);
	fclose(fp);
}