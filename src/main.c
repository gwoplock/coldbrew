#include <stdio.h>
#include "commandLine/CommandlineParser.h"

int main(int argc, char **argv)
{
	parseCommandLine(argc, argv);
	for (int i =0; i < command_line_args->size; i++){
		printf("%i: %s -> %i\n", i,command_line_args->key[i], command_line_args->map[i]);
	}
}
