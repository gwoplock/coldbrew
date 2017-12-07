//
// Created by Garrett Battaglia on 12/7/17.
//

#ifndef COLDBREW_HASHMAPSTRINGINT_H
#define COLDBREW_HASHMAPSTRINGINT_H

#include <stdlib.h>

struct HashMapStringInt {
	int map[26];
};

struct HashmapStringInt* newHashMapStringInt();

#endif //COLDBREW_HASHMAPSTRINGINT_H
