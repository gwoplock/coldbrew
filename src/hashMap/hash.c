//
// Created by Garrett Battaglia on 12/7/17.
//

#include "hash.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
/**
 * hashes a string based off java's string hash
 * @param key: value to hash
 * @return hash, absolute value of 32 bit int
 */
int hash_string(char *key)
{
	//using java's string hash function, sum(s[i]*31^(n-1-i), where i is the current index and n is the length of the string
	int key_size = strlen(key);
	int hash = 0;
	for (int i = 0; i < key_size; i++) {
		float expon = key_size - 1 - i;
		float multcan = (int) pow(31, expon);
		hash += roundf(key[i] * multcan);
	}
	return abs(hash);
}