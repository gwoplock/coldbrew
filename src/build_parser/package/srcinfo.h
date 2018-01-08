//
// Created by Garrett Battaglia on 1/8/18.
//

#ifndef COLDBREW_SRCINFO_H
#define COLDBREW_SRCINFO_H

#include <stdio.h>
#include "../../commandLine/CommandlineParser.h"

void parse_srcinfo(FILE *pkginfo_file, struct target *targ);

#endif //COLDBREW_SRCINFO_H
