//
// Created by Garrett Battaglia on 12/7/17.
//

#include "hash.h"
#include <math.h>
#include <string.h>

int hash_string(char *key)
{
	int key_size = strlen(key);
	int hash = 0;
	for (int i = 0; i < key_size; i++) {
		int expon = (key_size - 1) - 1 - i;
		int multcan = (int) pow(31, expon);
		hash += key[i] * multcan;
	}
	return hash;
}