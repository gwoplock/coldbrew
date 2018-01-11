//
// Created by Garrett Battaglia on 1/3/18.
//

#include <sys/stat.h>
#include <stdlib.h>
#include "fileIO.h"
#include "print.h"

int read_line(char *buffer, int buf_size, FILE *file)
{
	char last_read = '\0';
	for (int i = 0; i < buf_size && last_read != '\n'; i++) {
		if (last_read != '\0') {
			buffer[i - 1] = last_read;
		}
		last_read = getc(file);
		if (last_read == EOF) {
			return -1;
		}
		dbprintf(DEBUG, "just read: %c \n", last_read);
	}
	dbprintf(DEBUG, "exited loop with char: %c\n", last_read);
	if (last_read == '\n') {
		return 1;
	} else {
		return 0;
	}
}

void create_dir(char *location)
{
	struct stat st = {0};
	if (stat(location, &st) == -1) {
		volatile int ret = mkdir(location, 0700);
		volatile int foo = 10;
	}
}

void copy_file(FILE *in, FILE *out)
{
	char ch;
	while ((ch = fgetc(in)) != EOF) {
		fputc(ch, out);
	}
}

/**
 * gets the first int (4 bytes) from the file, may be moved to utils
 * @param file: FILE* to file
 * @return first 4 bytes. c
 */
int get_first_int(FILE *file)
{
	//create an int to hold the file
	int *ret = calloc(1, sizeof(int));
	//read a byte at a time because fuck endiness
	for (int i = 0; i < 3; i++) {
		fread(ret, 1, 1, file);
		*ret = *ret << 8;
	}
	//read lasy byte b/c dont want to shift
	fread(ret, 1, 1, file);
	//return
	return *ret;
}