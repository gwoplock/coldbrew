//
// Created by Garrett Battaglia on 12/29/17.
//

#ifndef COLDBREW_HTTP_H
#define COLDBREW_HTTP_H

struct resource
{
	char *IP;
	char *location;
};

void download(struct resource to_dl, char *local_loc, char *local_filename);

#endif //COLDBREW_HTTP_H
