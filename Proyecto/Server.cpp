#include "Server.h"
#include "NetMessage.h"

void Server::redirectMessages(){
    while(true){
        NetMessage m;
        Socket* client;
        socket.recv(m, client);
        switch(m.type){
            case NetMessage::LOGIN:
                clients.push_back(client);
                break;
            case NetMessage::LOGOUT:
                for (int i = 0; i < clients.size(); i++) {
                    if (*clients[i] == *client) {
                        clients.erase(clients.begin() + i);
                        break;
                    }
                }   
                break;
            case NetMessage::INPUT:{
                bool clientInList=false;
                for(int i=0; i<clients.size(); i++){
                    if(!(*clients[i] == *client)){
                        socket.send(m, *clients[i]);
                    }
                    else{
                        clientInList=true;
                    }
                }
                if(!clientInList){
                    clients.push_back(client);
                }
                break;
            }
            default:
                break;
        }

    }
}