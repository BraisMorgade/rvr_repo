#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <thread>
#include <vector>
#include <mutex>
#include <iostream>

class Connection {
public:
	Connection(int sd_client) { sd_client_ = sd_client; };
	void communicate() {

		while (true) {

			char buffer[80];
			ssize_t bytes = recv(sd_client_, (void*)buffer,
				sizeof(char) * 79, 0);

			std::cout << sd_client_ << std::endl;

			if (bytes <= 0) {
				break;
			}

			bytes = send(sd_client_, (void*)buffer, bytes, 0);

			if (bytes <= 0) {
				break;
			}

		}
		printf("Conexion terminada \n");
		close(sd_client_);


	};
private:
	int sd_client_;

};

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

	std::vector<Connection*> v;
	std::vector<std::thread*> pool;
	while (true) {
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

		printf("CONEXION DESDE IP:  %s PUERTO: %s CLIENTE: %d \n", host, service, sd_client);


		v.push_back(new Connection(sd_client));
		pool.push_back(new std::thread(&Connection::communicate,
			v.back()));

		pool.back()->detach();

	}
	for (int i = 0; i < pool.size(); i++) {
		delete pool[i];
	}
	for (int i = 0; i < v.size(); i++) {
		delete v[i];
	}

	return 0;
}


