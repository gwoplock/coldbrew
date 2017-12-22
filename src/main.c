#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "commandLine/CommandlineParser.h"
#include "utils/print.h"

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
 * @return int file descriptor for lockfile
 */
int lock()
{
	return creat (LOCKFILE, 00777);
}
/**
 * removes lockfile
 */
void unlock()
{
	unlink (LOCKFILE);
}

int main(int argc, char **argv)
{
	int lockfile;

	if (lockfile_exists()) {
		dbfprintf(NORMAL, stderr,
		        "Lockfile exists, exiting... \n if you believe this is an error verify coldbrew isn't running then delete \""LOCKFILE" \" \n");
		exit(1);
	}
	lockfile = lock();
	if (lockfile < 0) {
		dbfprintf(NORMAL, stderr, "unable to create lockfile \""LOCKFILE"\"\n");
		exit(1);
	}

	parseCommandLine(argc, argv);
	set_mode();
	set_options();
	back_print_options();
	set_mode_options();

	close(lockfile);
	unlock();
	exit(0);
}
