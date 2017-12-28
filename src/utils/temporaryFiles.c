//
// Created by Garrett Battaglia on 12/28/17.
//

#include <string.h>
#include <unistd.h>
#include "temporaryFiles.h"
#include "print.h"

char *create_tmp_dir(char *dir_name)
{
	char tmp_dir_template[256];
//create a template for the temp dir, this will be where we build the package and such.
	strcat(tmp_dir_template, "/tmp/coldbrew.");
	strcat(tmp_dir_template, dir_name);
	strcat(tmp_dir_template, ".XXXXXX");
	char* tmp = mkdtemp(tmp_dir_template);
	dbprintf(DEBUG, "target: %s, template: %s, tempdir: %s\n", dir_name, tmp_dir_template, tmp);
	return tmp;
}
