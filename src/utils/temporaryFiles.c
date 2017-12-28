//
// Created by Garrett Battaglia on 12/28/17.
//

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "temporaryFiles.h"
#include "print.h"

char *create_tmp_dir(char *dir_name)
{
	// +1 for null terminator
	const size_t name_len = 14 + strlen (dir_name) + 7 + 1;
	char tmp_dir_template[name_len];
	// Initialize to 0
	memset (tmp_dir_template, 0, name_len);
	//create a template for the temp dir, this will be where we build the package and such.
	strcat(tmp_dir_template, "/tmp/coldbrew.");
	strcat(tmp_dir_template, dir_name);
	strcat(tmp_dir_template, ".XXXXXX");
	char *tmp = mkdtemp(tmp_dir_template);
	if (tmp == NULL) {
		dbfprintf(VERBOSE, stderr,
		          "mkdtemp had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
		          strerror(errno));
	}
	dbprintf(DEBUG, "target: %s, template: %s, tempdir: %s\n", dir_name, tmp_dir_template, tmp);
	return tmp;
}
