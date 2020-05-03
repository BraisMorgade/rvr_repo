#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>



int main(int argc, char** argv)
{
	struct addrinfo hints;
	struct addrinfo* res;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = 0;
	hints.ai_flags = AI_PASSIVE;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0) {
		printf("Error: Name or service not known \n");
		return -1;
	}

	struct addrinfo* currentaddr = res;
	while (currentaddr != NULL) {

		char host[NI_MAXHOST];
		char service[NI_MAXSERV];

		getnameinfo(currentaddr->ai_addr, currentaddr->ai_addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

		printf("IP: %s\n", host);
		printf("Familia: %d\n", currentaddr->ai_family);
		printf("Tipo de socket: %d\n", currentaddr->ai_socktype);

		currentaddr = currentaddr->ai_next;
	}

	freeaddrinfo(res);

	return 0;

}