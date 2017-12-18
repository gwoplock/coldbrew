//
// Created by Garrett Battaglia on 12/7/17.
//

#include <string.h>
#include <math.h>
#include <printf.h>
#include "hash_map_string_int.h"
#include "hash.h"

struct hashmap_string_int *new_hashmap_string_int()
{
	//create struct
	struct hashmap_string_int *tmp = (struct hashmap_string_int *) calloc(1, sizeof(struct hashmap_string_int));
	//create map
	int *tmp_map = (int *) calloc(26, sizeof(int));
	//create the key array
	char **tmp_key = (char **) calloc(26, sizeof(char *));
	tmp->map = tmp_map;
	//base size is 26
	tmp->size = 26;
	tmp->key = tmp_key;
	return tmp;
}

void add_hashmap_string_int(struct hashmap_string_int *hashmap, char *key, int value)
{
	int hash = hash_string(key);
	int index = hash % hashmap->size;
	//if element is empty
	if (hashmap->map[index] == 0) {
		hashmap->map[index] = value;
		hashmap->key[index] = key;
	} else {
		//TODO side chaining
	}
	//check size and resize if needed
	if (hashmap_string_int_used(hashmap) > 75) {
		hashmap_string_int_resize(hashmap);
	}
}

int hashmap_string_int_used(struct hashmap_string_int *hashmap)
{
	int used = 0;
	//count non-empty elements
	for (int i = 0; i < hashmap->size; i++) {
		if (hashmap->map[i] != 0) {
			used++;
		}
	}
	return round(((double)used / (double)hashmap->size) * 100);
}


void hashmap_string_int_resize(struct hashmap_string_int *hashmap)
{
	int *old_map = hashmap->map;
	char **old_key_arr = hashmap->key;
	int old_size = hashmap->size;

	hashmap->map = (int *) calloc(old_size * 2, sizeof(int));
	hashmap->key = (char **) calloc(old_size * 2, sizeof(char *));
	hashmap->size = old_size * 2;

	for (int i = 0; i < old_size; i++) {
		int old_val = old_map[i];
		char *old_key = old_key_arr[i];
		if (old_val != 0/*TODO check for side chaining*/) {
			int index = hash_string(old_key) % hashmap->size;
			if(hashmap->map[index] == 0) {
				hashmap->key[index] = old_key;
				hashmap->map[index] = old_val;
			} else{
				//TODO side chaining
			}
		}
	}

	free(old_map);
	free(old_key_arr);


	/*//resize
	hashmap->map = (int *) realloc(hashmap->map, hashmap->size * 2 * sizeof(int));
	hashmap->size *= 2;
	//clear the mem
	memset(hashmap->map + hashmap->size / 2, 0, (hashmap->size / 2)* sizeof(int));
	//rehash and clear old elements
	for (int i = 0; i < hashmap->size / 2; i++) {
		if (hashmap->map[i] != 0) {

			int val = hashmap->map[i];
			char *key = hashmap->key[i];
			int hash = hash_string(key);
			int index = hash % hashmap->size;

			if (todo side chanined  1) {
				hashmap->map[i] = 0;
				hashmap->key[i] = "";
			}

			if (hashmap->map[index] == 0 1) {
				hashmap->map[index] = val;
				hashmap->key[index] = key;
			} else {
				//TODO side chaining
			}

		}
	}*/
}

void hashmap_string_int_remove(struct hashmap_string_int *hashmap, char *key)
{
	int index = hash_string(key) % hashmap->size;
	if (/*todo side chanined */ 1) {
		hashmap->map[index] = 0;
		hashmap->key[index] = "";
	}
}

int get_hashmap_string_int(struct hashmap_string_int *hashmap, char *key)
{
	int index = hash_string(key) % hashmap->size;
	if (/*todo side chanined */ 1) {
		return hashmap->map[index];
	}
}

void mod_hashmap_string_int(struct hashmap_string_int *hashmap, char *key, int value)
{
	int index = hash_string(key) % hashmap->size;
	if (/*todo side chanined */ 1) {
		hashmap->map[index] = value;
		hashmap->key[index] = key;
	}
}

int hashmap_string_int_contains(struct hashmap_string_int* hashmap, char* search){
	int index = hash_string(search) % hashmap->size;
	if (/*todo side chained*/ 1 ){
		if (hashmap->key[index] != 0 && !strcmp(hashmap->key[index],search)){
			return 1;
		} else {
			return 0;
		}
	} else {

	}
}