//
// Created by Garrett Battaglia on 12/7/17.
//

#include "hash_map_string_int.h"
#include "hash.h"

struct hashmap_string_int* new_hashmap_string_int(){
	return (struct hashmap_string_int*) malloc(sizeof(struct hashmap_string_int));
}

void add_hashmap_string_int(struct hashmap_string_int* hashmap, char* key, int key_size, int value){
	int index = hash_string(key, key_size);
	hashmap->map[index] = value;
}