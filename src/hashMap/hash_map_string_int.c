//
// Created by Garrett Battaglia on 12/7/17.
//

#include <string.h>
#include "hash_map_string_int.h"
#include "hash.h"

struct hashmap_string_int *new_hashmap_string_int()
{
	struct hashmap_string_int *tmp = (struct hashmap_string_int *) calloc(1, sizeof(struct hashmap_string_int));
	int *tmp_map = (int *) calloc(26, sizeof(int));
	char **tmp_key = (char **) calloc(26, sizeof(char*));
	tmp->map = tmp_map;
	tmp->size = 26;
	tmp->key = tmp_key;
	return tmp;
}

void add_hashmap_string_int(struct hashmap_string_int *hashmap, char *key, int value)
{
	int hash = hash_string(key);
	int index = hash % 26;
	if (hashmap->map[index] == 0) {
		hashmap->map[index] = value;
		hashmap->key[index] = key;
	} else {
		//TODO side chaining
	}

	if (hashmap_string_int_used(hashmap) > 75) {
		hashmap_string_int_resize(hashmap);
	}
}

int hashmap_string_int_used(struct hashmap_string_int *hashmap)
{
	//todo
}


void hashmap_string_int_resize(struct hashmap_string_int *hashmap)
{
	hashmap->map = (int *) realloc(hashmap->map, hashmap->size * 2 * sizeof(int));
	memset(hashmap->map + hashmap->size / 2, 0, hashmap->size / 2);
	hashmap->size *= 2;
	for (int i = 0; i < hashmap->size / 2; i++) {
		if (hashmap->map[i] != 0) {
			char* key = hashmap->key[i];
			int hash = hash_string(key);
			int index = hash % 26;
			if (hashmap->map[index] == 0) {
				hashmap->map[index] = hashmap->map[i];
				hashmap->key[index] = key;
			} else {
				//TODO side chaining
			}
		}
	}
}


