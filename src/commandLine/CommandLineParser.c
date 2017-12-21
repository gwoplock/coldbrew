//
// Created by Garrett Battaglia on 12/7/17.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
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
		if (strcmp(argv[i], "--color")) {
			config.brew_opts.color = 1;
		} else if (strcmp(argv[i], "--no-color")) {
			config.brew_opts.color = 0;
		} else if (strcmp(argv[i], "--verbose")) {
			config.brew_opts.verbosity = VERBOSE;
		} else if (strcmp(argv[i], "--debug")) {
			config.brew_opts.verbosity = DEBUG;
		} else if (strcmp(argv[i], "--no-confirm")) {
			config.brew_opts.confirm = 0;
		} else if (strcmp(argv[i], "--confirm")) {
			config.brew_opts.confirm = 1;
		} else if (strcmp(argv[i], "--no-sync")) {
			config.brew_opts.sync = 0;
		} else if (strcmp(argv[i], "--sync")) {
			config.brew_opts.sync = 1;
		} else {
			//bad arg
		}
	}
	return i;
}

void read_mode(int argc, char **argv, int index)
{
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
}

int parse_mode_opts(int argc, char **argv, int start_index)
{
	int i;
	for (i = start_index; i < argc && argv[i][0] == '-' && argv[i][0] == '-'; i++) {
		switch (config.selected_mode) {
			case INSTALL: {
				config.mode_opts = calloc(1, sizeof(struct install_options));
				if (strcmp(argv[i], "--local")) {

				} else if (strcmp(argv[i], "--no-deps")) {

				} else if (strcmp(argv[i], "--force")) {

				} else if (strcmp(argv[i], "--needed")) {

				} else if (strcmp(argv[i], "--as-deps")) {

				} else if (strcmp(argv[i], "--as-expl")) {

				} else {
					//bad option
				}
				break;
			}
			case UPGRADE: {
				config.mode_opts = calloc(1, sizeof(struct upgrade_options));
				if (strcmp(argv[i], "--force")) {

				} else if (strcmp(argv[i], "--no-save")) {

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
				if (strcmp(argv[i], "--no-deps")) {

				} else if (strcmp(argv[i], "--cascade")) {

				} else if (strcmp(argv[i], "--no-save")) {

				} else if (strcmp(argv[i], "--recursive")) {

				} else if (strcmp(argv[i], "--recursive-strong")) {

				} else if (strcmp(argv[i], "--unneeded")) {

				} else {

				}
				break;
			}
			case BUILD: {
				config.mode_opts = calloc(1, sizeof(struct build_options));
				if (strcmp(argv[i], "--local")) {

				} else if (strcmp(argv[i], "--force")) {

				} else {

				}
			}
			case CHECK: {
				config.mode_opts = calloc(1, sizeof(struct check_options));
				if (strcmp(argv[i], "--local")) {

				} else if (strcmp(argv[i], "--package")) {

				} else if (strcmp(argv[i], "--script")) {

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

			}
		}
	}
	return i;
}

void parse_targets(int argc, char **argv, int start_index)
{

}