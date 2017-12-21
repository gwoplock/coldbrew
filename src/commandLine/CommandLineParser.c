//
// Created by Garrett Battaglia on 12/7/17.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CommandlineParser.h"
#include "../utils/print.h"


struct configuration config;

struct target *targets;

int num_of_targets;

int max_targets = 10;

/***
 * inserts all elements into hashmap
 * @param argc
 * @param argv
 */
void parseCommandLine(int argc, char **argv)
{
	int end_index = parse_brew_opts(argc, argv) /*+ 1; //this + 1 may be needed*/;
	print_brew_opts();
	read_mode(argc, argv, end_index);
	print_mode();
	end_index = parse_mode_opts(argc, argv, end_index + 1/*may be a +2*/)/*+ 1; //this + 1 may be needed*/;
	print_mode_opts();
	parse_targets(argc, argv, end_index);
	print_targets();
}

int parse_brew_opts(int argc, char **argv)
{
	int i;
	for (i = 1; i < argc && argv[i][0] == '-' && argv[i][0] == '-'; i++) {
		if (strcmp(argv[i], "--color") == 0) {
			config.brew_opts.color = 1;
		} else if (strcmp(argv[i], "--no-color") == 0) {
			config.brew_opts.color = 0;
		} else if (strcmp(argv[i], "--verbose") == 0) {
			config.brew_opts.verbosity = VERBOSE;
		} else if (strcmp(argv[i], "--debug") == 0) {
			config.brew_opts.verbosity = DEBUG;
		} else if (strcmp(argv[i], "--no-confirm") == 0) {
			config.brew_opts.confirm = 0;
		} else if (strcmp(argv[i], "--confirm") == 0) {
			config.brew_opts.confirm = 1;
		} else if (strcmp(argv[i], "--no-sync") == 0) {
			config.brew_opts.sync = 0;
		} else if (strcmp(argv[i], "--sync") == 0) {
			config.brew_opts.sync = 1;
		} else {
			//bad arg
		}
	}
	return i;
}

void read_mode(int argc, char **argv, int index)
{
	if (index < argc - 1) {
		char *arg = argv[index];
		if (strcmp(arg, "install") == 0) {
			config.selected_mode = INSTALL;
		} else if (strcmp(arg, "upgrade") == 0) {
			config.selected_mode = UPGRADE;
		} else if (strcmp(arg, "update") == 0) {
			config.selected_mode = UPDATE;
		} else if (strcmp(arg, "sync") == 0) {
			config.selected_mode = SYNC;
		} else if (strcmp(arg, "uninstall") == 0) {
			config.selected_mode = UNINSTALL;
		} else if (strcmp(arg, "build") == 0) {
			config.selected_mode = BUILD;
		} else if (strcmp(arg, "check") == 0) {
			config.selected_mode = CHECK;
		} else if (strcmp(arg, "help") == 0) {
			config.selected_mode = HELP;
		} else if (strcmp(arg, "search") == 0) {
			config.selected_mode = SEARCH;
		} else if (strcmp(arg, "query") == 0) {
			config.selected_mode = QUERY;
		} else {
			//bad mode
		}
	} else {
		//bad num of params
	}
}

