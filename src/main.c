#include <stdio.h>
#include <unistd.h>
#include "commandLine/CommandlineParser.h"

char lockfile_exists(){
	return !access("/etc/coldbrew/lockfile", F_OK);
}

int main(int argc, char **argv)
{
	if (lockfile_exists()){
		fprintf(stderr, "Lockfile exists, exiting... \n if you believe this is an error verify coldbrew isn't running then delete \"/etc/coldbrew/lockfile\"");
		exit(-1);
	}
	parseCommandLine(argc-1, argv +1);

}
