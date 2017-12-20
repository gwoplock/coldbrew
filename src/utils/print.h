//
// Created by Garrett Battaglia on 12/20/17.
//

#ifndef COLDBREW_PRINT_H
#define COLDBREW_PRINT_H

enum print_level {
	NORMAL, VERBOSE, DEBUG
};

void dbprintf(enum print_level pl, char* format, ...);

#endif //COLDBREW_PRINT_H
