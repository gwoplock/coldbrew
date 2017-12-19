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
	set_mode_options();

	if (config.brew_opts.verbosity == 2) {
		// command line parsing testcode
		printf("----------------------------------\n");
		for (int i = 0; i < command_line_args->size; i++) {
			printf(" %i: %s -> %i\n", i, command_line_args->key[i], command_line_args->map[i]);
		}
		printf("---------------------------------- \n");
		printf(" mode is %i \n", config.selected_mode);
		printf("---------------------------------- \n");
		printf(" color: %i \n verbosity: %i \n confirm: %i \n sync: %i \n", config.brew_opts.color,
		       config.brew_opts.verbosity, config.brew_opts.confirm, config.brew_opts.sync);
		printf("----------------------------------\n");
	}
#ifdef DEV
	if (config.brew_opts.verbosity != 2) {
		// command line parsing testcode
		printf("----------------------------------\n");
		for (int i = 0; i < command_line_args->size; i++) {
			printf(" %i: %s -> %i\n", i, command_line_args->key[i], command_line_args->map[i]);
		}
		printf("---------------------------------- \n");
		printf(" mode is %i \n", config.selected_mode);
		printf("---------------------------------- \n");
		printf(" color: %i \n verbosity: %i \n confirm: %i \n sync: %i \n", config.brew_opts.color,
		       config.brew_opts.verbosity, config.brew_opts.confirm, config.brew_opts.sync);
		printf("----------------------------------\n");
	}
#endif
	unlock();

}
