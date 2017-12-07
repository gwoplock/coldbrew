//
// Created by Garrett Battaglia on 12/7/17.
//

#include "HashMapStringInt.h"

struct HashmapStringInt* newHashMapStringInt(){
	return (struct HashmapStringInt*) malloc(sizeof(struct HashMapStringInt));
}
