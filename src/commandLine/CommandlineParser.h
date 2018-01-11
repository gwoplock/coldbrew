//
// Created by Garrett Battaglia on 12/7/17.
//

#ifndef COLDBREW_COMMANDLINEPARSER_H
#define COLDBREW_COMMANDLINEPARSER_H

#include "../build_parser/package/pkginfo.h"
#include "../build_parser/package/package.h"

extern struct configuration config;

extern int num_of_targets;

extern int max_targets;






extern char lock();


extern void unlock();

void parseCommandLine(int argc, char **argv);

int parse_brew_opts(int argc, char **argv);

void read_mode(int argc, char **argv, int index);

int parse_mode_opts(int argc, char **argv, int start_index);

void parse_targets(int argc, char **argv, int start_index);

void print_brew_opts();

void print_mode();

void print_mode_opts();

void print_targets();

void set_defaults();

void validate_args();


#endif //COLDBREW_COMMANDLINEPARSER_H
