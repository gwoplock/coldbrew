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
			memset(buf, sizeof(char), 256);
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
		targ->pkginfo.pkgver=spl[1];
	} else if (strcmp(spl[0], "CBVER") == 0) {
		targ->pkginfo.cbver = spl[1];
	} else if (strcmp(spl[0], "SCRIPTTYP") == 0) {
		//TODO change to int
		targ->pkginfo.script_type=spl[1];
	} else if (strcmp(spl[0], "PKGNAME") == 0) {
		targ->pkginfo.pkgname=spl[1];
	} else if (strcmp(spl[0], "BULDDATE") == 0) {
		targ->pkginfo.build_date=spl[1];
	} else if (strcmp(spl[0], "DEPS") == 0) {
		//TODO split to each dep
		targ->pkginfo.deps=spl[1];
	} else {
		//error
	}
}