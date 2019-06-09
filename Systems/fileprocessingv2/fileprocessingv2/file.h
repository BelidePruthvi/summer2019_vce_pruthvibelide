#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include"disk.h"
#include<string.h>
#include<stdlib.h>

#define BLOCKSIZE 16384
struct file{
	char file_name[20];
	unsigned int  no_of_blocks, file_length,blocknum;

};

typedef struct file File;

struct meta{
	int magic;
	File files[32];
	char harddisk[20];
	int no_of_files;
	int block_size;
	int nooofblocks;
	int freeblocks;
	bool block_available[10000];
};

typedef struct meta Meta;

void ls_of_a_file(Meta *meta);

int getfilesize1(char* file_name);

void store(Meta* meta, char* filename, char *file_stored, char*buff);

void retrieve(Meta* meta, char* filename, char *file_stored, char*buff);

void delete_a_file(Meta* meta, char* filename, char*buff);
