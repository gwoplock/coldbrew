//
// Created by Garrett Battaglia on 1/3/18.
//



#ifndef COLDBREW_FILEIO_H
#define COLDBREW_FILEIO_H

#include <stdio.h>

int read_line(char *buffer, int buf_size, FILE *file);

void create_dir(char *location);

void copy_file(FILE *in, FILE *out);

int get_first_int(FILE *file);

#endif //COLDBREW_FILEIO_H
