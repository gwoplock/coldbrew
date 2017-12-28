//
// Created by Garrett Battaglia on 12/27/17.
//

#include <string.h>
#include <unistd.h>
#include "scriptHandler.h"
#include "../../utils/print.h"
#include "../../utils/stringManip.h"


//this should be moved to a build script file
void build_blob(struct target *targ)
{
	//create tmp dir if needed
	if (targ->tmp_dir == NULL) {
		char tmp_dir_template[256];
		//create a template for the temp dir, this will be where we build the package and such.
		strcat(tmp_dir_template, "/tmp/coldbrew.");
		strcat(tmp_dir_template, strip_path(targ->name));
		strcat(tmp_dir_template, ".XXXXXX");
		targ->tmp_dir = mkdtemp(tmp_dir_template);
		dbprintf(DEBUG, "target: %s, template: %s, tempdir: %s\n", targ->name, tmp_dir_template, targ->tmp_dir);
	}
	//parse script
	struct script script = parse_script(targ->blob_script_loc);
	//download and extract srcs
	for (int i = 0; i < script.src_leng; i++) {
		download_src(&script.srcs[i]);
		//extract src
		extract_src(&script.srcs[i]);
	}
	//run prep()
	script_prep(script);
	//run build()
	script_build(script);
	//run check()
	script_check(script);
	//run package()
	script_package(script);
	//compress package
	package_compress(script);
}

//this should be moved to a build script file with the above funct
struct script parse_script(char *script_path)
{

}

void download_src(struct source *src)
{

}

void extract_src(struct source *src){

}

void script_prep(struct script script)
{

}

void script_build(struct script script)
{

}

void script_check(struct script script)
{

}

void script_package(struct script script)
{

}

void package_compress(struct script script)
{

}