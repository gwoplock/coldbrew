//
// Created by Garrett Battaglia on 12/24/17.
//

#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>
#include "Install.h"
#include "../utils/print.h"
#include "../build_parser/coldbrew/scriptHandler.h"
#include "../utils/stringManip.h"
#include "../utils/temporaryFiles.h"
#include "../utils/http.h"
#include <sys/utsname.h>


const short SHABANG = 0x2321;

const short GZ_MAGIC_NUM = 0x1f8b;


/**
 * installs a target
 * @param targ: target to install
 */
void install(struct target *targ)
{
	targ->target_type = get_install_type(targ);
	if (targ->target_type == SCRIPT) {
		build_blob(targ);
	}
	install_blob(targ);

}

/**
 * gets the type of the target
 * @param targ: target to install
 * @return the type of the target (script or binary package)
 */
enum type get_install_type(struct target *targ)
{

	FILE *file;
	if (config.mode_opts != NULL && ((struct install_options *) (config.mode_opts))->local == 1) {
		targ->blob_script_loc = targ->name;
		file = fopen(targ->name, "r");
	} else {
		if (targ->tmp_dir == NULL) {
			targ->tmp_dir = create_tmp_dir(strip_path(targ->name));
		}
		targ->blob_script_loc = download_file(*targ, targ->tmp_dir);
		file = fopen(targ->blob_script_loc, "r");
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
	if (file_head >> 16 == GZ_MAGIC_NUM) {
		ret = PACKAGE;
	} else if (file_head >> 16 == SHABANG) {
		ret = SCRIPT;
	} else {
		dbfprintf(NORMAL, stderr, "The file doesn't appear to be a format we know about");
		unlock();
		exit(5);
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
	//TODO finish

	struct utsname *uname_info = calloc(sizeof(struct utsname), 1);
	//get info
	int tmp = uname(uname_info);
	//get OS version
	char *os = uname_info->sysname;
	//get arch
	char *arch = uname_info->machine;
	//pick repo
	//get repo ip addr
	//pick file
	//temp
	char *file_name = "";
	//TODO pick file
	//build download info
	struct resource file;
	char *slash = "/";
	size_t remote_location_strleng =
			strlen(slash) + strlen(os) + strlen(slash) + strlen(arch) + strlen(slash) + strlen(file_name);
	file.location = calloc(sizeof(char), remote_location_strleng);
	strcat(file.location, slash);
	strcat(file.location, os);
	strcat(file.location, slash);
	strcat(file.location, arch);
	strcat(file.location, slash);
	strcat(file.location, file_name);
	//TODO set repo ip addr
	//downlaod file to tmp dir
	download(file/*resource struct*/, tmp_dir/*fs location*/, file_name/*filename*/);
	//return filename
	return file_name;
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

void install_blob(struct target *targ)
{
	//create tmp dir if needed
	//create dirs
	//move files
	//set up links
	//apply permissions
	//save package info
}
