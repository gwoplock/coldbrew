//
// Created by Garrett Battaglia on 12/24/17.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Install.h"
#include "../utils/print.h"

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
		char* pkg_loc = download_file(targ, tmp_dir);
		file = fopen(pkg_loc,"r");
	}

	//check type


	fclose(file);
	//TODO: not this
	return (enum type) NULL;
}

char * download_file(struct target targ, char *tmp_dir)
{
}