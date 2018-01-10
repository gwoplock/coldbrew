//
// Created by Garrett Battaglia on 1/3/18.
//

#include <stdio.h>

#ifndef COLDBREW_FILEIO_H
#define COLDBREW_FILEIO_H

int read_line(char *buffer, int buf_size, FILE *file);

void create_dir(char* location);

void copy_file(FILE* in, FILE* out);

#endif //COLDBREW_FILEIO_H
