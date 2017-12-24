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

char* tmp_dir;


/**
 * installs a target
 * @param targ: target to install
 */
void install(struct target targ)
{
	enum type get_intall_type = get_install_type(targ);

}
/**
 * gets the type of the target
 * @param targ: target to install
 * @return the type of the target (script or binary package)
 */
enum type get_install_type(struct target targ)
{

	FILE *file;
	if (config.mode_opts != NULL && ((struct install_options *) (config.mode_opts))->local == 1) {
		file = fopen(targ.name, "r");

	} else {
		char tmp_dir_template[256];
		//create a template for the temp dir, this will be where we build the package and such.
		strcat(tmp_dir_template, "/tmp/coldbrew.");
		strcat(tmp_dir_template, targ.name);
		strcat(tmp_dir_template, ".XXXXXX");
		tmp_dir = mkdtemp(tmp_dir_template);
		dbprintf(DEBUG, "target: %s, tempdir: %s\n", targ.name, tmp_dir);
		char *pkg_loc = download_file(targ, tmp_dir);
		file = fopen(pkg_loc, "r");
	}
	//fopen (or mkdtemp) exploded. we need to die
	if (file == NULL) {
		dbfprintf(VERBOSE, stderr,
		          "fopen had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
		          strerror(errno));
		dbfprintf(NORMAL, stderr, "there was an error opening the package\n");
		unlock();
		exit(4);
	}
	enum type ret;
	//read first 4 bytes from the file
	int file_head = get_first_int(file);
	dbprintf(DEBUG, "first 4 bytes of the package are %x\n", file_head);
	//comp magic numbers, #! is the magic number for script files.
	if (file_head == GZ_MAGIC_NUM) {
		ret = PACKAGE;
	} else if (file_head >> 16 == SHABANG) {
		ret = SCRIPT;
	} else {
		dbfprintf(NORMAL, stderr, "The file doesn't appear to be a format we know about");
		unlock();
		exit(7);
	}
	dbprintf(VERBOSE, "we determened the target to be a type %i\n", ret);
	//close the file, we will need it later
	fclose(file);
	return ret;
}
/**
 * not done but will download target if needbe
 * @param targ: target to download
 * @param tmp_dir: dir to place the download
 * @return char* of package name/location
 */
char *download_file(struct target targ, char *tmp_dir)
{
	//TODO
	dbfprintf(NORMAL, stderr, "we cant download files yet \n");
	unlock();
	exit(5);
}
/**
 * gets the first int (4 bytes) from the file, may be moved to utils
 * @param file: FILE* to file
 * @return first 4 bytes. c
 */
int get_first_int(FILE *file)
{
	//create an int to hold the file
	int *ret = calloc(1, sizeof(int));
//read a byte at a time because fuck endiness
	for (int i = 0; i < 3; i++) {
		fread(ret, 1, 1, file);
		*ret = *ret << 8;
	}
	//read lasy byte b/c dont want to shift
	fread(ret, 1, 1, file);
	//return
	return *ret;
}