int parse_mode_opts(int argc, char **argv, int start_index)
{
	int i;
	for (i = start_index; i < argc && argv[i][0] == '-' && argv[i][0] == '-'; i++) {
		switch (config.selected_mode) {
			case INSTALL: {
				config.mode_opts = calloc(1, sizeof(struct install_options));
				if (strcmp(argv[i], "--local") == 0) {
					((struct install_options *) (config.mode_opts))->local = 1;
				} else if (strcmp(argv[i], "--no-deps") == 0) {
					((struct install_options *) (config.mode_opts))->no_deps = 1;
				} else if (strcmp(argv[i], "--force") == 0) {
					((struct install_options *) (config.mode_opts))->force = 1;
				} else if (strcmp(argv[i], "--needed") == 0) {
					((struct install_options *) (config.mode_opts))->needed = 1;
				} else if (strcmp(argv[i], "--as-deps") == 0) {
					((struct install_options *) (config.mode_opts))->as_dep = 1;
				} else if (strcmp(argv[i], "--as-expl") == 0) {
					((struct install_options *) (config.mode_opts))->as_expl = 1;
					((struct install_options *) (config.mode_opts))->as_dep = 0;

				} else {
					//bad option
				}
				break;
			}
			case UPGRADE: {
				config.mode_opts = calloc(1, sizeof(struct upgrade_options));
				if (strcmp(argv[i], "--force") == 0) {
					((struct upgrade_options *) (config.mode_opts))->force = 1;
				} else if (strcmp(argv[i], "--no-save") == 0) {
					((struct upgrade_options *) (config.mode_opts))->no_save = 1;
				} else {

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
				if (strcmp(argv[i], "--no-deps") == 0) {
					((struct uninstall_options *) (config.mode_opts))->no_deps = 1;
				} else if (strcmp(argv[i], "--cascade") == 0) {
					((struct uninstall_options *) (config.mode_opts))->cascade = 1;
					config.brew_opts.confirm = 1;
				} else if (strcmp(argv[i], "--no-save") == 0) {
					((struct uninstall_options *) (config.mode_opts))->no_save = 1;
				} else if (strcmp(argv[i], "--recursive") == 0) {
					((struct uninstall_options *) (config.mode_opts))->recursive = 1;
				} else if (strcmp(argv[i], "--recursive-strong") == 0) {
					((struct uninstall_options *) (config.mode_opts))->recursive = 2;
					config.brew_opts.confirm = 1;
				} else if (strcmp(argv[i], "--unneeded") == 0) {
					((struct uninstall_options *) (config.mode_opts))->unneeded = 1;
				} else {

				}
				break;
			}
			case BUILD: {
				config.mode_opts = calloc(1, sizeof(struct build_options));
				if (strcmp(argv[i], "--local") == 0) {
					((struct build_options *) (config.mode_opts))->local = 1;
				} else if (strcmp(argv[i], "--force") == 0) {
					((struct build_options *) (config.mode_opts))->force = 1;
				} else {

				}
			}
			case CHECK: {
				config.mode_opts = calloc(1, sizeof(struct check_options));
				if (strcmp(argv[i], "--local") == 0) {
					((struct check_options *) (config.mode_opts))->local = 1;
				} else if (strcmp(argv[i], "--package") == 0) {
					((struct check_options *) (config.mode_opts))->check_type = PACKAGE;
				} else if (strcmp(argv[i], "--script") == 0) {
					((struct check_options *) (config.mode_opts))->check_type = SCRIPT;
				} else {

				}
				break;
			}
			case HELP: {
				config.mode_opts = NULL;
				break;
			}
			case SEARCH: {
				config.mode_opts = NULL;
				break;
			}
			case QUERY: {
				config.mode_opts = NULL;
				break;
			}
			default: {
				//this really shouldn't happen, it only will if the mode is set outside of set_mode and to an int that isn't in the enum.
				fprintf(stderr, "Something went very wrong in parsing the commandline options.");
				unlock();
				exit(3);
			}
		}
	}
	return i;
}

void parse_targets(int argc, char **argv, int start_index)
{
	targets = calloc(max_targets, sizeof(struct target));
	for (int i = start_index; i < argc; i++) {
		if ((i - start_index) == max_targets) {
			max_targets *= 2;
			targets = realloc(targets, max_targets);
		}
		targets[i - start_index].name = argv[i];
	}
}

void print_brew_opts()
{
	dbprintf(VERBOSE, "----------------------------------\n");
	dbprintf(VERBOSE, " color: %i \n verbosity: %i \n confirm: %i \n sync: %i \n", config.brew_opts.color,
	         config.brew_opts.verbosity, config.brew_opts.confirm, config.brew_opts.sync);
	dbprintf(VERBOSE, "----------------------------------\n");

}

void print_mode()
{
	dbprintf(VERBOSE, " mode is %i \n", config.selected_mode);
	dbprintf(VERBOSE, "---------------------------------- \n");
}

void print_mode_opts()
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
	dbprintf(VERBOSE, "---------------------------------- \n");
}

void print_targets()
{

}