#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "commandLine/CommandlineParser.h"
#include "utils/print.h"
#include "Commands/Install.h"
#include "utils/http.h"

#ifdef DEV
#define LOCKFILE "./lockfile"
#else
#define LOCKFILE "/etc/coldbrew/lockfile"
#endif

/**
 * checks if the lockfile exsits
 * @return bool if file exsits, true if it does, false if not
 */
char lockfile_exists()
{
	return !access(LOCKFILE, F_OK);
}

/**
 * creates lockfile
 * @return bool if success, true, else false
 */
char lock()
{
	int fd = creat(LOCKFILE, 00777);
	if (fd < 0) {
		return 0;
	} else {
		close(fd);
		return 1;
	}
}

/**
 * removes lockfile
 */
void unlock()
{
	unlink(LOCKFILE);
}

int main(int argc, char **argv)
{
	if (lockfile_exists()) {
		dbfprintf(NORMAL, stderr,
		          "Lockfile exists, exiting... \n if you believe this is an error verify coldbrew isn't running then delete \""LOCKFILE" \" \n");
		exit(1);
	}
	if (!lock()) {
		dbfprintf(NORMAL, stderr, "unable to create lockfile \""LOCKFILE"\"\n");
		exit(1);
	}
	parseCommandLine(argc, argv);

	//TODO temp
	struct resource test;
	test.location = "/~john.cole/";
	test.host = "http://www.utdallas.edu";
	download(test, ".", "/test.html");
	install(&targets[0]);
	//end temp

	unlock();
	return 0;
}
