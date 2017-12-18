//
// Created by Garrett Battaglia on 12/18/17.
//

#include <stdlib.h>
#include <string.h>
#include "stringMinip.h"

char* lower_string(char *string)
{
	char* to_ret = (char*) calloc(sizeof(char), strlen(string));
	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] >= '\x61' && string[i] <= '\x7a'){
			to_ret[i]=string[i];
		} else {
			to_ret[i]=string[i]+0x20;
		}
	}
	return to_ret;
}