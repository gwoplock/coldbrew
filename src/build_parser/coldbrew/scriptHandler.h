//
// Created by Garrett Battaglia on 12/27/17.
//

#ifndef COLDBREW_SCRIPTHANDLER_H
#define COLDBREW_SCRIPTHANDLER_H

#include "../../commandLine/CommandlineParser.h"

struct script
{
	struct source *srcs;
	int src_leng;
};

struct source
{
	char *url;
};

struct script parse_script(char *script);

void build_blob(struct target *targ);

void download_src(struct source *src);

void extract_src(struct source *src);

void script_prep(struct script script);

void script_build(struct script script);

void script_check(struct script script);

void script_package(struct script script);

void package_compress(struct script script);

#endif //COLDBREW_SCRIPTHANDLER_H
