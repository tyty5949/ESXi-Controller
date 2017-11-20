/*
 MIT License

 Copyright (c) 2017 Tyler Hunt

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void print_constants() {
	printf("AF_INET=%i\n", AF_INET);
	printf("AF_INET6=%i\n", AF_INET6);
	printf("SOCK_STREAM=%i\n", SOCK_STREAM);
	printf("SOCK_DGRAM=%i\n", SOCK_DGRAM);
	printf("IPPROTO_TCP=%i\n", IPPROTO_TCP);
	printf("IPPROTO_UDP=%i\n", IPPROTO_UDP);
}

void print_sockaddr(struct sockaddr *skaddr) {
	char ipstr[skaddr->sa_len];
	int ipver;
	int port;

	if (skaddr->sa_family == AF_INET) {
		struct sockaddr_in *ipv4 = (struct sockaddr_in *) skaddr;
		ipver = 4;
		port = ipv4->sin_port;
		inet_ntop(skaddr->sa_family, &(ipv4->sin_addr), ipstr, sizeof ipstr);

	} else {
		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) skaddr;
		ipver = 6;
		port = ipv6->sin6_port;
		inet_ntop(skaddr->sa_family, &(ipv6->sin6_addr), ipstr, sizeof ipstr);
	}

	printf("\tipv%i: %s:%i\n", ipver, ipstr, port);
}

int main(int argc, char **argv) {
	int status; /*!< Return status of getaddrinfo() */
	struct addrinfo hints; /*!< Sets up the type of addrinfo to get */
	struct addrinfo *serverinfo; /*!< The addrinfo from the getaddrinfo function */
	struct addrinfo *node; /*!< Used to traverse serverinfo */

	print_constants();

	// Setup hints
	memset(&hints, 0, sizeof hints); /* 0 out the entire hints struct */
	hints.ai_family = AF_UNSPEC; /* Say we don't care if its ipv4 or ipv6 */
	//hints.ai_flags = AI_PASSIVE; /* Say we want to automatically use this servers ip */
	hints.ai_socktype = SOCK_STREAM; /* Say we want a stream socket */

	// Attempts the getaddrinfo function as a server
	if ((status = getaddrinfo("www.duckduckgo.com", NULL, &hints, &serverinfo)) != 0) {
		// Prints out the error based on the returned status code
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(0);
	}

	// Traverse the addrinfo
	for (node = serverinfo; node != 0; node = node->ai_next) {
		printf("\n\nNode Found:\n");
		printf("\tai_flags=%i\n", node->ai_flags);
		printf("\tai_family=%i\n", node->ai_family);
		printf("\tai_socktype=%i\n", node->ai_socktype);
		printf("\tai_protocol=%i\n", node->ai_protocol);
		printf("\tai_addrlen=%i\n", node->ai_addrlen);
		// sockaddr
		print_sockaddr(node->ai_addr);
		printf("\tai_canonname=%s\n", node->ai_canonname);
	}

	// Frees up the linked list within the addrinfo struct
	freeaddrinfo(serverinfo);

	return 0;
}
