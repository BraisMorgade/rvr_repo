#include <string.h>

#include "Serializable.h"
#include "Socket.h"

Socket::Socket(const char* address, const char* port) :sd(-1)
{
    struct addrinfo hints;
    struct addrinfo* res;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(address, port, &hints, &res);

    if (rc != 0) {
        std::cout << "El servidor no es valido" << "\n";
    }
    else {
        sa = *res->ai_addr;
        sa_len = res->ai_addrlen;
        sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    }
}

int Socket::recv(Serializable& obj, Socket*& sock)
{
    struct sockaddr sa;
    socklen_t sa_len = sizeof(struct sockaddr);

    char buffer[MAX_MESSAGE_SIZE];

    ssize_t bytes = ::recvfrom(sd, buffer, MAX_MESSAGE_SIZE, 0, &sa, &sa_len);

    if (bytes <= 0)
    {
        return -1;
    }
    
    sock = new Socket(&sa, sa_len);

    obj.from_bin(buffer);

    return 0;
}

int Socket::send(Serializable& obj, const Socket& sock)
{
    obj.to_bin();
    sendto(sd, obj.data(), obj.size(), 0, &sock.sa, sock.sa_len);
}

bool operator== (const Socket& s1, const Socket& s2)
{
    struct sockaddr_in* s1sock = (struct sockaddr_in*) & (s1.sa);
    struct sockaddr_in* s2sock = (struct sockaddr_in*) & (s2.sa);

    return (s1sock->sin_family == s2sock->sin_family &&
        s1sock->sin_addr.s_addr == s2sock->sin_addr.s_addr &&
        s1sock->sin_port == s2sock->sin_port);
};

std::ostream& operator<<(std::ostream& os, const Socket& s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr*) & (s.sa), s.sa_len, host, NI_MAXHOST, serv,
        NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;

    return os;
};
