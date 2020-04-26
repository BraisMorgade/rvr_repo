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

	if (bind(sd, res->ai_addr, res->ai_addrlen) != 0) {
		printf("Unable to bind to host \n");
		return -1;
	}

	printf("Server initialised \n");


	freeaddrinfo(res);


	char buffer[80];
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	struct sockaddr client_addr;
	socklen_t client_len = sizeof(struct sockaddr);

	ssize_t bytes;

	int socket_opened = 1;



	while (socket_opened) {

		bytes = recvfrom(sd, buffer, 79 * sizeof(char), 0, &client_addr, &client_len);

		buffer[bytes] = '\0';

		getnameinfo(&client_addr, client_len, host, NI_MAXHOST, service,
			NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

		printf("%zd bytes de %s:%s \n", bytes, host, service);

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);

		char message[BUFSIZ] = "";

		if (buffer[0] == 't') {
			strftime(message, BUFSIZ, "%I:%M:%S%p", &tm);
		}
		else if (buffer[0] == 'd') {
			strftime(message, BUFSIZ, "%Y-%m-%d", &tm);
		}
		else if (buffer[0] == 'q') {
			strcpy(message, "Quiting...");
			socket_opened = 0;
		}
		else {
			strcpy(message, "Comando no soportado ");

			strncat(message, buffer, BUFSIZ);
		}
		sendto(sd, message, BUFSIZ, 0, &client_addr, client_len);

	}
	if (socket_opened == 0) close(sd);

	return 0;
}


