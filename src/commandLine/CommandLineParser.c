//
// Created by Garrett Battaglia on 12/7/17.
//

#include <stdio.h>
#include <unistd.h>
#include "CommandlineParser.h"
#include "../utils/stringMinip.h"

struct hashmap_string_int *command_line_args;

struct configuration config;

void parseCommandLine(int argc, char **argv)
{
	command_line_args = new_hashmap_string_int();
	for (int i = 0; i < argc; i++) {
		char *arg = lower_string(argv[i]);

		//if it hasn't been added add it.
		if (get_hashmap_string_int(command_line_args, arg) == 0) {
			add_hashmap_string_int(command_line_args, arg, 1);
		} else {
			//increase the count if it exists
			mod_hashmap_string_int(command_line_args, arg,
			                       get_hashmap_string_int(command_line_args, arg) + 1);
		}
	}
}

void set_mode()
{
	if (hashmap_string_int_contains(command_line_args, "install")) {
		config.selected_mode = INSTALL;
	}
	if (hashmap_string_int_contains(command_line_args, "upgrade")) {
		config.selected_mode = UPGRADE;
	}
	if (hashmap_string_int_contains(command_line_args, "update")) {
		config.selected_mode = UPDATE;
	}
	if (hashmap_string_int_contains(command_line_args, "sync")) {
		config.selected_mode = SYNC;
	}
	if (hashmap_string_int_contains(command_line_args, "query")) {
		fprintf(stderr, "Mode query isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "search")) {
		fprintf(stderr, "Mode search isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "uninstall")) {
		config.selected_mode = UNINSTALL;
	}
	if (hashmap_string_int_contains(command_line_args, "build")) {
		config.selected_mode = BUILD;
	}
	if (hashmap_string_int_contains(command_line_args, "check")) {
		config.selected_mode = CHECK;
	}
	if (hashmap_string_int_contains(command_line_args, "help")) {
		config.selected_mode = HELP;
	}
}

void set_options()
{
	if (isatty(fileno(stdout))) {
		config.brew_opts.color = 1;
	} else {
		config.brew_opts.color = 0;
	}

	config.brew_opts.verbosity = 0;
	config.brew_opts.confirm = 1;
	config.brew_opts.sync = 1;

	if (hashmap_string_int_contains(command_line_args, "no-color")) {
		config.brew_opts.color = 0;
	}
	if (hashmap_string_int_contains(command_line_args, "color")) {
		config.brew_opts.color = 1;
	}
	if (hashmap_string_int_contains(command_line_args, "verbose")) {
		config.brew_opts.verbosity = 1;
	}
	if (hashmap_string_int_contains(command_line_args, "debug")) {
		config.brew_opts.verbosity = 2;
	}
	if (hashmap_string_int_contains(command_line_args, "no-confirm")) {
		config.brew_opts.confirm = 0;
	}
	if (hashmap_string_int_contains(command_line_args, "confirm")) {
		config.brew_opts.confirm = 1;
	}
	if (hashmap_string_int_contains(command_line_args, "no-sync")) {
		config.brew_opts.sync = 0;
	}
}

void set_mode_options()
{
	switch (config.selected_mode) {
		case INSTALL: {
			config.mode_opts = calloc(1, sizeof(struct install_options));
			break;
		}
		case UPGRADE: {
			config.mode_opts = calloc(1, sizeof(struct upgrade_options));
			break;
		}
		case UPDATE: {
			config.mode_opts = NULL;
			break;
		}
		case SYNC: {
			config.mode_opts = NULL;
			break;
		}
		case UNINSTALL: {
			config.mode_opts = calloc(1, sizeof(struct uninstall_options));
			break;
		}
		case BUILD: {
			config.mode_opts = calloc(1, sizeof(struct build_options));
			break;
		}
		case CHECK: {
			config.mode_opts = calloc(1, sizeof(struct check_options));
			break;
		}
		case HELP: {
			config.mode_opts = NULL;
			break;
		}
		default: {
			fprintf(stderr, "Something went very wrong in parsing the commandline options.");
			unlock();
			exit(3);
		}
	}
}