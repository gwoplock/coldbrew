//
// Created by Garrett Battaglia on 1/10/18.
//

#ifndef COLDBREW_PACKAGE_H
#define COLDBREW_PACKAGE_H


enum type
{
	PACKAGE, SCRIPT
};

struct pkginfo
{
	char *pkgver;
	char *cbver;
	int script_type;
	char *pkgname;
	char *build_date;
	char **deps;
	int to_install_count;
};

struct target
{
	char *name;
	char *tmp_dir;
	char *blob_loc;
	char *blob_script_loc;
	enum type target_type;
	struct pkginfo pkginfo;
};


extern struct target *targets;

#endif //COLDBREW_PACKAGE_H
