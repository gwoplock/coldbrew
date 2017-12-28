//
// Created by Garrett Battaglia on 12/27/17.
//

#include <string.h>
#include <unistd.h>
#include "scriptHandler.h"
#include "../../utils/print.h"
#include "../../utils/stringManip.h"


//this should be moved to a build script file
void build_blob(struct target *targ){
	//create tmp dir if needed
	if (targ->tmp_dir == NULL){
		char tmp_dir_template[256];
		//create a template for the temp dir, this will be where we build the package and such.
		strcat(tmp_dir_template, "/tmp/coldbrew.");
		strcat(tmp_dir_template, strip_path(targ->name));
		strcat(tmp_dir_template, ".XXXXXX");
		targ->tmp_dir = mkdtemp(tmp_dir_template);
		dbprintf(DEBUG, "target: %s, tempdir: %s\n", targ->name, targ->tmp_dir);
	}
	//parse script
	parse_script(targ->blob_script_loc);
	//extract srcs
	//run prep()
	//run build()
	//run check()
	//run package()
	//compress package
}

//this should be moved to a build script file with the above funct
void parse_script(char* script){

}