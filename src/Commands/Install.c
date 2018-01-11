//
// Created by Garrett Battaglia on 12/24/17.
//

#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>
#include "Install.h"
#include "../utils/IO/print.h"
#include "../build_parser/coldbrew/scriptHandler.h"
#include "../utils/stringManip.h"
#include "../utils/IO/http.h"
#include "../build_parser/package/srcinfo.h"
#include "../utils/IO/temporaryFiles.h"
#include "../utils/IO/fileIO.h"
#include <sys/utsname.h>
#include <unistd.h>
#include "../commandLine/options.h"

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
		targ->blob_loc = targ->blob_script_loc;
	} else if (file_head >> 16 == SHABANG) {
		ret = SCRIPT;
	} else {
		dbfprintf(NORMAL, stderr, "The file doesn't appear to be a format we know about");
		unlock();
		exit(5);
	}
	dbprintf(VERBOSE, "we determened the target \"%s\" to be a type %i\n", targ->name, ret);
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
	//TODO finish, waiting for database code

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
	//TODO pick file, waiting for database code
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
	//TODO set repo URL, waiting for database code
	//downlaod file to tmp dir
	download(file, tmp_dir, file_name);
	//return filename
	return file_name;
}


//TODO functionafiy
void install_blob(struct target *targ)
{
	//create tmp dir if needed
	if (targ->tmp_dir == NULL) {
		targ->tmp_dir = create_tmp_dir(strip_path(targ->name));
	}
	dbprintf(DEBUG, "targ->tmp_dir = %s\n", targ->tmp_dir);
	//extract blob
	extract_blob(targ);
	//parse .PKGINFO file
	char *pkginfo_name = "/.PKGINFO";
	size_t pkginfo_path_leng = strlen(targ->tmp_dir) + strlen(pkginfo_name);
	char *pkginfo_path = calloc(pkginfo_path_leng, sizeof(char));
	strcat(pkginfo_path, targ->tmp_dir);
	strcat(pkginfo_path, pkginfo_name);
	FILE *pkginfo = fopen(pkginfo_path, "r");
	parse_pkginfo(pkginfo, targ);
	//extract .SRCINFO
	extract_srcinfo(targ);
	//parse .SRCINFO file
	char *srcinfo_name = "/.SRCINFO";
	size_t srcinfo_path_leng = strlen(targ->tmp_dir) + strlen(srcinfo_name);
	char *srcinfo_path = calloc(srcinfo_path_leng, sizeof(char));
	strcat(srcinfo_path, targ->tmp_dir);
	strcat(srcinfo_path, srcinfo_name);
	FILE *srcinfo = fopen(srcinfo_path, "r");
	parse_srcinfo(srcinfo, targ);
	//save package info
	//install deps
}

void extract_blob(struct target *targ)
{
	char *tar_opts;
	if (config.brew_opts.verbosity == DEBUG) {
		tar_opts = "-xvf";
	} else {
		tar_opts = "-xf";
	}

	char *tar_output = "-C";

	pid_t pid = fork();
	dbprintf(DEBUG, "execlp(\"tar\", \"tar\", %s, %s, %s, %s)", tar_opts, targ->blob_loc, tar_output,
	         targ->tmp_dir);
	if (pid == 0) {
		int ret = execlp("tar", "tar", tar_opts, targ->blob_loc, tar_output, targ->tmp_dir, NULL);
		dbprintf(DEBUG, "exec returned %i\n", ret);
	} else if (pid < 0) {
		//error
	} else {
		waitpid(pid, NULL, 0);
	}
}

void extract_srcinfo(struct target *targ)
{
	char *srcinfo_gz_name = "/.SRCINFO.gz";
	size_t srcinfo_gz_command_leng = strlen(targ->tmp_dir) + strlen(srcinfo_gz_name) /*+ strlen(gunzip)*/;
	char *srcinfo_gz_command = calloc(srcinfo_gz_command_leng, sizeof(char));
	strcat(srcinfo_gz_command, targ->tmp_dir);
	strcat(srcinfo_gz_command, srcinfo_gz_name);
	dbprintf(DEBUG, "gunzip command: %s\n", srcinfo_gz_command);

	int pid = fork();
	if (pid == 0) {
		int ret = execlp("gunzip", "gunzip", srcinfo_gz_command, NULL);
		dbprintf(DEBUG, "exec returned %i\n", ret);
	} else if (pid < 0) {
		//error
	} else {
		waitpid(pid, NULL, 0);
	}
}