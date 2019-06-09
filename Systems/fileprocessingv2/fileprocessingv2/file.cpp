#include "file.h"

int getfilesize1(char* file_name)
{
	FILE* fp = fopen(file_name, "rb");
	fseek(fp, 0, SEEK_END);
	unsigned int size = ftell(fp);
	fclose(fp);
	return size;
}

void store(Meta* metadata, char* filename, char *file_store, char*buff)
{
	int i, j, blocks, offset;
	int size = getfilesize1(filename);
	blocks = size / (BLOCKSIZE);
	if (size % (BLOCKSIZE))
		blocks++;
	if (blocks == 1)
	{
		for (i = 0; i < (100*1024*1024) / BLOCKSIZE; i++)
		{
			if (metadata->block_available[i] == 0)
			{
				printf("i is %d\n", i);
				FILE *fp = fopen(filename, "rb");
				fread(buff, 1, BLOCKSIZE, fp);
				write_block(i ,buff);
				metadata->freeblocks -= 1;
				metadata->block_available[i] = 1;
				metadata->files[metadata->no_of_files].file_length = size;
				strcpy(metadata->files[metadata->no_of_files].file_name, file_store);
				metadata->files[metadata->no_of_files].no_of_blocks = blocks;
				metadata->files[metadata->no_of_files].blocknum = i;
				metadata->no_of_files++;
				memcpy(buff, metadata, sizeof(Meta));
				write_block(0, buff);
				fclose(fp);
				return;
			}
		}
		printf("cant allocate the data for the file");
		
	}
	else
	{
		FILE *fp = fopen(filename, "rb");
		if (metadata->freeblocks < blocks+1)
		{
			printf("cant allocate the data for the file");
		}
		
		for (i = 0; i < (100*1024*1024) / BLOCKSIZE; i++)
		{
			if (metadata->block_available[i] == 0)
			{
				metadata->block_available[i] = 1;
				metadata->files[metadata->no_of_files].blocknum = i;
				strcpy(metadata->files[i].file_name, file_store);
				break;
			}
		}
		int i = 0;
		int arr[1024],idx=0;
			for (j = 0; j < (100 * 1024 * 1024)/BLOCKSIZE; j++)
			{
				if (metadata->block_available[j] == 0)
				{
					arr[idx++] = j;
					metadata->block_available[j] = 1;
					metadata->freeblocks -= 1;
					fread(buff, 1, BLOCKSIZE, fp);
					write_block(j, buff);
					i += 1;
					if (i == blocks-1)
						break;
				}
			}
		
		if (blocks == size / (BLOCKSIZE))
			offset = BLOCKSIZE;
		else
			offset = size % (BLOCKSIZE);
		for (j = 0; j < (100 * 1024 * 1024) / BLOCKSIZE; j++)
		{
			if (metadata->block_available[j] == 0)
			{
				arr[idx++] = j;
				metadata->block_available[j] = 1;
				metadata->freeblocks -= 1;
				fread(buff, 1,offset, fp);
				write_block(j, buff);
				i += 1;
				break;
			}
		}
		write_block(metadata->files[metadata->no_of_files].blocknum, arr);
		metadata->files[metadata->no_of_files].file_length = size;
		strcpy(metadata->files[metadata->no_of_files].file_name, file_store);
		metadata->files[metadata->no_of_files].no_of_blocks = blocks;
		metadata->no_of_files++;
		memcpy(buff, metadata, sizeof(Meta));
		write_block(0, buff);
		fclose(fp);

	}
}

void retrieve(Meta* metadata, char* filename, char *file_store, char* buff)
{
	int i, size, j, blocks, start;
	for (i = 0; i < metadata->no_of_files; i++)
	{
		if (!strcmp(filename, metadata->files[i].file_name))
			break;
	}
	if (i >= metadata->no_of_files)
	{
		printf("Could't retrieve the give file\n");
		return;
	}
	if (metadata->files[i].no_of_blocks == 1)
	{
		size = metadata->files[i].file_length;
		start = metadata->files[i].blocknum;
		blocks = metadata->files[i].no_of_blocks;
		FILE* fp = fopen(file_store, "wb+");
		for (i = 0; i < blocks - 1; i++)
		{
			read_block(i + start, buff);
			fwrite(buff, 1, BLOCKSIZE, fp);
		}
		if (size % (BLOCKSIZE))
		{
			read_block(i + start, buff);
			fwrite(buff, 1, size % (BLOCKSIZE), fp);
		}
		else
		{
			read_block(i + start, buff);
			fwrite(buff, 1, BLOCKSIZE, fp);
		}
		fclose(fp);
		return;
	}
	size = metadata->files[i].file_length;
	start = metadata->files[i].blocknum;
	blocks = metadata->files[i].no_of_blocks;
	FILE* fp = fopen(file_store, "wb+");
	int idx = 0;
	int arr[4096];
	idx = 0;
	read_block(start, arr);
	for (i = 0; i < blocks - 1; i++)
	{
		read_block(arr[idx], buff);
		fwrite(buff, 1, BLOCKSIZE, fp);
		idx += 1;
	}
	if (size % (BLOCKSIZE))
	{
		read_block(arr[idx], buff);
		fwrite(buff, 1, size % (BLOCKSIZE), fp);
	}
	else
	{
		read_block(arr[idx], buff);
		fwrite(buff, 1, BLOCKSIZE, fp);
	}
	fclose(fp);
}

void delete_a_file(Meta* metadata, char* filename, char*buff)
{
	int i;
	for (i = 0; i < metadata->no_of_files; i++)
	{
		if (strcmp(metadata->files[i].file_name, filename) == 0)
			break;
	}
	if (i == metadata->no_of_files)
	{
		printf("file doesnt exists");
		return;
	}
	int start = metadata->files[i].blocknum;
	int end = metadata->files[i].no_of_blocks;
	metadata->files[i] = metadata->files[metadata->no_of_files - 1];
	metadata->no_of_files--;
	for (i = start; i < end - 1; i++)
	{
		metadata->block_available[i] = 0;
	}
	memcpy(buff, metadata, sizeof(Meta));
	write_block(0, buff);
}

void ls_of_a_file(Meta *meta)
{
	for (int i = 0; i < meta->no_of_files; i++)
	{
		printf("%s\n", meta->files[i].file_name);
	}
}