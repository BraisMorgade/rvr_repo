#ifndef NetMessage_h
#define NetMessage_h
#include "Serializable.h"
#include <stdio.h>
#include <string.h>
#include <iostream>


class NetMessage: public Serializable{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 80 + sizeof(u_int8_t);
    struct IN{
        bool left;
        bool right;
        bool up;
        bool down;
        bool atk;
    };
    enum MessageType
    {
        LOGIN = 0,
        INPUT = 1,
        LOGOUT = 2
    };

    NetMessage() {
    };

    NetMessage(u_int8_t t, char* m) :type(t) {
        message=(char*)malloc(sizeof(char)*82);
        memcpy(message, m, sizeof(char)*80);
        /*
        char* tmp = m;
        memcpy(&inputs.left,tmp, sizeof(bool));
        tmp+=sizeof(bool);

        if(inputs.left)
        std::cout<<"izquierda"<<std::endl;

        memcpy(&inputs.right,tmp, sizeof(bool));
        tmp+=sizeof(bool);

        memcpy(&inputs.up, tmp, sizeof(bool));
        tmp+=sizeof(bool);

        memcpy(&inputs.down, tmp,sizeof(bool));
        tmp+=sizeof(bool);

        memcpy( &inputs.atk,tmp, sizeof(bool));
        */
    };

    void to_bin() override;

    int from_bin(char* bobj) override;

    u_int8_t type;

    char* message;

    IN inputs;

  

};

#endif