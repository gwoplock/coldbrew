//
// Created by Garrett Battaglia on 12/29/17.
//


#include "http.h"
#include "print.h"
#include "../../commandLine/CommandlineParser.h"
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void download(struct resource to_dl, char *local_loc, char *local_filename)
{

	CURL *curl = curl_easy_init();

	int url_leng = strlen(to_dl.host) + strlen(to_dl.location);
	char *url = calloc(url_leng, sizeof(char));
	strcat(url, to_dl.host);
	strcat(url, to_dl.location);
	curl_easy_setopt(curl, CURLOPT_URL, url);

	size_t file_name_leng = strlen(local_loc) + strlen(local_filename);
	char *file_name = calloc(file_name_leng, sizeof(char));
	strcat(file_name, local_loc);
	strcat(file_name, local_filename);
	int file_num = creat(file_name, 0777);

	FILE *file = fdopen(file_num, "w");

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);

	if (config.brew_opts.verbosity == DEBUG) {
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	}

	CURLcode success = curl_easy_perform(curl);

	curl_easy_cleanup(curl);
}