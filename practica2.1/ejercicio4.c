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

	if (bind(sd, res->ai_addr, res->ai_addrlen) != 0) {
		printf("Unable to bind to host \n");
		return -1;
	}

	printf("Server initialised \n");


	freeaddrinfo(res);

	listen(sd, BUFSIZ);

	struct sockaddr client_addr;
	socklen_t client_len = sizeof(struct sockaddr);

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];


	int sd_client = accept(sd, &client_addr, &client_len);

	if (sd_client == -1) {
		printf("accept error");
		return -1;
	}

	getnameinfo(&client_addr, client_len, host, NI_MAXHOST, service,
		NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

	printf("CONEXION DESDE IP:  %s PUERTO: %s \n", host, service);

	char buffer[80];

	while (1) {
		ssize_t bytes = recv(sd_client, (void*)buffer,
			sizeof(char) * 79, 0);

		if (bytes <= 0) {
			printf("Conexion terminada \n");
			return 0;
		}

		bytes = send(sd_client, (void*)buffer, bytes, 0);

		if (bytes <= 0) {
			printf("Conexion terminada \n");
			return 0;
		}
	}
	return 0;
}


