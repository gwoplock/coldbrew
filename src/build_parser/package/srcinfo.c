//
// Created by Garrett Battaglia on 1/8/18.
//

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "srcinfo.h"
#include "../../utils/IO/fileIO.h"
#include "../../utils/IO/print.h"
#include "../../utils/stringManip.h"

void parse_srcinfo(FILE *pkginfo_file, struct target *targ)
{
	//read line
	char *buf = calloc(256, sizeof(char));
	int succ = 0;
	while (succ != -1) {
		succ = read_line(buf, 256, pkginfo_file);
		if (succ == 1) {
			proc_srcinfo_line(buf, 256, targ);
			memset(buf, 0, 256);
		} /*else if (succ < 0) {
			//this may not be true.
			dbfprintf(NORMAL, stderr, "the .SRCINFO was invalid.\n");
			dbfprintf(VERBOSE, stderr,
			          "read_line had an error and returned an errorno of %i, translated it is \"%s\"\n",
			          errno,
			          strerror(errno));
			unlock();
			exit(7);
		} */else {
			//im not worried about this, will write into spec that the max line length is 256 chars, if
			// needed we can change this but i dont think we will
		}
	}
}

void proc_srcinfo_line(char *buffer, int buf_size, struct target *targ)
{
	dbprintf(VERBOSE, "parsing line: %s\n", buffer);
	//split into path, type, type fields
	char **line = calloc(3, sizeof(char *));
	char **spl = string_split(buffer, ' ');
	line[0] = spl[0];
	char *temp = spl[1];
	spl = string_split(spl[1], ' ');
	if (spl == NULL) {
		line[1] = temp;
	} else {
		line[1] = spl[0];
	}
	dbprintf(DEBUG, "path: %s, type: %s\n", line[0], line[1]);

	//switch on type
	if (strcmp(line[1], "dir") == 0) {
		create_dir(line[0]);
	} else if (strcmp(line[1], "file") == 0) {
		handle_file(targ, line);
	} else if (strcmp(line[1], "link") == 0) {
		spl = string_split(spl[1], ' ');
		line[2] = spl[0];
		dbprintf(DEBUG, "type args: %s", line[2]);
		//todo parse type args
	} else {
		dbfprintf(NORMAL, stderr, "the .SRCINFO was invalid.\n");
		dbfprintf(VERBOSE, stderr, "The type \"%s\" was invalid, ", line[1]);
		unlock();
		exit(7);
	}
	//apply action
}

void handle_file(struct target *targ, char **line)
{
	//spl = string_split(spl[1], ' ');
	//line[2] = spl[0];
	//fidbprintf(DEBUG, "type args: %s", line[2]);
	//todo parse type args
	int tmp_path_length = strlen(targ->tmp_dir) + strlen(line[0]);
	char *tmp_path = calloc(tmp_path_length, sizeof(char));
	strcat(tmp_path, targ->tmp_dir);
	strcat(tmp_path, line[0]);
	FILE *to_cpy = fopen(tmp_path, "r");
	FILE *out = fopen(line[0], "w");
	if (to_cpy == NULL || out == NULL) {
		dbfprintf(NORMAL, stderr, "there was an error copying the file\n");
		dbfprintf(VERBOSE, stderr,
		          "fopen had an error and returned an errorno of %i, translated it is \"%s\"\n",
		          errno,
		          strerror(errno));
		unlock();
		exit(7);
	}
	copy_file(to_cpy, out);
	fclose(to_cpy);
	fclose(out);
}