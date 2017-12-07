//
// Created by Garrett Battaglia on 12/7/17.
//

#include <printf.h>
#include "CommandlineParser.h"

struct hashmap_string_int* command_line_args;

void parseCommandLine(int argc, char **argv)
{
	command_line_args = new_hashmap_string_int();
	for (int i = 0; i < argc; i++){
		char* arg = argv[i];
		mod_hashmap_string_int(command_line_args, arg, get_hashmap_string_int(command_line_args, arg)+1);
	}
}