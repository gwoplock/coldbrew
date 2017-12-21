//
// Created by Garrett Battaglia on 12/7/17.
//

#include <stdio.h>
#include <unistd.h>
#include "CommandlineParser.h"
#include "../utils/stringMinip.h"
#include "../utils/print.h"

struct hashmap_string_int *command_line_args;

struct configuration config;


/***
 * inserts all elements into hashmap
 * @param argc
 * @param argv
 */
void parseCommandLine(int argc, char **argv)
{
	int end_index = parse_brew_opts(argc, argv) /*+ 1; //this + 1 may be needed*/;
	read_mode(argc, argv, end_index);
	end_index = parse_mode_opts(argc, argv, end_index + 1/*may be a +2*/)/*+ 1; //this + 1 may be needed*/;
	parse_targets(argc, argv, end_index);
}

int parse_brew_opts(int argc, char **argv)
{
	int i;
	for (i = 0; i < argc && argv[i][0] == '-' && argv[i][0] == '-'; i++) {

	}
	return i;
}

void read_mode(int argc, char **argv, int index)
{

}

int parse_mode_opts(int argc, char **argv, int start_index)
{

}

void parse_targets(int argc, char **argv, int start_index)
{

}