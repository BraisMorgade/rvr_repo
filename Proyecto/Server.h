#ifndef Server_h
#define Server_h
#include "Socket.h"
#include <vector>


class Server{
public:
    Server(const char* s, const char* p):socket(s, p){
        socket.bind();
    };
    void redirectMessages();
private:
    Socket socket;

    std::vector<Socket*> clients;
};

#endif