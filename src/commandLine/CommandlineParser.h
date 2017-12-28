//
// Created by Garrett Battaglia on 12/7/17.
//

#ifndef COLDBREW_COMMANDLINEPARSER_H
#define COLDBREW_COMMANDLINEPARSER_H


extern struct configuration config;

extern struct target *targets;

extern int num_of_targets;

extern int max_targets;

enum mode
{
	INSTALL, UPGRADE, UPDATE, SYNC, UNINSTALL, BUILD, CHECK, HELP, SEARCH, QUERY
};

enum type
{
	PACKAGE, SCRIPT
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

struct install_options
{
	int local;
	int no_deps;
	int force;
	int needed;
	int as_dep;
	int as_expl;
};

struct uninstall_options
{
	int no_deps;
	int cascade;
	int no_save;
	int recursive;
	int unneeded;
};

struct upgrade_options
{
	int force;
	int no_save;
};

struct build_options
{
	int local;
	int force;
};

struct check_options
{
	int local;
	enum type check_type;
};


struct target
{
	char *name;
	char *tmp_dir;
	char *blob_loc;
	char *blob_script_loc;
	enum type target_type;
};

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
