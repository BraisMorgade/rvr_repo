#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <atomic>

#include <iostream>
#include <thread>
#include <vector>



class Communication {
public:
	Communication(int sd) :sd_(sd) {};
	void communicate(int id) {
		char buffer[80];
		char host[NI_MAXHOST];
		char service[NI_MAXSERV];
		struct sockaddr client_addr;
		socklen_t client_len = sizeof(struct sockaddr);
		ssize_t bytes;


		while (true) {
			bytes = recvfrom(sd_, buffer, 79 * sizeof(char), 0, &client_addr, &client_len);
			buffer[bytes] = '\0';
			getnameinfo(&client_addr, client_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
			std::cout << "THREAD: " << id << " IP: " << host << " 				PUERTO: " << service << "MENSAJE: " << buffer << std::endl;
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			char message[BUFSIZ] = "";
			if (buffer[0] == 't') {
				strftime(message, BUFSIZ, "%I:%M:%S%p", &tm);
			}
			else if (buffer[0] == 'd') {
				strftime(message, BUFSIZ, "%Y-%m-%d", &tm);
			}
			else {
				strcpy(message, "Comando no soportado ");
				strncat(message, buffer, BUFSIZ);
			}
			sendto(sd_, message, BUFSIZ, 0, &client_addr, client_len);

		}
	};
private:
	int sd_;
};

int main(int argc, char** argv)
{
	struct addrinfo hints;
	struct addrinfo* res;

	// ---------------------------------------------------------------------- //
	// INICIALIZACIÓN SOCKET & BIND //
	// ---------------------------------------------------------------------- //

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0) {
		std::cerr << "getaddrinfo: " << gai_strerror(rc) << std::endl;
		return -1;
	}

	// res contiene la representación como sockaddr de dirección + puerto

	int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (bind(sd, res->ai_addr, res->ai_addrlen) != 0) {
		std::cerr << "bind: " << std::endl;
		return -1;
	}

	freeaddrinfo(res);
	// -------------------------------------------------------------------------
	// POOL DE THREADS
	// -------------------------------------------------------------------------
	std::vector<std::thread> pool;

	for (int i = 0; i < 5; ++i) {
		Communication c(sd);
		pool.push_back(std::thread(&Communication::communicate, &c, i));
	}
	std::string quit = "";
	while (quit != "q") {
		std::cin >> quit;
	}
	std::cout << "quiting..\n";

	for (auto& t : pool) {
		t.detach();
	}

	close(sd);

	return 0;
}