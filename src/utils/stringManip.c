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
	char *ret = path;
	for (int i = 0; i < strlen(path); i++) {
		if (path[i] == '\\' || path[i] == '/') {
			ret = &path[i + 1];
		}
	}
	return ret;
}

//This looks like it works but it might not
char **string_split(char *to_split, char delim)
{
	int spl_ind = -1;
	for (int i = 0; i < strlen(to_split); i++) {
		if (to_split[i] == delim) {
			spl_ind = i;
			break;
		}
	}
	if (spl_ind == -1) {
		return NULL;
	}
	char **ret = calloc(2, sizeof(char *));
	ret[0] = to_split;
	ret[0][spl_ind] = '\0';
	ret[1] = to_split + spl_ind + 1;
	return ret;
}