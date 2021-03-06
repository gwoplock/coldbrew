//
// Created by Garrett Battaglia on 12/24/17.
//



#ifndef COLDBREW_INSTALL_H
#define COLDBREW_INSTALL_H

#include "../commandLine/CommandlineParser.h"
#include "../build_parser/package/package.h"

extern const short SHABANG;

extern const short GZ_MAGIC_NUM;


void install(struct target *targ);

enum type get_install_type(struct target *targ);

char *download_file(struct target targ, char *tmp_dir);


void install_blob(struct target *targ);

void extract_blob(struct target *targ);

void extract_srcinfo(struct target *targ);

#endif //COLDBREW_INSTALL_H
