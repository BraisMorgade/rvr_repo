#include "Server.h"
#include "NetMessage.h"


void Server::redirectMessages(){
    while(true){
        NetMessage m;
        Socket* client;
        socket.recv(m, client);
        switch(m.type){
            case NetMessage::INPUT:{
                auto r= rooms.begin();
                while(r!=rooms.end()){
                    if((*r)->playing){
                        if(*(*r)->guest==*client){
                            socket.send(m, *(*r)->host);
                            break;
                        }
                        else if(*(*r)->host==*client){
                            socket.send(m, *(*r)->guest);
                            break;
                        }
                    }
                    r++;
                }
                break;
            }
            case NetMessage::CREATE_ROOM:{
                auto r=rooms.begin();
                bool alreadyInRoom=false;
                while(r!=rooms.end()){
                    if(*(*r)->host == *client || *(*r)->guest==*client){
                        alreadyInRoom=true;
                        break;
                    }
                    else r++;
                }
                if(!alreadyInRoom){
                    rooms.emplace_back(new Room(client));
                    socket.send(m, *client);
                }
                break;
            }
            case NetMessage::JOIN:{
                auto r=rooms.begin();
                while(r!=rooms.end()){
                    if(*(*r)->host == *client){
                        break;
                    }
                    else if((*r)->guest==nullptr){
                        (*r)->guest=client;
                        socket.send(m, *(*r)->guest);
                        socket.send(m, *(*r)->host);
                        (*r)->playing=true;
                    }
                    else r++;
                }
                break;
            }
            case NetMessage::BEGIN_MATCH:{
                auto r=rooms.begin();
                while(r!=rooms.end()){
                    if(*(*r)->host==*client){
                        socket.send(m, *(*r)->host);
                        socket.send(m, *(*r)->guest);
                        (*r)->playing=true;
                        break;
                    }
                    r++;
                }
            }
            default:
                break;
        }
        /*
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
        */

    }
}