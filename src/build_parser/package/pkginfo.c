//
// Created by Garrett Battaglia on 1/3/18.
//

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "pkginfo.h"
#include "../../utils/IO/fileIO.h"
#include "../../utils/IO/print.h"
#include "../../utils/stringManip.h"
#include "package.h"

void parse_pkginfo(FILE *pkginfo_file, struct target *targ)
{
	char *buf = calloc(256, sizeof(char));
	int buf_size = 256;
	for (int i = 0; i < 6; i++) {
		int succ = read_line(buf, buf_size, pkginfo_file);
		if (succ == 1) {
			proc_pkg_line(buf, buf_size, targ);
			memset(buf, 0, buf_size);
		} else if (succ < 0) {
			dbfprintf(NORMAL, stderr, "the .PKGINFO was invalid.\n");
			dbfprintf(VERBOSE, stderr,
			          "read_line had an error and returned an errorno of %i, translated it is \"%s\"\n",
			          errno,
			          strerror(errno));
			unlock();
			exit(6);
		} else {
			//im not worried about this, will write into spec that the max line length is 256 chars, if
			// needed we can change this but i dont think we will
		}
	}
	print_pkg_info(targ);
}

void proc_pkg_line(char *buffer, int buf_size, struct target *targ)
{
	dbprintf(VERBOSE, "parsing line: %s\n", buffer);
	char **spl = string_split(buffer, '=');
	dbprintf(VERBOSE, "opt: %s, val: %s\n", spl[0], spl[1]);
	if (strcmp(spl[0], "PKGVER") == 0) {
		char *temp = calloc(strlen(spl[1]), sizeof(char));
		strcpy(temp, spl[1]);
		targ->pkginfo.pkgver = temp;
	} else if (strcmp(spl[0], "CBVER") == 0) {
		char *temp = calloc(strlen(spl[1]), sizeof(char));
		strcpy(temp, spl[1]);
		targ->pkginfo.cbver = temp;
	} else if (strcmp(spl[0], "SCRIPTTYP") == 0) {
		targ->pkginfo.script_type = atoi(spl[1]);
	} else if (strcmp(spl[0], "PKGNAME") == 0) {
		char *temp = calloc(strlen(spl[1]), sizeof(char));
		strcpy(temp, spl[1]);
		targ->pkginfo.pkgname = temp;
	} else if (strcmp(spl[0], "BULDDATE") == 0) {
		char *temp = calloc(strlen(spl[1]), sizeof(char));
		strcpy(temp, spl[1]);
		targ->pkginfo.build_date = temp;
	} else if (strcmp(spl[0], "DEPS") == 0) {
		proc_deps_from_pkginfo(spl[1], targ);
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
		ret = string_split(deps_arr, ',');
		char *temp = calloc(strlen(ret[0]), sizeof(char));
		strcpy(temp, ret[0]);
		targ->pkginfo.deps[0] = temp;
		for (int i = 1; ret != NULL; i++) {
			ret = string_split(ret[1], ',');
			char *temp = calloc(strlen(ret[0]), sizeof(char));
			strcpy(temp, ret[0]);
			targ->pkginfo.deps[i] = temp;
		}
	}
}

void print_pkg_info(struct target *targ)
{
	dbprintf(VERBOSE, "pkgver: %s\n", targ->pkginfo.pkgver);
	dbprintf(VERBOSE, "cbver: %s\n", targ->pkginfo.cbver);
	dbprintf(VERBOSE, "script_type: %i\n", targ->pkginfo.script_type);
	dbprintf(VERBOSE, "pkgname: %s\n", targ->pkginfo.pkgname);
	dbprintf(VERBOSE, "build_date: %s\n", targ->pkginfo.build_date);
	dbprintf(VERBOSE, "deps count: %i\n", targ->pkginfo.to_install_count);
	for (int i = 0; i < targ->pkginfo.to_install_count; i++) {
		dbprintf(VERBOSE, "dep %i: %s\n", i, targ->pkginfo.deps[i]);
	}
}