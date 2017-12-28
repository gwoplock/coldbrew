//
// Created by Garrett Battaglia on 12/18/17.
//

#include <stdlib.h>
#include <string.h>
#include "stringManip.h"

/**
 * converts a char* to all lowercase
 * @param string: char* to turn to lowercase
 * @return lowercase string
 */
char *lower_string(char *string)
{
	// +1 so that there's the null termintor
	char *ret = calloc(strlen(string) + 1, sizeof(char));
	int cx;

	for (cx = 0; cx < strlen(string); cx++) {
		if (string[cx] > 0x40 && string[cx] < 0x5B) {
			ret[cx] = string[cx] + 0x20;
		} else {
			ret[cx] = string[cx];
		}
	}
	return ret;
}

char *strip_path(char *path)
{
	return "foo";
}