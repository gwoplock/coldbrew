#include <stdio.h>
#include <unistd.h>
#include "commandLine/CommandlineParser.h"

#ifdef DEV
#define LOCKFILE "./lockfile"
#else
#define LOCKFILE "/etc/coldbrew/lockfile"
#endif

char lockfile_exists(){
	return !access(LOCKFILE, F_OK);
}

void lock(){
	system("touch "  LOCKFILE);
}

void unlock(){
	system("rm " LOCKFILE);
}

int main(int argc, char **argv)
{
	if (lockfile_exists()){
		fprintf(stderr, "Lockfile exists, exiting... \n if you believe this is an error verify coldbrew isn't running then delete \""LOCKFILE" \" ");
		exit(-1);
	}
	lock();
	parseCommandLine(argc-1, argv +1);
#ifdef DEV
	// command line parsing testcode
	for(int i = 0; i<command_line_args->size; i++){
		printf("%i: %s -> %i\n", i, command_line_args->key[i], command_line_args->map[i]);
	}
#endif
	unlock();

}
