//
// Created by Garrett Battaglia on 1/3/18.
//

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "pkginfo.h"
#include "../../utils/fileIO.h"
#include "../../utils/print.h"
#include "../../utils/stringManip.h"

void parse_pkginfo(FILE *pkginfo_file, struct target *targ)
{
	char *buf = calloc(256, sizeof(char));
	for (int i = 0; i < 6; i++) {
		int succ = read_line(buf, 256, pkginfo_file);
		if (succ == 1) {
			proc_pkg_line(buf, 256, targ);
			memset(buf, 0, 256);
		} else if (succ < 0) {
			dbfprintf(NORMAL, stderr, "the .PKGINFO was invalid.\n");
			dbfprintf(VERBOSE, stderr,
			          "read_line had an error and returned an errorno of %i, translated it is \"%s\"\n",
			          errno,
			          strerror(errno));
			unlock();
			exit(6);
		} else {
			//TODO
			//didnt read full line
		}
	}
}

void proc_pkg_line(char *buffer, int buf_size, struct target *targ)
{
	dbprintf(VERBOSE, "parsing line: %s\n", buffer);
	char **spl = string_split(buffer, '=');
	dbprintf(VERBOSE, "opt: %s, val: %s\n", spl[0], spl[1]);
	if (strcmp(spl[0], "PKGVER") == 0) {
		targ->pkginfo.pkgver = spl[1];
	} else if (strcmp(spl[0], "CBVER") == 0) {
		targ->pkginfo.cbver = spl[1];
	} else if (strcmp(spl[0], "SCRIPTTYP") == 0) {
		targ->pkginfo.script_type = atoi(spl[1]);
	} else if (strcmp(spl[0], "PKGNAME") == 0) {
		targ->pkginfo.pkgname = spl[1];
	} else if (strcmp(spl[0], "BULDDATE") == 0) {
		targ->pkginfo.build_date = spl[1];
	} else if (strcmp(spl[0], "DEPS") == 0) {
		proc_deps_from_pkginfo(spl[1], targ);

		/*//TODO split to each dep
		targ->pkginfo.deps=spl[1];*/
	} else {
		//error
	}
}

void proc_deps_from_pkginfo(char *deps_arr, struct target *targ)
{
	if (strcmp(deps_arr, "(NONE)") == 0) {
		//no deps
	} else {
		int count = 0;
		for (int i = 0; i < strlen(deps_arr); i++) {
			if (deps_arr[i] == ',') {
				count++;
			}
		}
		targ->pkginfo.deps = calloc(count + 1, sizeof(char *));
		char **ret;
		ret = string_split(deps_arr, ",");
		targ->pkginfo.deps[0] = ret[0];
		for (int i = 1; ret != NULL; i++) {
			ret = string_split(ret[1], ",");
			targ->pkginfo.deps[i] = ret[0];
		}
	}
}