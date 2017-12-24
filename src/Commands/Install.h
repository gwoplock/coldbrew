//
// Created by Garrett Battaglia on 12/24/17.
//

#include "../commandLine/CommandlineParser.h"

#ifndef COLDBREW_INSTALL_H
#define COLDBREW_INSTALL_H


void install(struct target targ);

enum type get_install_type(struct target targ);

#endif //COLDBREW_INSTALL_H
