//
// Created by Garrett Battaglia on 1/10/18.
//

#ifndef COLDBREW_OPTIONS_H
#define COLDBREW_OPTIONS_H

#include "../build_parser/package/package.h"

enum mode
{
	INSTALL, UPGRADE, UPDATE, SYNC, UNINSTALL, BUILD, CHECK, HELP, SEARCH, QUERY
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

#endif //COLDBREW_OPTIONS_H
