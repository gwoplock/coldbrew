//
// Created by Garrett Battaglia on 1/3/18.
//

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