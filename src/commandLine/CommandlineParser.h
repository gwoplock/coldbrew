//
// Created by Garrett Battaglia on 12/7/17.
//

#ifndef COLDBREW_COMMANDLINEPARSER_H
#define COLDBREW_COMMANDLINEPARSER_H

#include "../hashMap/hash_map_string_int.h"

extern struct hashmap_string_int *command_line_args;

extern struct configuration config;

enum mode
{
	INSTALL, UPGRADE, UPDATE, SYNC, UNINSTALL, BUILD, CHECK, HELP
};

struct brew_options
{
	int color;
	int verbosity;
	int confirm;
	int sync;
};

struct configuration
{
	enum mode selected_mode;
	struct brew_options brew_opts;
	struct mode_options *mode_opts;
};


void parseCommandLine(int argc, char **argv);

void set_mode();

void set_options();

void set_mode_options();

#endif //COLDBREW_COMMANDLINEPARSER_H
