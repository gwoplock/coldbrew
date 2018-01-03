//
// Created by Garrett Battaglia on 1/3/18.
//

#ifndef COLDBREW_PKGINFO_H
#define COLDBREW_PKGINFO_H

#include <stdio.h>
#include "../../commandLine/CommandlineParser.h"

void parse_pkginfo(FILE *pkginfo_file, struct target *targ);

void proc_pkg_line(char *buffer, int buf_size, struct target *targ);

struct pkginfo
{
	char *pkgver;
	char *cbver;
	int script_type;
	char *pkgname;
	char *build_date;
	char **deps;
	int to_install_count;
};

#endif //COLDBREW_PKGINFO_H
