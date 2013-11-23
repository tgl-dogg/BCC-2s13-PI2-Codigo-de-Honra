#ifndef _FILE_LOADER_H_
#define _FILE_LOADER_H_

#include <stdio.h>
#include <stdlib.h>

char ***alloc_text (int x, int y, int z);
void free_text (char ***M, int x, int y);

void limpa (FILE *entrada, char t);
char ***load_file (const char *path);
#endif