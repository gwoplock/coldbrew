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
#include <errno.h>
#include "http.h"
#include "print.h"
#include "../commandLine/CommandlineParser.h"


void download(struct resource to_dl, char *local_loc, char *local_filename)
{
	//create socket
	int socket_num = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_num == -1) {
		dbfprintf(NORMAL, stderr, "There was an error opening the socket to download the file");
		dbfprintf(DEBUG, stderr,
		          "socket had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
		          strerror(errno));
		unlock();
		exit(6);
	}

	//connect to server
	struct sockaddr_in serv;
	serv.sin_addr.s_addr = inet_addr(to_dl.IP);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(80);
	ssize_t res = connect(socket_num, (struct sockaddr *) &serv, sizeof(serv));
	if (res < 0) {
		dbfprintf(NORMAL, stderr, "There was an error conneting to the server to download the file");
		dbfprintf(DEBUG, stderr,
		          "connect had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
		          strerror(errno));
		unlock();
		exit(6);
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
		dbfprintf(NORMAL, stderr, "There was an error sending the request of the file");
		dbfprintf(DEBUG, stderr,
		          "send had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
		          strerror(errno));
		unlock();
		exit(6);
	}

	//open file for response
	size_t file_name_leng = strlen(local_loc) + strlen(local_filename);
	char *file_name = calloc(file_name_leng, sizeof(char));
	strcat(file_name, local_loc);
	strcat(file_name, local_filename);
	int file_num = creat(file_name, 0777);
	if (file_num < 0) {
		dbfprintf(NORMAL, stderr, "There was an error creating the file");
		dbfprintf(DEBUG, stderr,
		          "creat had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
		          strerror(errno));
		unlock();
		exit(7);
	}

	//receive response
	char reply[256];
	int found_EOH = 1;
	int found_n = 1;
	int found_nr = 1;
	int first_read = 0;
	char status_code[4] = {0};
	ssize_t readb;
	do {

		readb = recv(socket_num, reply, 258, 0);
		if (res <= 0) {
			dbfprintf(NORMAL, stderr, "There was an error receveing the file");
			dbfprintf(DEBUG, stderr,
			          "recv had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
			          strerror(errno));
			unlock();
			exit(6);
		}
		if (first_read == 0) {
			// char 9-12
			status_code[0] = reply[9];
			status_code[1] = reply[10];
			status_code[2] = reply[11];
			status_code[3] = '\0';
			dbprintf(VERBOSE, "the server returned a %s response code.", status_code);
			first_read = 1;
		}
		if (strcmp(status_code, "200") == 0) {
			//TODO change
			dbfprintf(NORMAL, stderr, "the server didn't return a 200 OK message");
			dbfprintf(DEBUG, stderr, "The server returned a %s message insted of 200 OK", status_code);
			unlock();
			exit(8);
		}
		if (found_EOH != 0) {
			//I think this works for detecting the end of a header
			for (int i = 0; i < 256; i++) {
				if (reply[i] == '\r') {
					found_n = 0;
				} else if (reply[i] == '\n' && found_n == 0) {
					found_nr = 0;
					found_n = 1;
				} else {
					found_n = 1;
				}

				if (reply[i] == '\r' && found_nr == 0) {
					found_n = 0;
				} else if (reply[i] == '\n' && found_n == 0 && found_nr == 0) {
					found_nr = 1;
					found_n = 1;
					found_EOH = 0;
				} else if (reply[i] != '\n') {
					found_nr = 1;
					found_n = 1;
				}

				if (found_EOH) {
					res = write(file_num, reply + i, 256 - i);
				}
			}
		} else {
			res = write(file_num, reply, 256);
		}
		if (res < 0) {
			dbfprintf(NORMAL, stderr, "There was an error writing to the file");
			dbfprintf(DEBUG, stderr,
			          "write had an error and returned an errorno of %i, translated it is \"%s\"\n", errno,
			          strerror(errno));
			unlock();
			exit(7);
		}
	} while (readb == 256);

	//close file
	close(file_num);
	close(socket_num);
}