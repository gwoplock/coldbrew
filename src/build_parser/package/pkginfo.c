//
// Created by Garrett Battaglia on 1/3/18.
//

#include <stdlib.h>
#include "pkginfo.h"
#include "../../utils/fileIO.h"

void parse_pkginfo(FILE* pkginfo_file){
	char* buf = calloc(256, sizeof(char));
	for(int i = 0; i< 6;i++){
		int succ = read_line(buf,256,pkginfo_file);
		if(succ == 1){
			proc_pkg_line(buf,256);
		} else if (succ > 0){
			//error
		} else {
			//didnt read full line
		}
	}
}

void proc_pkg_line(char* buffer, int buf_size){

}