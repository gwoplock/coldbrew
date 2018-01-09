//
// Created by Garrett Battaglia on 1/8/18.
//

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "srcinfo.h"
#include "../../utils/fileIO.h"
#include "../../utils/print.h"

void parse_srcinfo(FILE *pkginfo_file, struct target *targ)
{
	//read line
	char *buf = calloc(256, sizeof(char));
	//TODO replace with a while loop
	//for (int i = 0; i < 6; i++) {
		int succ = read_line(buf, 256, pkginfo_file);
		if (succ == 1) {
			proc_srcinfo_line(buf, 256, targ);
			memset(buf, 0, 256);
		} else if (succ < 0) {
			//TODO this may not be true. 
			dbfprintf(NORMAL, stderr, "the .SRCINFO was invalid.\n");
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
	//}
	//apply action
}

void proc_srcinfo_line(char *buffer, int buf_size, struct target *targ)
{

}