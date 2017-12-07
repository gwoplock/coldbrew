//
// Created by Garrett Battaglia on 12/7/17.
//

#ifndef COLDBREW_COMMANDLINEPARSER_H
#define COLDBREW_COMMANDLINEPARSER_H

#include "../hashMap/hash_map_string_int.h"

extern struct hashmap_string_int* command_line_args;

void parseCommandLine(int argc, char **argv);

#endif //COLDBREW_COMMANDLINEPARSER_H
