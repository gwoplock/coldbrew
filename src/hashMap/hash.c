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
		float expon = key_size - 1 - i;
		float multcan = (int) pow(31, expon);
		hash += roundf(key[i] * multcan);
	}
	return hash;
}