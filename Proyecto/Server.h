#ifndef Server_h
#define Server_h
#include "Socket.h"
#include <vector>
#include <list>

class Server{
public:
    struct Room{
        Socket* host;
        Socket* guest;
        bool playing;
        Room(Socket* h):host(h){
            guest=nullptr;
            playing=false;
        }
    };
    Server(const char* s, const char* p):socket(s, p){
        socket.bind();
    };
    void redirectMessages();
private:
    Socket socket;

    std::vector<Socket*> clients;

    std::list<Room*>rooms;

};

#endif