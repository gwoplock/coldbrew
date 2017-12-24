//
// Created by Garrett Battaglia on 12/24/17.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>
#include "Install.h"
#include "../utils/print.h"

const short SHABANG = 0x2321;

const short GZ_MAGIC_NUM = 0;

void install(struct target targ)
{
	enum type get_intall_type = get_install_type(targ);

}

enum type get_install_type(struct target targ)
{

	FILE *file;
	if (config.mode_opts != NULL && ((struct install_options *) (config.mode_opts))->local == 1) {
		file = fopen(targ.name, "r");

	} else {
		char tmp_dir_template[256];
		strcat(tmp_dir_template, "/tmp/coldbrew.");
		strcat(tmp_dir_template, targ.name);
		strcat(tmp_dir_template, ".XXXXXX");
		char *tmp_dir = mkdtemp(tmp_dir_template);
		dbprintf(DEBUG, "target: %s, tempdir: %s", targ.name, tmp_dir);
		char *pkg_loc = download_file(targ, tmp_dir);
		file = fopen(pkg_loc, "r");
	}

	if (file == NULL) {
		dbfprintf(VERBOSE, stderr,
		          "fopen had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
		          strerror(errno));
		dbfprintf(NORMAL, stderr, "there was an error opening the package");
		unlock();
		exit(4);
	}
	enum type ret;
	int file_head = get_first_int(file);
	dbprintf(DEBUG, "first 4 bytes of the package are %x\n", file_head);
	if (file_head == GZ_MAGIC_NUM) {
		ret = PACKAGE;
	} else if (file_head >> 16 == SHABANG) {
		ret = SCRIPT;
	}
	dbprintf(VERBOSE, "we determened the target to be a type %i", ret);
	fclose(file);
	return ret;
}

char *download_file(struct target targ, char *tmp_dir)
{
}

int get_first_int(FILE *file)
{
	int *ret = calloc(1, sizeof(int));
	for (int i = 0; i < 3; i++) {
		fread(ret, 1, 1, file);
		*ret = *ret << 8;
	}
	fread(ret, 1, 1, file);
	return *ret;
}