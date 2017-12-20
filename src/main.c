#include <stdio.h>
#include <unistd.h>
#include "commandLine/CommandlineParser.h"

#ifdef DEV
#define LOCKFILE "./lockfile"
#else
#define LOCKFILE "/etc/coldbrew/lockfile"
#endif

char lockfile_exists()
{
	return !access(LOCKFILE, F_OK);
}

void lock()
{
	system("touch "  LOCKFILE);
}

void unlock()
{
	system("rm " LOCKFILE);
}

int main(int argc, char **argv)
{
	if (lockfile_exists()) {
		fprintf(stderr,
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
