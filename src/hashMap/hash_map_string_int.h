//
// Created by Garrett Battaglia on 12/7/17.
//

#ifndef COLDBREW_HASHMAPSTRINGINT_H
#define COLDBREW_HASHMAPSTRINGINT_H

#include <stdlib.h>

struct hashmap_string_int
{
	char **key;
	int *map;
	int size;
};

struct hashmap_string_int *new_hashmap_string_int();

void add_hashmap_string_int(struct hashmap_string_int *hashmap, char *key,  int value);

int hashmap_string_int_used(struct hashmap_string_int *hashmap);

void hashmap_string_int_resize(struct hashmap_string_int *hashmap);

void hashmap_string_int_remove(struct hashmap_string_int *hashmap, char *key);

int get_hashmap_string_int(struct hashmap_string_int *hashmap, char *key);

void mod_hashmap_string_int(struct hashmap_string_int *hashmap, char *key, int value);

#endif //COLDBREW_HASHMAPSTRINGINT_H
