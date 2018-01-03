//
// Created by Garrett Battaglia on 1/3/18.
//

#ifndef COLDBREW_PKGINFO_H
#define COLDBREW_PKGINFO_H

#include <stdio.h>

void parse_pkginfo(FILE* pkginfo_file);

void proc_pkg_line(char* buffer, int buf_size);

#endif //COLDBREW_PKGINFO_H
