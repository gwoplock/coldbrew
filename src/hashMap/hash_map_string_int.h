//
// Created by Garrett Battaglia on 12/7/17.
//

#ifndef COLDBREW_HASHMAPSTRINGINT_H
#define COLDBREW_HASHMAPSTRINGINT_H

#include <stdlib.h>

struct hashmap_string_int {
	int map[26];
};

struct hashmap_string_int* new_hashmap_string_int();

#endif //COLDBREW_HASHMAPSTRINGINT_H
