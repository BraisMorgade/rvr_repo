#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv)
{
	struct addrinfo hints;
	struct addrinfo* res;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0)
	{
		printf("getaddrinfo: %s\n", gai_strerror(rc));
		return -1;
	}


	int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (connect(sd, res->ai_addr, res->ai_addrlen) != 0) {
		printf("Unable to connect to host \n");
		return -1;
	}


	freeaddrinfo(res);

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ssize_t bytes;

	bytes = sendto(sd, argv[3], 2, 0, res->ai_addr, res->ai_addrlen);

	char message[BUFSIZ];

	recvfrom(sd, message, BUFSIZ, 0, res->ai_addr, &res->ai_addrlen);

	printf("%s \n", &message);

	close(sd);

	return 0;
}


