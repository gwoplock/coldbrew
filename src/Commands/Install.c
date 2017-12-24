//
// Created by Garrett Battaglia on 12/24/17.
//

#include <stdio.h>
#include "Install.h"

void install(struct target targ)
{
	enum type get_intall_type = get_install_type(targ);

}

enum type get_install_type(struct target targ)
{
	FILE* file;
	if (((struct install_options *) (config.mode_opts))->local == 1) {
		file = fopen(targ.name, "r");
	} else {
		//create tmp dir 
		//download to tmp
		//open file
	}

	//check type

	//close file

	//TODO: not this
	return (enum type) NULL;
}