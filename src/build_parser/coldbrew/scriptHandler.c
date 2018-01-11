//
// Created by Garrett Battaglia on 12/27/17.
//

#include <string.h>
#include <stdlib.h>
#include "scriptHandler.h"
#include "../../utils/stringManip.h"
#include "../../utils/IO/temporaryFiles.h"


//this should be moved to a build script file
void build_blob(struct target *targ)
{
	//create tmp dir if needed
	if (targ->tmp_dir == NULL) {
		targ->tmp_dir = create_tmp_dir(strip_path(targ->name));
	}
	//parse script
	struct script *script = parse_script(targ->blob_script_loc);
	//download and extract srcs
	for (int i = 0; i < script->src_leng; i++) {
		download_src(&script->srcs[i]);
		//extract src
		extract_src(&script->srcs[i]);
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
struct script *parse_script(char *script_path)
{
	struct script *ret = calloc(sizeof(struct script), 1);

	return ret;
}

void download_src(struct source *src)
{

}

void extract_src(struct source *src)
{

}

void script_prep(struct script *script)
{

}

void script_build(struct script *script)
{

}

void script_check(struct script *script)
{

}

void script_package(struct script *script)
{

}

void package_compress(struct script *script)
{

}