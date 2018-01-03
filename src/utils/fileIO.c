//
// Created by Garrett Battaglia on 1/3/18.
//

#include "fileIO.h"

int read_line(char* buffer, int buf_size, FILE* file){
	char last_read ='\0';
	for(int i = 0; i< buf_size && last_read != '\n'; i++){
		buffer[i] = last_read;
		last_read = getc(file);
	}
}