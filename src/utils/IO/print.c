//
// Created by Garrett Battaglia on 12/20/17.
//

#include <stdarg.h>
#include <stdio.h>
#include "print.h"
#include "../../commandLine/options.h"
#include "../../commandLine/CommandlineParser.h"

void dbprintf(enum print_level pl, char *format, ...)
{
	va_list list;
	va_start(list, format);
	if (config.brew_opts.verbosity >= pl) {
		vprintf(format, list);
	}
	va_end(list);
}

void dbfprintf(enum print_level pl, FILE *output, char *format, ...)
{
	va_list list;
	va_start(list, format);
	if (config.brew_opts.verbosity >= pl) {
		vfprintf(output, format, list);
	}
	va_end(list);
}