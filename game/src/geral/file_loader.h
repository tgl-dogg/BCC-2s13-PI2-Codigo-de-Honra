#ifndef _FILE_LOADER_H_
#define _FILE_LOADER_H_

#include <stdio.h>
#include <stdlib.h>

char ***alloc_tri_matrix(int x, int y, int z);
void free_tri_matrix(char ***M, int x, int y);
char ***load_file(const char *path, int *n);

#endif