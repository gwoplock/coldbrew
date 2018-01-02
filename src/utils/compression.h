//
// Created by Garrett Battaglia on 1/1/18.
//

#include <stdio.h>

#ifndef COLDBREW_COMPRESSION_H
#define COLDBREW_COMPRESSION_H

int decompress(FILE *in, FILE *out);

int decompress_gzip(FILE *in, FILE* out);

#endif //COLDBREW_COMPRESSION_H
