//
// Created by Garrett Battaglia on 12/29/17.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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
	int res = connect(socket_num, (struct sockaddr *) &serv, sizeof(serv));
	if (res < 0) {
		//error
	}

	//send get request
	char *get_start = "GET ";
	char *get_tail = " HTTP/1.1\r\n\r\n";
	size_t get_req_leng = strlen(get_start) + strlen(to_dl.location) + strlen(get_tail);
	char *get_req = calloc(sizeof(char), get_req_leng);
	strcat(get_req, get_start);
	strcat(get_req, to_dl.location);
	strcat(get_req, get_tail);
	res = send(socket_num, get_req, get_req_leng, 0);
	if (res < 0) {
		//error
	}

	//open file for response
	size_t file_name_leng = strlen(local_loc) + strlen(local_filename);
	char *file_name = calloc(file_name_leng, sizeof(char));
	strcat(file_name, local_loc);
	strcat(file_name, local_filename);
	int file_num = creat(file_name, 0777);
	if (file_num < 0) {
		//error
	}
	//receive response
	char reply[256];
	//TODO check header for response code and print info if != 200
	//TODO remove header
	do {
		res = write(file_num, reply, 256);
		if (res < 0) {
			//error
		}
		res = recv(socket_num, reply, 258, 0);
		if (res <= 0){
			//error
		}
	} while (res == 256);

	//close file
	close(file_num);
	close(socket_num);
}