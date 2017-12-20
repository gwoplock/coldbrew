#include <stdio.h>
#include <unistd.h>
#include "commandLine/CommandlineParser.h"

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
		switch (config.selected_mode) {
			case INSTALL : {
				printf(" local: %i \n no-deps: %i \n force: %i \n needed: %i \n as-dep: %i \n as-expl: %i \n",
				       ((struct install_options *) (config.mode_opts))->local,
				       ((struct install_options *) (config.mode_opts))->no_deps,
				       ((struct install_options *) (config.mode_opts))->force,
				       ((struct install_options *) (config.mode_opts))->needed,
				       ((struct install_options *) (config.mode_opts))->as_dep,
				       ((struct install_options *) (config.mode_opts))->as_expl);
				break;
			}
			case UPGRADE: {
				printf(" force: %i, no-save: %i",
				       ((struct upgrade_options *) (config.mode_opts))->force,
				       ((struct upgrade_options *) (config.mode_opts))->no_save);
				break;
			}
			case UNINSTALL: {
				printf(" no-deps: %i \n cascade: %i \n no-save: %i \n recursive: %i \n unneeded: %i \n",
				       ((struct uninstall_options *) (config.mode_opts))->no_deps,
				       ((struct uninstall_options *) (config.mode_opts))->cascade,
				       ((struct uninstall_options *) (config.mode_opts))->no_save,
				       ((struct uninstall_options *) (config.mode_opts))->recursive,
				       ((struct uninstall_options *) (config.mode_opts))->unneeded);
				break;
			}
			case BUILD: {
				printf(" local: %i \n force: %i \n",
				       ((struct build_options *) (config.mode_opts))->local,
				       ((struct build_options *) (config.mode_opts))->force);
				break;
			}
			case CHECK: {
				printf(" local: %i \n type: %i \n",
				       ((struct check_options *) (config.mode_opts))->local,
				       ((struct check_options *) (config.mode_opts))->check_type);
				break;
			}

			default: {
				printf("Selected mode doesn't have options \n");
			}
		}
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
		switch (config.selected_mode) {
			case INSTALL : {
				printf(" local: %i \n no-deps: %i \n force: %i \n needed: %i \n as-dep: %i \n as-expl: %i \n",
				       ((struct install_options *) (config.mode_opts))->local,
				       ((struct install_options *) (config.mode_opts))->no_deps,
				       ((struct install_options *) (config.mode_opts))->force,
				       ((struct install_options *) (config.mode_opts))->needed,
				       ((struct install_options *) (config.mode_opts))->as_dep,
				       ((struct install_options *) (config.mode_opts))->as_expl);
				break;
			}
			case UPGRADE: {
				printf(" force: %i, no-save: %i",
				       ((struct upgrade_options *) (config.mode_opts))->force,
				       ((struct upgrade_options *) (config.mode_opts))->no_save);
				break;
			}
			case UNINSTALL: {
				printf(" no-deps: %i \n cascade: %i \n no-save: %i \n recursive: %i \n unneeded: %i \n",
				       ((struct uninstall_options *) (config.mode_opts))->no_deps,
				       ((struct uninstall_options *) (config.mode_opts))->cascade,
				       ((struct uninstall_options *) (config.mode_opts))->no_save,
				       ((struct uninstall_options *) (config.mode_opts))->recursive,
				       ((struct uninstall_options *) (config.mode_opts))->unneeded);
				break;
			}
			case BUILD: {
				printf(" local: %i \n force: %i \n",
				       ((struct build_options *) (config.mode_opts))->local,
				       ((struct build_options *) (config.mode_opts))->force);
				break;
			}
			case CHECK: {
				printf(" local: %i \n type: %i \n",
				       ((struct check_options *) (config.mode_opts))->local,
				       ((struct check_options *) (config.mode_opts))->check_type);
				break;
			}

			default: {
				printf("Selected mode doesn't have options \n");
			}
		}
		printf("----------------------------------\n");
	}
#endif
	unlock();

}
