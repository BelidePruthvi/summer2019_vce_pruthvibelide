#include "input.h"

void start_fileprocessing()
{
	Meta *meta = (Meta*)calloc(1, sizeof(Meta));
	char buff[BLOCKSIZE];

	char command[10], filename[20], file_stored[20];
	int i;
	while (1)
	{
		read_block(0, buff);
		memcpy(meta, buff, sizeof(Meta));
		printf("> ");
		scanf("%s", &command);
		
		if (!strcmp(command, "format"))
		{
			int blocksize;
			scanf("%d", &blocksize);
			meta = (Meta*)calloc(1, sizeof(Meta));
			meta->magic = 1234;
			meta->block_size = blocksize;
			meta->freeblocks = (100 * 1024 * 1024) / blocksize;
			strcpy(meta->harddisk,"sample.hdd");
			meta->block_available[0] = 1;
			memcpy(buff, meta, sizeof(Meta));
			write_block(0, buff);
		}

		else if (strcmp(command, "copytoFS") == 0)
		{
			scanf("%s", &filename);
			scanf("%s", &file_stored);
			store(meta, filename, file_stored, buff);
		}

		else if (strcmp(command, "copyfromFS") == 0)
		{
			scanf("%s", &filename);
			scanf("%s", &file_stored);
			retrieve(meta, filename, file_stored, buff);
		}

		else if (strcmp(command, "delete") == 0)
		{
			scanf("%s", &filename);
			delete_a_file(meta, filename, buff);
		}
		else if (strcmp(command, "ls") == 0)
		{
			ls_of_a_file(meta);
		}
		else if (strcmp(command, "exit") == 0)
		{
			break;
		}

		else
		{
			printf("Invalid command format\n");
		}

	}
}