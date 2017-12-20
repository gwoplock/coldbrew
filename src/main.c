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
 */
void lock()
{
	system("touch "  LOCKFILE);
}
/**
 * removes lockfile
 */
void unlock()
{
	system("rm " LOCKFILE);
}

int main(int argc, char **argv)
{
	if (lockfile_exists()) {
		dbfprintf(NORMAL, stderr,
		        "Lockfile exists, exiting... \n if you believe this is an error verify coldbrew isn't running then delete \""LOCKFILE" \" ");
		exit(1);
	}
	lock();
	parseCommandLine(argc, argv);
	set_mode();
	set_options();
	back_print_options();
	set_mode_options();
	unlock();
}
