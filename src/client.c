/*
 * client.c
 *
 *  Created on: Nov 20, 2017
 *      Author: tyty5949
 */

#include "client.h"

struct addrinfo *client_get_addrinfo(int ai_family, int ai_socktype, char **hostname) {
	int status;
	struct addrinfo *info, hints;

	memset(&hints, 0, sizeof hints);
	hints->ai_family = ai_family;
	hints->ai_socktype = ai_socktype;

	if ((status = getaddrinfo(*hostname, NULL, &hints, info)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return NULL;
	}

	return info;
}
