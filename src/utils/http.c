//
// Created by Garrett Battaglia on 12/29/17.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "http.h"


void download(struct resource to_dl, char *local_loc, char *local_filename)
{
	//create socket
	int socket_num = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_num == -1) {
		//error
	}
	//connect to server
	struct sockaddr_in serv;
	serv.sin_addr.s_addr = inet_addr(to_dl.IP);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(80);
	int con_res = connect(socket_num, (struct sockaddr *) &serv, sizeof(serv));
	if (con_res < 0) {
		//error
	}
	//send get request
	//receive response
}