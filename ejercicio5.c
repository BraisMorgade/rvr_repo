#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	struct addrinfo hints;
	struct addrinfo* res;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0)
	{
		printf("getaddrinfo: %s\n", gai_strerror(rc));
		return -1;
	}

	int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (connect(sd, res->ai_addr, res->ai_addrlen) != 0) {
		printf("Unable to connect to server \n");
		return -1;
	}


	freeaddrinfo(res);

	char buffer[80];

	while (1) {

		scanf("%s", buffer);

		if (buffer[0] == 'Q')
			return 0;

		send(sd, (void*)buffer, 80, 0);

		char message[80];

		recv(sd, (void*)message, 80, 0);

		printf("%s \n", message);
	}
	return 0;
}


