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
		dbfprintf(NORMAL, stderr, "Mode upgrade isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "update")) {
		config.selected_mode = UPDATE;
		dbfprintf(NORMAL, stderr, "Mode update isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "sync")) {
		config.selected_mode = SYNC;
		dbfprintf(NORMAL, stderr, "Mode sync isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "query")) {
		config.selected_mode = QUERY;
		dbfprintf(NORMAL, stderr, "Mode query isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "search")) {
		config.selected_mode = SEARCH;
		dbfprintf(NORMAL, stderr, "Mode search isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "uninstall")) {
		config.selected_mode = UNINSTALL;

	}
	if (hashmap_string_int_contains(command_line_args, "build")) {
		config.selected_mode = BUILD;
		dbfprintf(NORMAL, stderr, "Mode build isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "check")) {
		config.selected_mode = CHECK;
		dbfprintf(NORMAL, stderr, "Mode check isn't supported yet");
		unlock();
		exit(2);
	}
	if (hashmap_string_int_contains(command_line_args, "help")) {
		config.selected_mode = HELP;
		dbfprintf(NORMAL, stderr, "Mode help isn't supported yet");
		unlock();
		exit(2);
	}
}

void set_options()
{
	if (isatty(fileno(stdout))) {
		config.brew_opts.color = 1;
	} else {
		config.brew_opts.color = 0;
	}

#ifdef DEV
	config.brew_opts.verbosity = DEBUG;
#else
	config.brew_opts.verbosity = NORMAL;
#endif
	config.brew_opts.confirm = 1;
	config.brew_opts.sync = 1;

	if (hashmap_string_int_contains(command_line_args, "no-color")) {
		config.brew_opts.color = 0;
	}
	if (hashmap_string_int_contains(command_line_args, "color")) {
		config.brew_opts.color = 1;
	}
	if (hashmap_string_int_contains(command_line_args, "verbose")) {
		config.brew_opts.verbosity = VERBOSE;
	}
	if (hashmap_string_int_contains(command_line_args, "debug")) {
		config.brew_opts.verbosity = DEBUG;
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
			if (hashmap_string_int_contains(command_line_args, "local")) {
				((struct install_options *) (config.mode_opts))->local = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "no-deps")) {
				((struct install_options *) (config.mode_opts))->no_deps = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "force")) {
				((struct install_options *) (config.mode_opts))->force = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "needed")) {
				((struct install_options *) (config.mode_opts))->needed = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "as-dep")) {
				((struct install_options *) (config.mode_opts))->as_dep = 1;
				fprintf(stderr, "as-dep is not supported yet");
				exit(4);
			}
			if (hashmap_string_int_contains(command_line_args, "as-expl")) {
				((struct install_options *) (config.mode_opts))->as_expl = 1;
				((struct install_options *) (config.mode_opts))->as_dep = 0;

			}
			break;
		}
		case UPGRADE: {
			config.mode_opts = calloc(1, sizeof(struct upgrade_options));
			if (hashmap_string_int_contains(command_line_args, "force")) {
				((struct upgrade_options *) (config.mode_opts))->force = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "no-save")) {
				((struct upgrade_options *) (config.mode_opts))->no_save = 1;
			}
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
			if (hashmap_string_int_contains(command_line_args, "no-deps")) {
				((struct uninstall_options *) (config.mode_opts))->no_deps = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "cascade")) {
				((struct uninstall_options *) (config.mode_opts))->cascade = 1;
				config.brew_opts.confirm = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "no-save")) {
				((struct uninstall_options *) (config.mode_opts))->no_save = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "recursive")) {
				((struct uninstall_options *) (config.mode_opts))->recursive = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "recursive-strong")) {
				((struct uninstall_options *) (config.mode_opts))->recursive = 2;
				config.brew_opts.confirm = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "unneeded")) {
				((struct uninstall_options *) (config.mode_opts))->unneeded = 1;
			}
			break;
		}
		case BUILD: {
			config.mode_opts = calloc(1, sizeof(struct build_options));
			if (hashmap_string_int_contains(command_line_args, "local")) {
				((struct build_options *) (config.mode_opts))->local = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "force")) {
				((struct build_options *) (config.mode_opts))->force = 1;
			}
			break;
		}
		case CHECK: {
			config.mode_opts = calloc(1, sizeof(struct check_options));
			if (hashmap_string_int_contains(command_line_args, "local")) {
				((struct check_options *) (config.mode_opts))->local = 1;
			}
			if (hashmap_string_int_contains(command_line_args, "package")) {
				((struct check_options *) (config.mode_opts))->check_type = PACKAGE;
			}
			if (hashmap_string_int_contains(command_line_args, "script")) {
				((struct check_options *) (config.mode_opts))->check_type = SCRIPT;
			}
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
	print_mode_options();
}

void print_mode_options()
{
	switch (config.selected_mode) {
		case INSTALL : {
			dbprintf(VERBOSE,
			         " local: %i \n no-deps: %i \n force: %i \n needed: %i \n as-dep: %i \n as-expl: %i \n",
			         ((struct install_options *) (config.mode_opts))->local,
			         ((struct install_options *) (config.mode_opts))->no_deps,
			         ((struct install_options *) (config.mode_opts))->force,
			         ((struct install_options *) (config.mode_opts))->needed,
			         ((struct install_options *) (config.mode_opts))->as_dep,
			         ((struct install_options *) (config.mode_opts))->as_expl);
			break;
		}
		case UPGRADE: {
			dbprintf(VERBOSE, " force: %i, no-save: %i",
			         ((struct upgrade_options *) (config.mode_opts))->force,
			         ((struct upgrade_options *) (config.mode_opts))->no_save);
			break;
		}
		case UNINSTALL: {
			dbprintf(VERBOSE,
			         " no-deps: %i \n cascade: %i \n no-save: %i \n recursive: %i \n unneeded: %i \n",
			         ((struct uninstall_options *) (config.mode_opts))->no_deps,
			         ((struct uninstall_options *) (config.mode_opts))->cascade,
			         ((struct uninstall_options *) (config.mode_opts))->no_save,
			         ((struct uninstall_options *) (config.mode_opts))->recursive,
			         ((struct uninstall_options *) (config.mode_opts))->unneeded);
			break;
		}
		case BUILD: {
			dbprintf(VERBOSE, " local: %i \n force: %i \n",
			         ((struct build_options *) (config.mode_opts))->local,
			         ((struct build_options *) (config.mode_opts))->force);
			break;
		}
		case CHECK: {
			dbprintf(VERBOSE, " local: %i \n type: %i \n",
			         ((struct check_options *) (config.mode_opts))->local,
			         ((struct check_options *) (config.mode_opts))->check_type);
			break;
		}

		default: {
			dbprintf(DEBUG, "Selected mode doesn't have options \n");
		}
	}
	printf("----------------------------------\n");
}

void back_print_options()
{
	// command line parsing testcode
	dbprintf(VERBOSE, "----------------------------------\n");
	for (int i = 0; i < command_line_args->size; i++) {
		dbprintf(DEBUG, " %i: %s -> %i\n", i, command_line_args->key[i], command_line_args->map[i]);
	}
	dbprintf(DEBUG, "---------------------------------- \n");
	dbprintf(VERBOSE, " mode is %i \n", config.selected_mode);
	dbprintf(VERBOSE, "---------------------------------- \n");
	dbprintf(VERBOSE, " color: %i \n verbosity: %i \n confirm: %i \n sync: %i \n", config.brew_opts.color,
	         config.brew_opts.verbosity, config.brew_opts.confirm, config.brew_opts.sync);
	dbprintf(VERBOSE, "----------------------------------\n");

}