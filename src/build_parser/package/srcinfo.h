//
// Created by Garrett Battaglia on 1/8/18.
//

#ifndef COLDBREW_SRCINFO_H
#define COLDBREW_SRCINFO_H

#include <stdio.h>
#include "../../commandLine/CommandlineParser.h"

void parse_srcinfo(FILE *pkginfo_file, struct target *targ);

void proc_srcinfo_line(char *buffer, int buf_size, struct target *targ);

void handle_file(struct target *targ, char **line);

#endif //COLDBREW_SRCINFO_H
