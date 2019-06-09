#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define BLOCKSIZE 16384

void write_block(int block, void* buff);

void read_block(int block, void* buff);

void writenumber(int block, char num, int offset);